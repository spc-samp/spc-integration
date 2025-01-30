#include "logger.h"
#include "url_validator.h"

bool URL_Validator::Is_Valid(const std::string& url) {
    Log_Printf(" ");
    Log_Printf("[SPC Integration]: Starting full validation of the image URL...");

    return Validate_With_Timeout(url);
}

bool URL_Validator::Validate_With_Timeout(const std::string& url) {
    auto future = std::async(std::launch::async, [&url]() {
        return Perform_Full_Validation(url);
    });

    if (future.wait_for(std::chrono::seconds(VALIDATION_TIMEOUT)) == std::future_status::timeout)
        return (Log_Printf("[SPC Integration]: Error: Timeout during URL validation after '%d' seconds.", VALIDATION_TIMEOUT), false);

    try {
        return future.get();
    }
    catch (const std::exception& e) {
        Log_Printf("[SPC Integration]: Error during validation: '%s'.", e.what());

        return false;
    }
}

bool URL_Validator::Perform_Full_Validation(const std::string& url) {
    if (url.empty() || url.length() > 2048)
        return (Log_Printf("[SPC Integration]: Error: URL is empty or too long (maximum 2048 characters)."), false);

    if (!Has_Valid_Scheme(url))
        return (Log_Printf("[SPC Integration]: Error: URL must start with 'http://' or 'https://'."), false);

    if (!Has_Valid_HostAndPath(url))
        return (Log_Printf("[SPC Integration]: Error: URL must contain a valid hostname and path."), false);

    if (!Has_Valid_Characters(url))
        return (Log_Printf("[SPC Integration]: Error: URL contains invalid characters."), false);

    if (!Validate_Image_Headers(url))
        return (Log_Printf("[SPC Integration]: Error: The URL content is not a valid image."), false);

    Log_Printf("[SPC Integration]: Validation successfully completed!");

    return true;
}

bool URL_Validator::Validate_Image_Headers(const std::string& url) {
    std::vector<unsigned char> header_data;
    std::string host, path;

    size_t scheme_end = url.find("://");

    if (scheme_end == std::string::npos)
        return false;

    size_t host_start = scheme_end + 3;
    size_t path_start = url.find("/", host_start);

    if (path_start == std::string::npos) {
        host = url.substr(host_start);
        path = "/";
    }
    else {
        host = url.substr(host_start, path_start - host_start);
        path = url.substr(path_start);
    }

    #ifdef _WIN32
        std::wstring w_host(host.begin(), host.end());
        std::wstring w_path(path.begin(), path.end());

        if (!Fetch_Image_Data_Windows(w_host, w_path, header_data))
            return false;
    #else
        if (!Fetch_Image_Data_Linux(host, path, header_data))
            return false;
    #endif

    return Check_Image_Magic_Numbers(header_data);
}

bool URL_Validator::Check_Image_Magic_Numbers(const std::vector<unsigned char>& data) {
    if (data.size() < 4)
        return false;

    // JPEG (FF D8 FF)
    if (data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF)
        return true;

    // PNG (89 50 4E 47 0D 0A 1A 0A)
    if (data.size() >= 8 && data[0] == 0x89 && data[1] == 0x50 && data[2] == 0x4E &&
        data[3] == 0x47 && data[4] == 0x0D && data[5] == 0x0A && data[6] == 0x1A && data[7] == 0x0A)
        return true;

    // GIF (47 49 46 38)
    if (data[0] == 0x47 && data[1] == 0x49 && data[2] == 0x46 && data[3] == 0x38)
        return true;
 
    // BMP (42 4D)
    if (data[0] == 0x42 && data[1] == 0x4D)
        return true;

    // WebP (52 49 46 46 ... 57 45 42 50)
    if (data.size() >= 12 && data[0] == 0x52 && data[1] == 0x49 && data[2] == 0x46 &&
        data[3] == 0x46 && data[8] == 0x57 && data[9] == 0x45 && data[10] == 0x42 && data[11] == 0x50)
        return true;

    return false;
}

bool URL_Validator::Has_Valid_Scheme(const std::string& url) {
    return (url.substr(0, 7) == "http://" || url.substr(0, 8) == "https://");
}

bool URL_Validator::Has_Valid_HostAndPath(const std::string& url) {
    std::regex host_path_pattern(R"(^https?://([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}(/[^/\s]*)*$)");

    return std::regex_match(url, host_path_pattern);
}

