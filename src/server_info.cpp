#include "plugin_defines.h"
#include "server_info.h"
#include "url_validator.h"

bool File_Exists(const char* filename) {
    std::ifstream file(filename);

    return file.good();
}

std::string Extract_Quoted_String(const std::string& str) {
    size_t first = str.find('\"');

    if (first == std::string::npos)
        return "";

    size_t second = str.find('\"', first + 1);

    if (second == std::string::npos)
        return "";

    return str.substr(first + 1, second - first - 1);
}

const char* Server_Info::Get_Config_File_Name() const {
    if (File_Exists(CONFIG_FILE_SAMP))
        return CONFIG_FILE_SAMP;

    if (File_Exists(CONFIG_FILE_OPEN))
        return CONFIG_FILE_OPEN;

    return CONFIG_FILE_SAMP;
}

bool Server_Info::Get_Server_IP() {
    #ifdef _WIN32
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            return false;

        char hostname[256];

        if (gethostname(hostname, sizeof(hostname)) == 0) {
            struct addrinfo hints;
            struct addrinfo* result = nullptr;
            ZeroMemory(&hints, sizeof(hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;

            if (getaddrinfo(hostname, NULL, &hints, &result) == 0) {
                struct sockaddr_in* addr = (struct sockaddr_in*)result->ai_addr;
            
                char ip_buffer[INET_ADDRSTRLEN];

                if (InetNtop(AF_INET, &(addr->sin_addr), ip_buffer, sizeof(ip_buffer)) != NULL) {
                    ip = ip_buffer;
                    freeaddrinfo(result);
                    WSACleanup();

                    return true;
                }

                freeaddrinfo(result);
                WSACleanup();
            }
        }
    #else
        struct ifaddrs* ifaddr = nullptr;
        struct ifaddrs* ifa = nullptr;
    
        if (getifaddrs(&ifaddr) == -1)
            return false;

        for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == nullptr)
                continue;

            if (ifa->ifa_addr->sa_family == AF_INET && strcmp(ifa->ifa_name, "lo") != 0) {
                struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
                ip = inet_ntoa(addr->sin_addr);
                freeifaddrs(ifaddr);

                return true;
            }
        }

        freeifaddrs(ifaddr);
    #endif

    return false;
}

bool Server_Info::Get_Server_Port() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        std::ifstream config(CONFIG_FILE_SAMP);

        if (!config.is_open())
            return false;

        std::string line;

        while (std::getline(config, line)) {
            line.erase(0, line.find_first_not_of(" \t"));

            if (line.empty() || line[0] == ';' || line[0] == '#')
                continue;

            if (line.find("port") == 0) {
                std::istringstream iss(line);
                std::string key;
                iss >> key >> port;

                return true;
            }
        }
    }

    else if (File_Exists(CONFIG_FILE_OPEN)) {
        std::ifstream config(CONFIG_FILE_OPEN);

        if (!config.is_open())
            return false;

        std::string json_content((std::istreambuf_iterator<char>(config)),
            std::istreambuf_iterator<char>());

        size_t network_pos = json_content.find("\"network\"");

        if (network_pos == std::string::npos)
            return false;

        size_t port_pos = json_content.find("\"port\":", network_pos);

        if (port_pos == std::string::npos)
            return false;

        size_t value_start = json_content.find_first_of("0123456789", port_pos);

        if (value_start == std::string::npos)
            return false;

        size_t value_end = json_content.find_first_not_of("0123456789", value_start);

        if (value_end == std::string::npos)
            value_end = json_content.length();

        port = json_content.substr(value_start, value_end - value_start);

        return true;
    }

    return false;
}

