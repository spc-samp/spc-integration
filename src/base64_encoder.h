#ifndef BASE64_ENCODER_H
    #define BASE64_ENCODER_H

    #include <string>

    class Base64_Encoder {
        public:
            static std::string Encode(const std::string& input);
        private:
            static const std::string base64_chars;
        };
#endif