#ifndef HTTP_RESPONSE_H
    #define HTTP_RESPONSE_H

    #include "inclusions.h"

    class HTTP_Response {
        public:
            std::string message;
            std::string type;
            bool success = false;
    
            void Log_Response() const;
            bool Parse_Response(const std::string& json);
    };
#endif