bool URL_Validator::Has_Valid_Characters(const std::string& url) {
    std::regex valid_chars_pattern(R"(^[a-zA-Z0-9\-._~:/?#\[\]@!$&'()*+,;=\%]*$)");
    
    return std::regex_match(url, valid_chars_pattern);
}

#ifdef _WIN32
    bool URL_Validator::Fetch_Image_Data_Windows(const std::wstring& host, const std::wstring& path, std::vector<unsigned char>& data) {
        HINTERNET spc_session = NULL, spc_connect = NULL, spc_request = NULL;

        bool result = false;

        spc_session = WinHttpOpen(L"URL-Validator/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

        if (!spc_session)
            return false;

        spc_connect = WinHttpConnect(spc_session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);

        if (!spc_connect)
            return (WinHttpCloseHandle(spc_session), false);

        spc_request = WinHttpOpenRequest(spc_connect, L"GET", path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

        if (!spc_request) {
            WinHttpCloseHandle(spc_connect);
            WinHttpCloseHandle(spc_session);

            return false;
        }

        std::wstring range_header = L"Range: bytes=0-" + std::to_wstring(MAX_HEADER_SIZE - 1);
        WinHttpAddRequestHeaders(spc_request, range_header.c_str(), -1L, WINHTTP_ADDREQ_FLAG_ADD);

        if (WinHttpSendRequest(spc_request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
            if (WinHttpReceiveResponse(spc_request, NULL)) {
                DWORD bytes_available;
                data.reserve(MAX_HEADER_SIZE);

                while (WinHttpQueryDataAvailable(spc_request, &bytes_available) && bytes_available > 0) {
                    std::vector<unsigned char> buffer(bytes_available);
                    DWORD bytes_read = 0;

                    if (WinHttpReadData(spc_request, buffer.data(), bytes_available, &bytes_read)) {
                        data.insert(data.end(), buffer.begin(), buffer.begin() + bytes_read);

                        if (data.size() >= MAX_HEADER_SIZE)
                            break;
                    }
                }

                result = !data.empty();
            }
        }

        if (spc_request)
            WinHttpCloseHandle(spc_request);

        if (spc_connect)
            WinHttpCloseHandle(spc_connect);

        if (spc_session)
            WinHttpCloseHandle(spc_session);

        return result;
    }
#else
    bool URL_Validator::Fetch_Image_Data_Linux(const std::string& host, const std::string& path, std::vector<unsigned char>& data) {
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_all_algorithms();

        const SSL_METHOD* method = SSLv23_client_method();

        if (!method)
            return false;

        SSL_CTX* ctx = SSL_CTX_new(method);

        if (!ctx)
            return false;

        SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0)
            return (SSL_CTX_free(ctx), false);

        struct hostent* server = gethostbyname(host.c_str());

        if (!server) {
            close(sockfd);
            SSL_CTX_free(ctx);

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

            return false;
        }

        SSL* ssl = SSL_new(ctx);

        if (!ssl) {
            close(sockfd);
            SSL_CTX_free(ctx);

            return false;
        }

        SSL_set_fd(ssl, sockfd);
        SSL_set_tlsext_host_name(ssl, host.c_str());

        if (SSL_connect(ssl) != 1) {
            SSL_free(ssl);
            close(sockfd);
            SSL_CTX_free(ctx);

            return false;
        }

        std::string request = "GET " + path + " HTTP/1.1\r\n"
            "Host: " + host + "\r\n"
            "Range: bytes=0-" + std::to_string(MAX_HEADER_SIZE - 1) + "\r\n"
            "Connection: close\r\n\r\n";

        SSL_write(ssl, request.c_str(), request.length());

        std::vector<unsigned char> buffer(4096);
        bool headers_parsed = false;
        data.reserve(MAX_HEADER_SIZE);

        while (int bytes = SSL_read(ssl, buffer.data(), buffer.size())) {
            if (bytes <= 0)
                break;

            if (!headers_parsed) {
                std::string response(buffer.begin(), buffer.begin() + bytes);
                size_t header_end = response.find("\r\n\r\n");

                if (header_end != std::string::npos) {
                    headers_parsed = true;
                    data.insert(data.end(), buffer.begin() + header_end + 4, buffer.begin() + bytes);
                }
            }
            else
                data.insert(data.end(), buffer.begin(), buffer.begin() + bytes);

            if (data.size() >= MAX_HEADER_SIZE)
                break;
        }

        SSL_free(ssl);
        close(sockfd);
        SSL_CTX_free(ctx);
        ERR_free_strings();
        EVP_cleanup();

        return !data.empty();
    }
#endif