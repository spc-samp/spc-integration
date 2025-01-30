#ifndef SERVER_INFO_H
    #define SERVER_INFO_H

    #include "inclusions.h"

    enum class Config_Status {
        Success,
        Not_Found,
        Empty,
        Web_Not_Found,
        Web_Empty
    };

    class Server_Info {
        public:
            std::string ip;
            std::string port;
            std::string image_url;
            std::string web_url;
            Config_Status image_config_status;
            Config_Status web_config_status;

            Server_Info() : port("7777"), image_config_status(Config_Status::Not_Found), web_config_status(Config_Status::Web_Not_Found) {}

            const char* Get_Config_File_Name() const;

            bool Initialize() {
                if (!Get_Server_IP())
                    return false;

                Get_Server_Port();
                Get_Image_URL();
                Get_Web_URL();

                return true;
            }

        private:
            bool Get_Server_IP();
            bool Get_Server_Port();
            bool Get_Image_URL();
            bool Get_Web_URL();
        };
#endif