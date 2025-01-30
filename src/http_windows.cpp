#ifdef _WIN32
    #include "http_client.h"
    #include "http_response.h"
    #include "logger.h"

    bool HTTP_Client::Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data) {
        HINTERNET spc_session = NULL, spc_connect = NULL, spc_request = NULL;

        bool result = false;

        spc_session = WinHttpOpen(L"SPC-INTEGRATION/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

        if (!spc_session)
            return (Log_Printf("[SPC Integration]: Server Error: Failed to initialize WinHTTP session."), false);

        DWORD timeout = 60000;

        WinHttpSetOption(spc_session, WINHTTP_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
        WinHttpSetOption(spc_session, WINHTTP_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
        WinHttpSetOption(spc_session, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

        spc_connect = WinHttpConnect(spc_session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);

        if (!spc_connect) {
            WinHttpCloseHandle(spc_session);
            Log_Printf("[SPC Integration]: Server Error: Failed to connect to host.");

            return false;
        }

        spc_request = WinHttpOpenRequest(spc_connect, L"POST", path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

        if (!spc_request) {
            WinHttpCloseHandle(spc_connect);
            WinHttpCloseHandle(spc_session);
            Log_Printf("[SPC Integration]: Server Error: Failed to create request.");

            return false;
        }

        const wchar_t* headers = L"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
            L"Accept: application/json\r\n"
            L"Connection: Keep-Alive\r\n";

        DWORD max_buffer_size = 64 * 1024;

        WinHttpSetOption(spc_request, WINHTTP_OPTION_MAX_RESPONSE_DRAIN_SIZE, &max_buffer_size, sizeof(max_buffer_size));

        if (WinHttpSendRequest(spc_request, headers, -1L, (LPVOID)data.c_str(), data.length(), data.length(), 0)) {
            if (WinHttpReceiveResponse(spc_request, NULL)) {
                std::string response;
                DWORD size = 0;
                DWORD downloaded = 0;
                char* buffer = NULL;

                do {
                    size = 0;
                    WinHttpQueryDataAvailable(spc_request, &size);

                    if (size == 0)
                        break;

                    buffer = new char[size + 1];
                    ZeroMemory(buffer, size + 1);

                    if (WinHttpReadData(spc_request, buffer, size, &downloaded))
                        response.append(buffer, downloaded);

                    delete[] buffer;
                }

                while (size > 0);

                HTTP_Response http_response;

                if (http_response.Parse_Response(response)) {
                    http_response.Log_Response();
                    result = http_response.success;
                }
                else
                    Log_Printf("[SPC Integration]: Server Error: Failed to parse server response: '%s'.", response.c_str());
            }
        }
        else {
            DWORD error = GetLastError();
            Log_Printf("[SPC Integration]: Server Error: Failed to send request. Error code: '%lu'.", error);
        }

        if (spc_request)
            WinHttpCloseHandle(spc_request);

        if (spc_connect)
            WinHttpCloseHandle(spc_connect);

        if (spc_session)
            WinHttpCloseHandle(spc_session);

        return result;
    }
#endif