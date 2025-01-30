#include "http_response.h"
#include "logger.h"

void HTTP_Response::Log_Response() const {
    const char* prefix = "[SPC Integration]:";
    
    if (success) {
        Log_Printf("%s %s", prefix, message.c_str());

        return;
    }
    
    const char* error_prefix = nullptr;
    
    if (type == "Server")
        error_prefix = "Server Configuration Error";
    else if (type == "Validation")
        error_prefix = "Input Validation Error";
    else if (type == "Authentication")
        error_prefix = "API Authentication Error";
    else if (type == "File")
        error_prefix = "File Operation Error";
    else if (type == "Method")
        error_prefix = "HTTP Method Error";
    else if (type == "Route")
        error_prefix = "API Route Error";
    else
        error_prefix = "Unknown Error";
    
    Log_Printf("%s %s: %s", prefix, error_prefix, message.c_str());
    
    if (type == "Server")
        Log_Printf("%s Please check your server configuration and permissions.", prefix);
    else if (type == "Authentication")
        Log_Printf("%s Please verify your API key in 'plugin_defines.h'.", prefix);
    else if (type == "Validation")
        Log_Printf("%s Please check your server.cfg settings.", prefix);
}

bool HTTP_Response::Parse_Response(const std::string& json) {
    size_t sucess_pos = json.find("\"success\":");
    size_t message_pos = json.find("\"message\":\"");
    
    if (sucess_pos == std::string::npos || message_pos == std::string::npos) {
        success = false;
        message = "Invalid JSON response from server";
        type = "Server";

        return false;
    }

    success = (json.find("true", sucess_pos) != std::string::npos);
    
    size_t message_start = message_pos + 11;
    size_t message_end = message_start;
    bool found_end = false;
    
    while (message_end < json.length()) {
        message_end = json.find("\"", message_end);

        if (message_end == std::string::npos)
            break;
        
        if (message_end > 0 && json[message_end - 1] != '\\') {
            found_end = true;
            break;
        }

        message_end++;
    }
    
    if (!found_end) {
        success = false;
        message = "Malformed response message";
        type = "Server";

        return false;
    }

    message = json.substr(message_start, message_end - message_start);
    
    size_t pos = 0;

    while ((pos = message.find("\\\"", pos)) != std::string::npos) {
        message.replace(pos, 2, "\"");
        pos++;
    }
    
    if (message.find("Server Error:") != std::string::npos)
        type = "Server";
    else if (message.find("Validation Error:") != std::string::npos)
        type = "Validation";
    else if (message.find("Authentication Error:") != std::string::npos)
        type = "Authentication";
    else if (message.find("File error:") != std::string::npos)
        type = "File";
    else if (message.find("Method Error:") != std::string::npos)
        type = "Method";
    else if (message.find("Route Error:") != std::string::npos)
        type = "Route";
    else if (success)
        type = "Success";
    else
        type = "Unknown";

    return true;
}