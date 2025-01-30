#ifndef _WIN32
    #include "http_client.h"
    #include "http_response.h"
    #include "logger.h"

    bool HTTP_Client::Send_Request_Linux(const std::string& host, const std::string& path, const std::string& data) {
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_all_algorithms();

        const SSL_METHOD* method = SSLv23_client_method();

        if (!method)
            return (Log_Printf("[SPC Integration]: Server Error: Failed to create SSL method."), false);

        SSL_CTX* ctx = SSL_CTX_new(method);

        if (!ctx)
            return (Log_Printf("[SPC Integration]: Server Error: Failed to create SSL context."), false);

        SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            SSL_CTX_free(ctx);
            Log_Printf("[SPC Integration]: Server Error: Failed to create socket.");

            return false;
        }

        struct timeval timeout;
        timeout.tv_sec = 60;
        timeout.tv_usec = 0;

        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0 || setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
            close(sockfd);
            SSL_CTX_free(ctx);
            Log_Printf("[SPC Integration]: Server Error: Failed to set socket timeout.");
            
            return false;
        }

        struct hostent* server = gethostbyname(host.c_str());

        if (!server) {
            close(sockfd);
            SSL_CTX_free(ctx);
            Log_Printf("[SPC Integration]: Server Error: Failed to resolve hostname: '%s'.", host.c_str());

            return false;
        }

        struct sockaddr_in serv_addr;
        std::memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(443);
        std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

        if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            close(sockfd);
            SSL_CTX_free(ctx);
            Log_Printf("[SPC Integration]: Server Error: Failed to connect to server: '%s'.", host.c_str());

            return false;
        }

        SSL* ssl = SSL_new(ctx);

        if (!ssl) {
            close(sockfd);
            SSL_CTX_free(ctx);
            Log_Printf("[SPC Integration]: Server Error: Failed to create SSL object.");

            return false;
        }

        SSL_set_fd(ssl, sockfd);
        SSL_set_tlsext_host_name(ssl, host.c_str());

        if (SSL_connect(ssl) != 1) {
            SSL_free(ssl);
            close(sockfd);
            SSL_CTX_free(ctx);
            Log_Printf("[SPC Integration]: Server Error: SSL connection failed.");

            return false;
        }

        std::stringstream request;
        request << "POST " << path << " HTTP/1.1\r\n"
            << "Host: " << host << "\r\n"
            << "Content-Type: application/x-www-form-urlencoded\r\n"
            << "Content-Length: " << data.length() << "\r\n"
            << "Connection: close\r\n"
            << "\r\n"
            << data;

        std::string request_str = request.str();

        int written = 0;
        int total = request_str.length();

        while (written < total) {
            int bytes = SSL_write(ssl, request_str.c_str() + written, total - written);

            if (bytes <= 0) {
                int err = SSL_get_error(ssl, bytes);

                if (err != SSL_ERROR_WANT_WRITE && err != SSL_ERROR_WANT_READ) {
                    SSL_free(ssl);
                    close(sockfd);
                    SSL_CTX_free(ctx);
                    Log_Printf("[SPC Integration]: Server Error: Failed to send request.");

                    return false;
                }
                continue;
            }
            written += bytes;
        }

        std::string response;
        char buffer[4096];
        bool headers_complete = false;
        std::string header_buffer;

        while (true) {
            int bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);

            if (bytes <= 0) {
                int err = SSL_get_error(ssl, bytes);

                if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE)
                    break;

                continue;
            }

            buffer[bytes] = '\0';

            if (!headers_complete) {
                header_buffer.append(buffer, bytes);
                size_t header_end = header_buffer.find("\r\n\r\n");

                if (header_end != std::string::npos) {
                    response = header_buffer.substr(header_end + 4);
                    headers_complete = true;
                }
            }
            else
                response.append(buffer, bytes);
        }

        bool result = false;
        HTTP_Response http_response;

        if (http_response.Parse_Response(response)) {
            http_response.Log_Response();
            result = http_response.success;
        }
        else
            Log_Printf("[SPC Integration]: Server Error: Failed to parse server response: '%s'.", response.c_str());

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(sockfd);
        SSL_CTX_free(ctx);
        ERR_free_strings();
        EVP_cleanup();

        return result;
    }
#endif