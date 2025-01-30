#include "http_client.h"

bool HTTP_Client::Send_Request(const std::string& host, const std::string& path, const std::string& data, const std::string& action) {
    #ifdef _WIN32
        std::wstring w_host(host.begin(), host.end());
        std::wstring w_path = std::wstring(path.begin(), path.end()) + L"?action=" + std::wstring(action.begin(), action.end());

        return Send_Request_Windows(w_host, w_path, data);
    #else
        std::string fullPath = path + "?action=" + action;

        return Send_Request_Linux(host, fullPath, data);
    #endif
}