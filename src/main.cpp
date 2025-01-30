#include "inclusions.h"
#include "amx_defines.h"
#include "base64_encoder.h"
#include "http_client.h"
#include "logger.h"
#include "plugin_defines.h"
#include "server_info.h"
#include "url_validator.h"

#ifdef _WIN32
    #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
    #pragma comment(linker, "/EXPORT:Load=_Load@4")
    #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
    #pragma comment(linker, "/EXPORT:AmxLoad=_AmxLoad@4")
    #pragma comment(linker, "/EXPORT:AmxUnload=_AmxUnload@4")
#endif

AMX_Get_String_t AMX_Get_String_Ptr = nullptr;
AMX_Register_t AMX_Register_Ptr = nullptr;
AMX_Set_String_t AMX_Set_String_Ptr = nullptr;
AMX_String_Len_t AMX_String_Len_Ptr = nullptr;
AMX_Get_Addr_t AMX_Get_Addr_Ptr = nullptr;

Server_Info SPC_Server_Info;
Log_Printf_t Log_Printf = nullptr;

bool Send_ToBackend(const Server_Info& info, const char* action) {
    std::string post_data = "api_key=" + std::string(API_KEY) +  "&server_ip=" + info.ip + "&server_port=" + info.port;

    if ((strcmp(action, "create") == 0 || strcmp(action, "update") == 0) && !info.image_url.empty()) {
        std::string encoded_URL = Base64_Encoder::Encode(info.image_url);
        post_data += "&image_url=" + encoded_URL + "&encoded=true";
    }

    if ((strcmp(action, "create") == 0 || strcmp(action, "update") == 0) && !info.web_url.empty()) {
        std::string encoded_URL = Base64_Encoder::Encode(info.web_url);
        post_data += "&web_url=" + encoded_URL + "&encoded=true";
    }

    Log_Printf(" ");
    Log_Printf("[SPC Integration]: Trying to execute function '%s' for server data...", action);

    bool result = HTTP_Client::Send_Request(BACKEND_HOST, BACKEND_PATH, post_data, action);

    if (!result) {
        if (strcmp(action, "create") == 0)
            return Send_ToBackend(info, "update");
    }

    return result;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** Plugin_Data) {
    Log_Printf = (Log_Printf_t)Plugin_Data[PLUGIN_DATA_LOGPRINTF];

    Log_Printf(" ");
    Log_Printf("[SPC Integration]: Initializing plugin...");

    void** AMX_Exports = (void**)Plugin_Data[PLUGIN_DATA_AMX_EXPORTS];
    AMX_Get_String_Ptr = (AMX_Get_String_t)AMX_Exports[PLUGIN_AMX_EXPORT_GetString];
    AMX_Register_Ptr = (AMX_Register_t)AMX_Exports[PLUGIN_AMX_EXPORT_Register];
    AMX_Set_String_Ptr = (AMX_Set_String_t)AMX_Exports[PLUGIN_AMX_EXPORT_SetString];
    AMX_String_Len_Ptr = (AMX_String_Len_t)AMX_Exports[PLUGIN_AMX_EXPORT_StrLen];
    AMX_Get_Addr_Ptr = (AMX_Get_Addr_t)AMX_Exports[PLUGIN_AMX_EXPORT_GetAddr];

    if (!SPC_Server_Info.Initialize()) {
        Log_Printf(" ");
        Log_Printf("[SPC Integration]: Server Error: Failed to initialize server info.");
        Log_Printf("[SPC Integration]: Please check your network configuration.");
        Log_Printf(" ");

        return false;
    }

    Log_Printf("\n");
    Log_Printf("+================================================================+");
    Log_Printf("|                                                                |");
    Log_Printf("|                        spc-integration                         |");
    Log_Printf("|                     ---------------------                      |");
    Log_Printf("|                                                                |");
    Log_Printf("|                  SA-MP Programming Community                   |");
    Log_Printf("|                                                                |");
    Log_Printf("|----------------------------------------------------------------|");
    Log_Printf("|                                                                |");
    Log_Printf("|  [Social]                                                      |");
    Log_Printf("|    * GitHub: https://github.com/spc-samp                       |");
    Log_Printf("|    * Discord: https://discord.gg/3fApZh66Tf                    |");
    Log_Printf("|    * Instagram: https://instagram.com/spc.samp                 |");
    Log_Printf("|    * YouTube: https://youtube.com/@spc-samp                    |");
    Log_Printf("|    * TikTok: https://tiktok.com/@spc.samp                      |");
    Log_Printf("|                                                                |");
    Log_Printf("|----------------------------------------------------------------|");
    Log_Printf("|                                                                |");
    Log_Printf("|  [Plugin Info]                                                 |");
    Log_Printf("|    * Developer: Calasans                                       |");
    Log_Printf("|    * Version: %-48s |", PLUGIN_VERSION);
    Log_Printf("|                                                                |");
    Log_Printf("+================================================================+");

    const char* config_file = SPC_Server_Info.Get_Config_File_Name();

    if (SPC_Server_Info.image_config_status != Config_Status::Success) {
        Log_Printf(" ");
        
        if (SPC_Server_Info.image_config_status == Config_Status::Not_Found) {
            Log_Printf("[SPC Integration]: Validation Error: 'spc_integration_image' parameter not found in '%s'.", config_file);
            Log_Printf("[SPC Integration]: The 'spc_integration_image' parameter must be added to '%s'.", config_file);
        }
        else if (SPC_Server_Info.image_config_status == Config_Status::Empty) {
            Log_Printf("[SPC Integration]: Validation Error: 'spc_integration_image' parameter is empty in '%s'.", config_file);
            Log_Printf("[SPC Integration]: The 'spc_integration_image' parameter must contain a valid URL in '%s'.", config_file);
        }

        Log_Printf("[SPC Integration]: Plugin will not be loaded.");
        Log_Printf(" ");

        return false;
    }

    if (SPC_Server_Info.web_config_status != Config_Status::Success) {
        Log_Printf(" ");

        if (SPC_Server_Info.web_config_status == Config_Status::Web_Not_Found) {
            const char* web_param = (std::string(config_file) == CONFIG_FILE_SAMP) ? "weburl" : "website";

            Log_Printf("[SPC Integration]: Validation Error: '%s' parameter not found in '%s'.", web_param, config_file);
            Log_Printf("[SPC Integration]: The '%s' parameter must be added to '%s'.", web_param, config_file);
        }
        else if (SPC_Server_Info.web_config_status == Config_Status::Web_Empty) {
            const char* web_param = (std::string(config_file) == CONFIG_FILE_SAMP) ? "weburl" : "website";

            Log_Printf("[SPC Integration]: Validation Error: '%s' parameter is empty in '%s'.", web_param, config_file);
            Log_Printf("[SPC Integration]: The '%s' parameter must contain a valid URL in '%s'.", web_param, config_file);
        }

        Log_Printf("[SPC Integration]: Plugin will not be loaded.");
        Log_Printf(" ");

        return false;
    }

    if (!URL_Validator::Is_Valid(SPC_Server_Info.image_url)) {
        Log_Printf(" ");
        Log_Printf("[SPC Integration]: Plugin will not be loaded.");
        Log_Printf(" ");

        return false;
    }

    bool success = Send_ToBackend(SPC_Server_Info, "create");

    if (!success)
        success = Send_ToBackend(SPC_Server_Info, "update");

    if (!success) {
        Log_Printf(" ");
        Log_Printf("[SPC Integration]: Server error: Failed to initialize server data. Please report this issue to the (SPC Team).");
        Log_Printf("[SPC Integration]: Please check your configuration and try again.");
        Log_Printf("[SPC Integration]: Please make sure your API key and server settings are correct. Please report this issue to the (SPC Team).");
        Log_Printf(" ");

        return false;
    }

    Log_Printf(" ");
    Log_Printf("[SPC Integration]: Information sent to the server data storage of the SPC:");
    Log_Printf("-- Server IP: '%s'.", SPC_Server_Info.ip.c_str());
    Log_Printf("-- Server Port: '%s'.", SPC_Server_Info.port.c_str());
    Log_Printf("-- Image URL configured: '%s'.", SPC_Server_Info.image_url.c_str());
    Log_Printf("-- Web URL configured: '%s'.", SPC_Server_Info.web_url.c_str());
    Log_Printf(" ");

    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    Log_Printf(" ");
    Log_Printf("[SPC Integration]: Plugin unloaded successfully.");
    Log_Printf(" ");
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* Amx) {
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* Amx) {
    return AMX_ERR_NONE;
}