bool Server_Info::Get_Image_URL() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        std::ifstream config(CONFIG_FILE_SAMP);

        if (!config.is_open())
            return false;

        std::string line;
        bool found_config_line = false;

        while (std::getline(config, line)) {
            line.erase(0, line.find_first_not_of(" \t"));

            if (line.empty() || line[0] == ';' || line[0] == '#')
                continue;

            if (line.find("spc_integration_image") == 0) {
                found_config_line = true;
                std::string key;
                std::istringstream iss(line);
                iss >> key;
                std::getline(iss, image_url);
                image_url.erase(0, image_url.find_first_not_of(" \t"));
                image_url.erase(image_url.find_last_not_of(" \t") + 1);

                if (!image_url.empty())
                    image_config_status = Config_Status::Success;
                else
                    image_config_status = Config_Status::Empty;

                return image_config_status == Config_Status::Success;
            }
        }

        image_config_status = Config_Status::Not_Found;

        return false;
    }

    else if (File_Exists(CONFIG_FILE_OPEN)) {
        std::ifstream config(CONFIG_FILE_OPEN);

        if (!config.is_open())
            return false;

        std::string json_content((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());

        size_t url_pos = json_content.find("\"spc_integration_image\"");

        if (url_pos == std::string::npos) {
            image_config_status = Config_Status::Not_Found;
            return false;
        }

        size_t value_start = json_content.find('\"', url_pos + std::string("\"spc_integration_image\"").length());

        if (value_start == std::string::npos) {
            image_config_status = Config_Status::Not_Found;
            return false;
        }

        size_t value_end = json_content.find('\"', value_start + 1);

        if (value_end == std::string::npos) {
            image_config_status = Config_Status::Not_Found;
            return false;
        }

        image_url = json_content.substr(value_start + 1, value_end - value_start - 1);

        image_url.erase(0, image_url.find_first_not_of(" \t"));
        image_url.erase(image_url.find_last_not_of(" \t") + 1);

        if (!image_url.empty())
            image_config_status = Config_Status::Success;
        else
            image_config_status = Config_Status::Empty;

        return true;
    }

    image_config_status = Config_Status::Not_Found;

    return false;
}

bool Server_Info::Get_Web_URL() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        std::ifstream config(CONFIG_FILE_SAMP);

        if (!config.is_open())
            return false;

        std::string line;
        bool found_config_line = false;

        while (std::getline(config, line)) {
            line.erase(0, line.find_first_not_of(" \t"));

            if (line.empty() || line[0] == ';' || line[0] == '#')
                continue;

            if (line.find("weburl") == 0) {
                found_config_line = true;
                std::string key;
                std::istringstream iss(line);
                iss >> key;
                std::getline(iss, web_url);
                web_url.erase(0, web_url.find_first_not_of(" \t"));
                web_url.erase(web_url.find_last_not_of(" \t") + 1);

                if (!web_url.empty())
                    web_config_status = Config_Status::Success;
                else
                    web_config_status = Config_Status::Web_Empty;

                return true;
            }
        }

        web_config_status = Config_Status::Web_Not_Found;

        return false;
    }
    
    else if (File_Exists(CONFIG_FILE_OPEN)) {
        std::ifstream config(CONFIG_FILE_OPEN);

        if (!config.is_open())
            return false;

        std::string json_content((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());

        size_t url_pos = json_content.find("\"website\"");

        if (url_pos == std::string::npos) {
            web_config_status = Config_Status::Web_Not_Found;
            return false;
        }

        size_t value_start = json_content.find('\"', url_pos + std::string("\"website\"").length());

        if (value_start == std::string::npos) {
            web_config_status = Config_Status::Web_Not_Found;
            return false;
        }

        size_t value_end = json_content.find('\"', value_start + 1);

        if (value_end == std::string::npos) {
            web_config_status = Config_Status::Web_Not_Found;
            return false;
        }

        web_url = json_content.substr(value_start + 1, value_end - value_start - 1);

        web_url.erase(0, web_url.find_first_not_of(" \t"));
        web_url.erase(web_url.find_last_not_of(" \t") + 1);

        if (!web_url.empty())
            web_config_status = Config_Status::Success;
        else
            web_config_status = Config_Status::Web_Empty;

        return true;
    }

    web_config_status = Config_Status::Web_Not_Found;

    return false;
}