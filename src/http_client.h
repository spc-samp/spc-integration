#ifndef HTTP_CLIENT_H
    #define HTTP_CLIENT_H

    #include "inclusions.h"

    class HTTP_Client {
        public:
            static bool Send_Request(const std::string& host, const std::string& path,
                const std::string& data, const std::string& action);
        private:
            #ifdef _WIN32
                static bool Send_Request_Windows(const std::wstring& host, const std::wstring& path,
                    const std::string& data);
            #else
                static bool Send_Request_Linux(const std::string& host, const std::string& path,
                    const std::string& data);
            #endif
    };
#endif