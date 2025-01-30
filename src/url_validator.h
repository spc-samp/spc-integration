#ifndef URL_VALIDATOR_H
    #define URL_VALIDATOR_H

    #include "inclusions.h"

    class URL_Validator {
        public:
            static bool Is_Valid(const std::string& url);
        private:
            static bool Validate_With_Timeout(const std::string& url);
            static bool Perform_Full_Validation(const std::string& url);
            static bool Has_Valid_Scheme(const std::string& url);
            static bool Has_Valid_HostAndPath(const std::string& url);
            static bool Has_Valid_Characters(const std::string& url);
            static bool Validate_Image_Headers(const std::string& url);
            static bool Check_Image_Magic_Numbers(const std::vector<unsigned char>& data);
    
            #ifdef _WIN32
                static bool Fetch_Image_Data_Windows(const std::wstring& host, const std::wstring& path, std::vector<unsigned char>& data);
            #else
                static bool Fetch_Image_Data_Linux(const std::string& host, const std::string& path, std::vector<unsigned char>& data);
            #endif

            static const int VALIDATION_TIMEOUT = 10;
            static const size_t MAX_HEADER_SIZE = 16;
    };
#endif