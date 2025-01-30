# spc-integration

The **SPC Integration** is a plugin developed for SA-MP (San Andreas Multiplayer) and open.mp (Open Multiplayer) that collects information from the server, such as IP, port, website URL, and a configurable image URL. This information is sent to the SPC (SA-MP Programming Community) website, where server information is stored.

## Languages

- Deutsch: [README](translations/Deutsch/README.md)
- English: [README](translations/English/README.md)
- Español: [README](translations/Espanol/README.md)
- Français: [README](translations/Francais/README.md)
- Italiano: [README](translations/Italiano/README.md)
- Polski: [README](translations/Polski/README.md)
- Русский: [README](translations/Русский/README.md)
- Svenska: [README](translations/Svenska/README.md)
- Türkçe: [README](translations/Turkce/README.md)

## Index

- [spc-integration](#spc-integration)
  - [Languages](#languages)
  - [Index](#index)
  - [Main Features](#main-features)
    - [1. Server Information Collection](#1-server-information-collection)
    - [2. URL Validation](#2-url-validation)
    - [3. Backend Integration](#3-backend-integration)
    - [4. Cross-Platform Compatibility](#4-cross-platform-compatibility)
  - [How to Use the Plugin](#how-to-use-the-plugin)
    - [1. Download](#1-download)
    - [2. Installation](#2-installation)
    - [3. Configuration](#3-configuration)
    - [4. Verification](#4-verification)
  - [Project Structure](#project-structure)
  - [Code Details](#code-details)
    - [1. Server Information Collection](#1-server-information-collection-1)
      - [Main Structure](#main-structure)
      - [Server IP Collection](#server-ip-collection)
      - [Server Port Reading](#server-port-reading)
      - [Image and Website URLs](#image-and-website-urls)
      - [Configuration Status](#configuration-status)
      - [Initialization](#initialization)
      - [Main Features](#main-features-1)
    - [2. Image URL Validation](#2-image-url-validation)
      - [Architecture Overview](#architecture-overview)
      - [Timeout Protected Validation](#timeout-protected-validation)
      - [Complete Validation Pipeline](#complete-validation-pipeline)
      - [URL Component Validation](#url-component-validation)
      - [Image Content Validation](#image-content-validation)
      - [Cross-Platform Implementation](#cross-platform-implementation)
      - [Main Features](#main-features-2)
    - [3. HTTP Client](#3-http-client)
      - [Structure and Functioning](#structure-and-functioning)
      - [Windows Implementation (WinHTTP)](#windows-implementation-winhttp)
      - [Linux Implementation (OpenSSL)](#linux-implementation-openssl)
      - [Response Processing](#response-processing)
      - [Main Features](#main-features-3)
    - [4. Base64 Encoding](#4-base64-encoding)
      - [Interface Definition](#interface-definition)
      - [Base64 Alphabet and Implementation](#base64-alphabet-and-implementation)
      - [Initialization and Buffers](#initialization-and-buffers)
      - [Main Encoding Loop](#main-encoding-loop)
      - [Padding Handling](#padding-handling)
      - [Main Features](#main-features-4)
    - [5. Logging](#5-logging)
      - [Interface Definition](#interface-definition-1)
      - [Function Type Definition](#function-type-definition)
      - [Function Pointer Declaration](#function-pointer-declaration)
      - [Main Features](#main-features-5)
    - [6. Plugin Entry Point](#6-plugin-entry-point)
      - [Main Entry Functions](#main-entry-functions)
    - [7. Definitions and Inclusions](#7-definitions-and-inclusions)
      - [Plugin Definitions](#plugin-definitions)
      - [Base Structure of Inclusions](#base-structure-of-inclusions)
      - [Windows-Specific Inclusions](#windows-specific-inclusions)
      - [Unix/Linux-Specific Inclusions](#unixlinux-specific-inclusions)
      - [Main Features](#main-features-6)
  - [Back-End](#back-end)
    - [1. Data Reception](#1-data-reception)
    - [2. Request Validation](#2-request-validation)
    - [3. Directory Validation](#3-directory-validation)
    - [4. URL Processing](#4-url-processing)
    - [5. Data Storage](#5-data-storage)
    - [6. JSON File Format](#6-json-file-format)
    - [7. Backup System](#7-backup-system)
    - [8. Error Handling](#8-error-handling)
  - [Important Definitions](#important-definitions)
    - [1. BACKEND\_HOST and BACKEND\_PATH](#1-backend_host-and-backend_path)
    - [2. upload\_dir in Backend](#2-upload_dir-in-backend)
    - [Security and Privacy](#security-and-privacy)
  - [Compilation](#compilation)
    - [Compilation for Windows](#compilation-for-windows)
      - [1. Requirements](#1-requirements)
      - [2. Compilation Steps](#2-compilation-steps)
        - [2-1. Opening the Project in Visual Studio](#2-1-opening-the-project-in-visual-studio)
        - [2-2. Configuring the Project](#2-2-configuring-the-project)
        - [2-3. Compiling the Project](#2-3-compiling-the-project)
      - [2-4. Verifying the Compilation](#2-4-verifying-the-compilation)
    - [Compilation for Linux](#compilation-for-linux)
      - [1. Requirements](#1-requirements-1)
      - [2. Compilation Steps](#2-compilation-steps-1)
        - [2-1. Building the Docker Image](#2-1-building-the-docker-image)
        - [2-2. `build.sh`](#2-2-buildsh)
        - [2-3. Building the Plugin](#2-3-building-the-plugin)
        - [2-4. `compile.sh`](#2-4-compilesh)
      - [3. Dockerfile](#3-dockerfile)

## Main Features

### 1. Server Information Collection
   - The plugin automatically collects the IP and port of the running server.
   - Identifies whether the server is SA-MP or open.mp and collects the corresponding website URL, if available.
   - Allows configuration of a custom image URL through the `spc_integration_image` parameter, which must be added to the server's configuration file.

### 2. URL Validation
   - Before sending the image URL to the backend, the plugin validates whether the provided URL is accessible and corresponds to a valid image format (JPEG, PNG, GIF, etc.).
   - This ensures that only valid image URLs are sent, avoiding unnecessary creations or updates in the JSON.

### 3. Backend Integration
   - The plugin sends the collected information to a backend via an HTTP POST request.
   - The backend validates the request, ensuring that the provided `API_KEY` matches the key configured in the backend. This is crucial for security, as it prevents unauthorized requests from being processed.
   - If the data is valid, the backend creates a JSON file in the format `IP-Port.json`, storing the server information.

### 4. Cross-Platform Compatibility
   - Supports compilation for Linux (using Docker, CMake, and GCC 8) and Windows (using Visual Studio 2022).
   - Works for both SA-MP and open.mp, allowing all servers to use the plugin.

## How to Use the Plugin

### 1. Download

- Download the latest version of the plugin from the [releases](https://github.com/spc-samp/spc-integration/releases) section.
- Choose the appropriate file for your operating system:
  - Windows: `spc-integration.dll`
  - Linux: `spc-integration.so`

### 2. Installation

1. Extract the downloaded file.
2. Place the plugin in the `plugins` folder of your server.
3. Configure the server to load the plugin:
   - **For SA-MP**: Add to your `server.cfg`:
     ```
     plugins spc-integration
     ```
   - **For open.mp**: Add `"spc-integration"` to the `legacy_plugins` list in your `config.json`:
     ```json
     {
         "pawn": {
             "legacy_plugins": [
             "spc-integration"
             ]
         }
     }
     ```
> [!WARNING]  
> If you already have other plugins installed, make sure to load spc-integration after them.

### 3. Configuration

You need to configure the image URL that will be displayed for your server. Choose one of the options below according to your platform:

- **1. server.cfg (SA-MP)**
    ```
    spc_integration_image https://example.com/image.png
    ```

- **2. config.json (open.mp)**
    ```json
    {
        "spc_in tegration_image": "https://example.com/image.png"
    }
    ```

> [!IMPORTANT]
> The image URL must be valid and publicly accessible.

### 4. Verification

1. Start your server.
2. Check the server logs. If you see a message similar to this, the plugin is working correctly:
    ```
    [SPC Integration]: Information sent to the server data storage of the SPC:
    -- Server IP: '127.0.0.1'
    -- Server Port: '7777'
    -- Image URL configured: 'https://example.com/image.png'
    -- Web URL configured: 'https://example.com'
    ```

## Project Structure

The project structure is organized as follows:
```
└── src/
    ├── cmake/
    │   ├── CMakeLists.txt               // CMake configuration file
    │   └── compile.sh                   // Compilation script for Linux
    │
    ├── docker/
    │   ├── build.sh                     // Script to build the Docker image
    │   └── Dockerfile                   // Docker file for Linux compilation
    │
    ├── sdk/
    │   └── (SA-MP SDK)                  // SDK required for plugin development
    │
    ├── amx_defines.h                    // AMX related definitions
    ├── base64_encoder.cpp               // Base64 encoder implementation
    ├── base64_encoder.h                 // Base64 encoder header
    ├── http_client.cpp                  // HTTP client implementation
    ├── http_client.h                    // HTTP client header
    ├── http_linux.cpp                   // Linux specific HTTP client implementation
    ├── http_response.cpp                // HTTP response implementation
    ├── http_response.h                  // HTTP response header
    ├── http_windows.cpp                 // Windows specific HTTP client implementation
    ├── inclusions.h                     // Common inclusions and global definitions
    ├── logger.h                         // Logging header
    ├── main.cpp                         // Plugin entry point
    ├── plugin_defines.h                 // Plugin specific definitions
    ├── server_info.cpp                  // Server information collection implementation
    ├── server_info.h                    // Server information collection header
    ├── spc-integration.sln              // Visual Studio solution file
    ├── spc-integration.vcxproj          // Visual Studio project file
    ├── spc-integration.vcxproj.filters  // Visual Studio project filters configuration
    ├── url_validator.cpp                // URL validator implementation
    └── url_validator.h                  // URL validator header
```

## Code Details

Below is a detailed analysis of the main components of the **SPC Integration** code. Each section of the code is explained in depth to understand the plugin's functioning and its integration with the backend.

### 1. Server Information Collection

| **Files**          |
|---------------------|
| `server_info.h`     |
| `server_info.cpp`   |

- The `Server_Info` class is responsible for collecting and managing essential server information, including IP, port, integration URLs, and website. The system supports two configuration file formats: server.cfg (SA-MP) and config.json (open.mp).

#### Main Structure

```cpp
class Server_Info {
    public:
        std::string ip;
        std::string port;
        std::string image_url;
        std::string web_url;
        Config_Status image_config_status;
        Config_Status web_config_status;

        Server_Info() : port("7777"), image_config_status(Config_Status::Not_Found), web_config_status(Config_Status::Web_Not_Found) {}
};
```

#### Server IP Collection

```cpp
bool Server_Info::Get_Server_IP() {
    #ifdef _WIN32
        // Windows: Uses WinSock API
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            return false;
            
        char hostname[256];

        if (gethostname(hostname, sizeof(hostname)) == 0) {
            // Code to get IP on Windows
            // ...
        }
    #else
        // Linux: Uses getifaddrs
        struct ifaddrs* ifaddr = nullptr;

        for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr->sa_family == AF_INET && strcmp(ifa->ifa_name, "lo") != 0) {
                struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
                ip = inet_ntoa(addr->sin_addr);

                return true;
            }
        }
    #endif

    return false;
}
```

#### Server Port Reading

```cpp
bool Server_Info::Get_Server_Port() {
    ```cpp
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Reads from the server.cfg file (SA-MP)
        std::ifstream config(CONFIG_FILE_SAMP);
        std::string line;

        while (std::getline(config, line)) {
            if (line.find("port") == 0) {
                std::istringstream iss(line);
                std::string key;
                iss >> key >> port;
                return true;
            }
        }
    }
    else if (File_Exists(CONFIG_FILE_OPEN)) {
        // Reads from the config.json file (open.mp)
        std::ifstream config(CONFIG_FILE_OPEN);
        std::string json_content((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
        // Processes JSON to find the port
        // ...
    }
    return false;
}
```

#### Image and Website URLs

The system manages two types of URLs:
1. Image URL (`image_url`): Address of the server's image URL.
2. Website URL (`web_url`): Address of the server's website.

```cpp
bool Server_Info::Get_Image_URL() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Looks for "spc_integration_image" in the file
        if (/* URL found */)
            image_config_status = Config_Status::Success;
        else
            image_config_status = Config_Status::Empty;
    }
    // Similar for CONFIG_FILE_OPEN
}

bool Server_Info::Get_Web_URL() {
    // Similar process to Get_ImageURL(), but looks for "weburl" or "website"
}
```

#### Configuration Status

The system uses enumerations to control the status of configurations:

```cpp
enum class Config_Status {
    Success,        // Configuration found and valid
    Not_Found,      // Configuration not found
    Empty,          // Configuration found but empty
    Web_Not_Found,  // Website URL not found
    Web_Empty       // Website URL empty
};
```

#### Initialization

The initialization process is managed by the `Initialize()` method:

```cpp
bool Initialize() {
    if (!Get_Server_IP())
        return false;

    Get_Server_Port();
    Get_Image_URL();
    Get_Web_URL();

    return true;
}
```

#### Main Features

1. **Information Collection**:
    - Automatic detection of the server's IP.
    - Reading of the configured port.
    - Support for image and website URLs.
    - Validation of all collected information.

2. **Compatibility**:
    - Support for multiple operating systems.
    - Compatibility with SA-MP and open.mp.
    - Reading of different configuration formats.

3. **State Management**:
    - Robust status system for configurations.
    - Granular error and state control.
    - Individualized validation of each component.

4. **Data Processing**:
    - Automatic string cleaning.
    - Detection and removal of whitespace.
    - Validation of URLs and configurations.

### 2. Image URL Validation

| **Files**          |
|---------------------|
| `url_validator.h`   |
| `url_validator.cpp` |

- The URL validation system is a critical security component that performs comprehensive validation of image URLs through multiple layers of checks. It not only validates the URL format but also checks if the URL points to a valid image file.

#### Architecture Overview

The validation process is implemented in the `URL_Validator` class and follows a multi-stage validation pipeline:

- **Initial Validation** (`Is_Valid`).
- **Timeout Management** (`Validate_With_Timeout`).
- **Complete Validation Process** (`Perform_Full_Validation`).
- **Image Content Verification** (`Validate_Image_Headers`).

#### Timeout Protected Validation

```cpp
bool URL_Validator::Is_Valid(const std::string& url) {
    Log_Printf(" ");
    Log_Printf("[SPC Integration]: Starting full validation of the image URL...");

    return Validate_With_Timeout(url);
}

bool URL_Validator::Validate_With_Timeout(const std::string& url) {
    auto future = std::async(std::launch::async, [&url]() {
        return Perform_Full_Validation(url);
    });

    if (future.wait_for(std::chrono::seconds(VALIDATION_TIMEOUT)) == std::future_status::timeout)
        return (Log_Printf("[SPC Integration]: Error: Timeout during URL validation after '%d' seconds.", VALIDATION_TIMEOUT), false);
    // ... exception handling
}
```

- The system implements a timeout mechanism using `std::async` to avoid hanging on slow or unresponsive URLs. The validation process will automatically fail if it exceeds `VALIDATION_TIMEOUT` seconds (set to 10 seconds in the code).

#### Complete Validation Pipeline

The `Perform_Full_Validation` method implements a series of checks:

```cpp
bool URL_Validator::Perform_Full_Validation(const std::string& url) {
    // Length validation
    if (url.empty() || url.length() > 2048)
        return (Log_Printf("[SPC Integration]: Error: URL is empty or too long (maximum 2048 characters)."), false);

    // Protocol validation
    if (!Has_Valid_Scheme(url))
        return (Log_Printf("[SPC Integration]: Error: URL must start with 'http://' or 'https://'."), false);

    // Structure validation
    if (!Has_Valid_HostAndPath(url))
        return (Log_Printf("[SPC Integration]: Error: URL must contain a valid hostname and path."), false);

    // Character validation
    if (!Has_Valid_Characters(url))
        return (Log_Printf("[SPC Integration]: Error: URL contains invalid characters."), false);

    // Image validation
    if (!Validate_Image_Headers(url))
        return (Log_Printf("[SPC Integration]: Error: The URL content is not a valid image."), false);

    Log_Printf("[SPC Integration]: Validation successfully completed!");

    return true;
}
```

#### URL Component Validation

The system includes specialized validators for different components of the URL:

```cpp
bool URL_Validator::Has_Valid_Scheme(const std::string& url) {
    return (url.substr(0, 7) == "http://" || url.substr(0, 8) == "https://");
}

bool URL_Validator::Has_Valid_HostAndPath(const std::string& url) {
    std::regex host_path_pattern(R"(^https?://([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}(/[^/\s]*)*$)");

    return std::regex_match(url, host_path_pattern);
}

bool URL_Validator::Has_Valid_Characters(const std::string& url) {
    std::regex valid_chars_pattern(R"(^[a-zA-Z0-9\-._~:/?#\[\]@!$&'()*+,;=\%]*$)");
    
    return std::regex_match(url, valid_chars_pattern);
}
```

#### Image Content Validation

The system performs actual image validation by checking the file headers:

```cpp
bool URL_Validator::Check_Image_Magic_Numbers(const std::vector<unsigned char>& data) {
    if (data.size() < 4)
        return false;

    // Supports multiple image formats:
    // JPEG: FF D8 FF
    if (data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF)
        return true;

    // PNG: 89 50 4E 47 0D 0A 1A 0A
    if (data.size() >= 8 && data[0] == 0x89 && data[1] == 0x50 /* ... */)
        return true;

    // Additional formats: GIF, BMP, WebP
    // ...
}
```

#### Cross-Platform Implementation

The system includes platform-specific implementations to fetch image data:

- **Windows**: Uses the WinHTTP API (`Fetch_Image_Data_Windows`).
- **Linux**: Uses OpenSSL and socket programming (`Fetch_Image_Data_Linux`).

Both implementations:
- Establish secure connections (HTTPS).
- Request only the header portion of the image (first 16 bytes).
- Manage connection and resource cleanup.

#### Main Features

1. **Comprehensive Validation**:
    - URL format and structure.
    - Protocol security (support for HTTPS).
    - Domain and path validation.
    - Character set validation.
    - Efficient image format verification.

2. **Security Features**:
    - Timeout protection.
    - Maximum URL length limit.
    - Secure cross-platform connections.
    - Efficient in-memory image validation.

3. **Supported Image Formats**:
    - JPEG
    - PNG
    - GIF
    - BMP
    - WebP

4. **Error Handling**:
    - Detailed logging at each validation stage.
    - Elegant timeout management.
    - Platform-specific error handling.
    - Resource cleanup in all scenarios.

### 3. HTTP Client

| **Files**          |
|---------------------|
| `http_client.h`     |
| `http_client.cpp`   |
| `http_windows.cpp`  |
| `http_linux.cpp`    |
| `http_response.h`   |
| `http_response.cpp` |

- The HTTP client is responsible for sending the collected information to the backend via HTTPS. The implementation is cross-platform, using WinHTTP on Windows and OpenSSL/sockets on Linux, ensuring secure communication through SSL/TLS.

#### Structure and Functioning

The main file `http_client.h` defines the interface of the class:

```cpp
class HTTP_Client {
    public:
        static bool Send_Request(const std::string& host, const std::string& path,
            const std:: string& data, const std::string& action);
    private:
        #ifdef _WIN32
            static bool Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data);
        #else
            static bool Send_Request_Linux(const std::string& host, const std::string& path, const std::string& data);
        #endif
};
```

The implementation in `http_client.cpp` automatically selects the correct implementation:

```cpp
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
```

#### Windows Implementation (WinHTTP)

In `http_windows.cpp`, the implementation uses the WinHTTP API:

```cpp
bool HTTP_Client::Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data) {
    HINTERNET spc_session = WinHttpOpen(L"SPC-INTEGRATION/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    // Set timeout of 60 seconds
    DWORD timeout = 60000;

    WinHttpSetOption(spc_session, WINHTTP_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

    // Connect and send HTTPS request
    HINTERNET spc_connect = WinHttpConnect(spc_session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    
    // ... rest of the Windows implementation
}
```

#### Linux Implementation (OpenSSL)

In `http_linux.cpp`, the implementation uses OpenSSL with sockets:

```cpp
bool HTTP_Client::Send_Request_Linux(const std::string& host, const std::string& path, const std::string& data) {
    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Set up SSL context
    const SSL_METHOD* method = SSLv23_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    // Create and configure socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;

    // ... rest of the Linux implementation
}
```

#### Response Processing

The `HTTP_Response` class in `http_response.h` processes server responses:

```cpp
class HTTP_Response {
    public:
        std::string message;
        std::string type;
        bool success = false;
    
        void Log_Response() const;
        bool Parse_Response(const std::string& json);
};
```

The implementation in `http_response.cpp` handles different types of responses:

```cpp
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
    // ... other error types

    Log_Printf("%s %s: %s", prefix, error_prefix, message.c_str());
}
```

#### Main Features

1. **Secure Communication**:
    - HTTPS (port 443) with SSL/TLS.
    - 60 seconds timeout for connection, sending, and receiving.
    - Content-Type: `application/x-www-form-urlencoded` with UTF-8.

2. **Error Handling**:
    - Checks each communication step.
    - Properly releases resources.
    - Detailed logging by error type:
        - Server errors: Suggest checking configurations.
        - Authentication errors: Indicates checking API key.
        - Validation errors: Recommends reviewing configurations.

3. **JSON Response Format**:
    ```json
    {
        "success": true/false,
        "message": "Response message"
    }
    ```

### 4. Base64 Encoding

| **Files**          |
|---------------------|
| `base64_encoder.h`   |
| `base64_encoder.cpp` |

- Base64 encoding is used to encode the image URL before sending it to the backend. This is especially useful when the URL contains special characters that may not be handled correctly in an HTTP request.

#### Interface Definition

```cpp
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
```

- The interface is defined using include guards to prevent multiple definitions. The class uses a static method `Encode` that takes a string as input and returns its encoded version.

#### Base64 Alphabet and Implementation

```cpp
#include "base64_encoder.h"

const std::string Base64_Encoder::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
```

- The Base64 alphabet is defined as a constant string containing 64 different characters. This string is used as a lookup table during the encoding process.

#### Initialization and Buffers

```cpp
// ... "Base64 Alphabet and Implementation" ...

std::string Base64_Encoder::Encode(const std::string& input) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    const char* bytes_to_encode = input.c_str();
    size_t in_len = input.length();

    return ret;
}
```

- Two character arrays are initialized: one to store the 3 input bytes and another for the 4 resulting Base64 characters. The input string is converted to a character array for byte-by-byte processing.

#### Main Encoding Loop

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Initialization and Buffers" ...

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);

        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                ret += base64_chars[char_array_4[i]];

            i = 0;
        }
    }

    return ret;
}
```

- The main loop processes the input in groups of 3 bytes, converting them into 4 Base64 characters through bitwise operations. Each group of 24 bits is divided into four groups of 6 bits.

#### Padding Handling

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Main Encoding Loop" ...

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; j < i + 1; j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';
    }

    return ret;
}
```

- For inputs that are not multiples of 3 bytes, padding is necessary. The remaining bytes are filled with zeros and encoded, and the '=' character is added to complete the group of 4 characters.

#### Main Features

1. **Data Processing**:
    - Conversion of groups of 3 bytes into 4 Base64 characters.
    - Bitwise manipulation for precise value extraction.
    - Automatic padding handling for non-multiple sizes of 3.

2. **Design and Architecture**:
    - Modular implementation with clear separation of responsibilities.
    - Use of static methods for easy access.
    - Encapsulation of the Base64 alphabet as a private member.

3. **Optimization and Performance**:
    - Efficient byte-by-byte processing.
    - Use of fixed arrays to minimize memory allocations.
    - Optimized bitwise operations for fast conversion.

4. **Robustness and Reliability**:
    - Safe handling of strings of any size.
    - Guarantee of always valid Base64 output.
    - Preservation of data integrity during encoding.

### 5. Logging

| **Files**          |
|---------------------|
| `logger.h`          |

- The logging system is a fundamental part of the plugin, as it allows developers to monitor the plugin's behavior and identify issues. The use of logs aids in debugging and maintaining the code.

#### Interface Definition

```cpp
#ifndef LOGGER_H
    #define LOGGER_H

    typedef void (*Log_Printf_t)(const char* Format, ...);
    extern Log_Printf_t Log_Printf;
#endif
```

- The logging system is defined through a function pointer that uses variable arguments, allowing flexibility in formatting messages. The `extern` declaration indicates that the actual implementation of the function will be provided at runtime.

#### Function Type Definition

```cpp
typedef void (*Log_Printf_t)(const char* Format, ...);
```

The type `Log_Printf_t` defines the signature of the logging function:
- `void`: The function does not return a value.
- `const char* Format`: The first parameter is a format string.
- `...`: Allows variable arguments for dynamic formatting.

#### Function Pointer Declaration

```cpp
extern Log_Printf_t Log_Printf;
```

The pointer `Log_Printf` is declared as external, allowing:
- The actual implementation to be provided by the host application.
- The plugin to utilize the existing logging infrastructure.
- Messages to be integrated into the main logging system.

#### Main Features

1. **Implementation Flexibility**:
    - Support for variable arguments for dynamic formatting.
    - Ability to integrate with different logging systems.
    - Implementation can be provided at runtime.

2. **Integration with Host System**:
    - Utilizes existing logging infrastructure.
    - Messages can be directed to different outputs.
    - Consistency with the main application logging.

3. **Ease of Use**:
    - Simple and familiar interface (similar to printf).
    - Can be used anywhere in the code.
    - Does not require additional configuration in the plugin code.

### 6. Plugin Entry Point

| **Files**          |
|---------------------|
| `main.cpp`          |

- The plugin entry point is where the execution of the plugin begins. This file is responsible for:
    - Initializing essential AMX functions.
    - Collecting and validating server information.
    - Checking configurations in the server.cfg/config.json file.
    - Sending data to the SPC backend.

#### Main Entry Functions

```cpp
// Initial loading of the plugin.
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** Plugin_Data) {
    // Initializes AMX functions and logging system.
    // Collects server information.
    // Validates image and website URLs.
    // Sends data to the backend.
    // Displays status information.
}

// Unloading the plugin.
PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    // Finalizes the plugin.
}

// Supported resources.
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

// Loading AMX scripts.
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* Amx) {
    return AMX_ERR_NONE;
}

// Unloading AMX scripts.
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* Amx) {
    return AMX_ERR_NONE;
}
```

1. **Initialization Process**:
    - Initializes essential AMX functions and logging system.
    - Collects server information through the `Server_Info` class.
    - Checks for the presence and validity of parameters:
        - `spc_integration_image` in the configuration file.
        - `weburl/website` in the configuration file.
    - Validates the provided URLs.
    - Attempts to send the data to the backend (first as "create", then as "update" if necessary).
    - Displays detailed information about the initialization status.

2. **Validations and Checks**:
    - Checks the presence and validity of the image URL.
    - Checks the presence and validity of the website URL.
    - Validates the URLs using the `URL_Validator` class.
    - Attempts automatic reconnection in case of initial send failure.

3. **Feedback and Logging**:
    - Displays an informative banner with plugin details and social links.
    - Provides detailed messages about configuration errors.
    - Shows the final status of initialization with server information.

### 7. Definitions and Inclusions

| **Files**          |
 |---------------------|
| `plugin_defines.h`   |
| `inclusions.h`       |

- These files contain definitions and inclusions necessary for the plugin's operation, establishing important constants and ensuring cross-platform compatibility.

#### Plugin Definitions

```cpp
#ifndef PLUGIN_DEFINES_H
    #define PLUGIN_DEFINES_H
    
    #define PLUGIN_VERSION "1.0.0"
    #define BACKEND_HOST "example_site.com" // Without the 'https://' or 'http://'.
    #define BACKEND_PATH "/backend_directory/spc-integration.php"
    #define API_KEY "YOUR_SECURE_KEY_TO_ACCESS_PHP"
    #define CONFIG_FILE_SAMP "server.cfg"
    #define CONFIG_FILE_OPEN "config.json"
#endif
```

The definitions file contains crucial constants for the plugin's operation:
- Plugin version.
- Backend configurations for communication.
- API key for authentication.
- Names of configuration files.

#### Base Structure of Inclusions

```cpp
#ifndef INCLUSIONS_H
    #define INCLUSIONS_H

    #include <stdint.h>
    #define HAVE_STDINT_H

    #include <string>
    #include <regex>
    #include <fstream>
    #include <sstream>
    #include <cstring>
    #include <chrono>
    #include <future>
```

Inclusion of standard C++ libraries necessary for:
- String and file manipulation.
- Regular expressions.
- Asynchronous operations.
- Time manipulation.

#### Windows-Specific Inclusions

```cpp
#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #include <windows.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <winhttp.h>

    #pragma comment(lib, "ws2_32.lib")
    #pragma comment(lib, "winhttp.lib")
```

Windows-specific support:
- Windows networking APIs.
- Windows HTTP libraries.
- Linking configurations.

#### Unix/Linux-Specific Inclusions

```cpp
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <ifaddrs.h>
    #include <net/if.h>
    #include <openssl/ssl.h>
    #include <openssl/err.h>
#endif
```

Unix/Linux-specific support:
- POSIX networking APIs.
- SSL support via OpenSSL.
- Networking interfaces.

#### Main Features

1. **Backend Configuration**:
    - Configurable host and path for deployment flexibility.
    - API key for secure authentication.
    - Explicit versioning of the plugin.

2. **Cross-Platform Compatibility**:
    - Native support for Windows and Unix/Linux.
    - Abstraction of platform-specific APIs.
    - Conditional implementations for each platform.

3. **Security and Communication**:
    - Support for SSL/TLS for secure communication.
    - Authentication via API key.
    - Robust libraries for networking.

4. **Resource Management**:
    - Support for asynchronous operations.
    - Efficient handling of strings and files.
    - Time and timing control.

## Back-End

The backend is responsible for receiving the information sent by the plugin and storing it in a JSON file. Here is a detailed explanation of its operation:

### 1. Data Reception
  - The plugin sends an HTTP POST request containing the server information (IP, port, website URL, and image URL).
  - The backend validates the request, ensuring that the provided `API_KEY` matches the key configured in the backend.
  - This is crucial for security, as it prevents unauthorized requests from being processed.
  - Supports URLs in both normal and base64-encoded formats.

### 2. Request Validation
   - The backend checks if the provided `API_KEY` in the request is valid.
   - Uses the `hash_equals()` function for secure key comparison.
   - If the key is invalid, it returns an authentication error.
   - The code below illustrates this validation:
        ```php
        function Validate_Request($provided_key) {
            global $api_key;

            return hash_equals($api_key, $provided_key);
        }

        if (!Validate_Request($api_key_provided)) {
            $response = [
                'success' => false,
                'message' => 'Authentication Error: Invalid API key provided. Please check your configuration.'
            ];
            echo json_encode($response);

            exit;
        }
        ```

### 3. Directory Validation
  - Checks for the existence of necessary directories:
      - `example_directory` as the base directory.
      - `example_servers` as the storage location.
  - Confirms write permissions in the upload directory.
  - Returns specific error messages if any validation fails.

### 4. URL Processing
   - Functions specifically process image and web URLs.
   - Supports both normal and base64-encoded URLs.
   - Validates base64 decoding when used.
   - Handles errors for invalid URLs.

### 5. Data Storage
   - Creates unique JSON files in the format `IP-Port.json`.
   - Sanitizes file names for security.
   - Sets appropriate permissions (chmod 0644).
   - Implements a backup system for updates.
   - The code below shows the storage process:
        ```php
        $filename = preg_replace('/[^a-zA-Z0-9\-\.]/', '', $server_ip . '-' . $server_port . '.json');
        $file_path = 'example_directory/' . $filename;

        $json_data = json_encode([
            'spc_integration_image' => $processed_image_URL,
            'spc_web_url' => $processed_web_URL
        ], JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);

        if (file_put_contents($file_path, $json_data) !== false) {
            $response = [
                'success' => true,
                'message' => 'Server data successfully created for ' . $server_ip . ':' . $server_port
            ];
        }
        else {
            $response = [
                'success' => false,
                'message' => 'Server error: Failed to create server data file. Please report this issue to the (SPC Team).'
            ];
        }
        ```

### 6. JSON File Format
   - Clear and organized structure of the data.
   - Uses pretty-print formatting for better readability.
   - Preserves URL formatting with unescaped slashes.
   - Example of the JSON file content:
        ```json
        {
            "spc_integration_image": "https://example.com/image.png",
            "spc_web_url": "https://example.com"
        }
        ```

### 7. Backup System
   - Automatically creates a backup before updates.
   - Restores original data in case of failure.
   - Removes backup files after successful operations.
   - Ensures data integrity during updates.

### 8. Error Handling
   - Detailed and specific error messages.
   - Validations at each stage of the process.
   - Consistent responses in JSON format.
   - Types of errors handled:
       - Authentication failures.
       - Directory issues.
       - File operation errors.
       - Validation failures.
       - HTTP method restrictions.

## Important Definitions

### 1. BACKEND_HOST and BACKEND_PATH

In the `plugin_defines.h` file, you will find the following definitions:

```cpp
#define BACKEND_HOST "example_site.com" // Without the 'https://' or 'http://'.
#define BACKEND_PATH "/backend_directory/spc-integration.php"
```

- **BACKEND_HOST**: This definition represents the address of the server where the backend is hosted. In the context of the plugin, this is the location to which the server information will be sent. It is important to note that, for security reasons, SPC does not disclose the actual backend address. This is done to protect the integrity and security of the data, preventing sensitive information from being exposed.

- **BACKEND_PATH**: This definition specifies the path of the PHP script that will process the requests sent by the plugin. The path must be accessible from the `BACKEND_HOST` and must be configured to accept POST requests. The PHP script is responsible for validating the received data and storing it in a JSON file.

### 2. upload_dir in Backend

In the PHP script (`spc-integration.php`), the variable `upload_dir` is defined as follows:

```php
$upload_dir = $base_dir . '/example_directory/example_servers/';
```

- **upload_dir**: This directory is where the JSON files containing the server information will be stored. The backend checks if this directory exists and is writable before attempting to create or modify files. If the directory does not exist or is not writable, the backend will return an error, indicating that it could not store the data.

### Security and Privacy

SPC prioritizes the security and privacy of data. Therefore, the actual backend address and the `API_KEY` are not publicly disclosed. The compiled plugin available in the [releases](https://github.com/spc-samp/spc-integration/releases) uses the SPC's address and `API_KEY` to securely store server information. This ensures that only authorized requests are processed and that server data is protected against unauthorized access.

## Compilation

The **SPC Integration** can be compiled in both Windows and Linux environments. This section details the compilation process, including environment setup, the use of Docker, CMake, and compilation scripts.

### Compilation for Windows

#### 1. Requirements

To compile the plugin in a Windows environment, the following are required:

- **Visual Studio 2022**: Visual Studio must be installed with C++ support, with the option for desktop development with C++ selected during installation.

#### 2. Compilation Steps

##### 2-1. Opening the Project in Visual Studio

1. Open Visual Studio 2022.
2. Navigate to the `spc-integration.sln` file in the project and open it.
3. Visual Studio will load the project and its settings.

##### 2-2. Configuring the Project

- The C++ version should be set to C++17 in the project settings under **Project Properties** > **Configuration Properties** > **C/C++** > **Language** > **C++ Language Standard**.

##### 2-3. Compiling the Project

- With the project configured, select "Build" from the top menu and choose "Build Solution" or press `Ctrl + Shift + B`.
- Visual Studio will compile the project and generate the plugin.

#### 2-4. Verifying the Compilation

- After a successful compilation, the plugin file (`spc-integration.dll`) will be available in the output folder (usually `Debug` or `Release`).

### Compilation for Linux

#### 1. Requirements

The compilation environment requires the following tools:

- **Docker**: A platform for building, deploying, and running applications in containers. Docker is used to create an isolated build environment.
- **CMake**: A build automation tool that uses configuration files to generate project files for different build systems.
- **GCC 8**: The GNU C++ compiler used to compile the plugin code.

#### 2. Compilation Steps

##### 2-1. Building the Docker Image

The process starts by navigating to the `docker` folder and executing the `build.sh` script to build the Docker image and compile the plugin. This script creates a build environment containing all necessary dependencies and performs the compilation automatically.

```bash
cd docker
./build.sh
```

##### 2-2. `build.sh`

The `build.sh` script performs the following operations:

```bash
#!/bin/bash

dos2unix "$0" 2>/dev/null || true

if ! command -v docker &> /dev/null; then
    echo "Docker is not installed. Please install Docker first."
    exit 1
fi

PROJECT_ROOT="$(dirname "$(pwd)")"

TEMP_DIR=$(mktemp -d)
echo "Creating temporary working directory: $TEMP_DIR"

echo "Copying required files..."
cp -r \
    "$PROJECT_ROOT"/*.cpp \
    "$PROJECT_ROOT"/*.h \
    "$PROJECT_ROOT/sdk" \
    "$TEMP_DIR/"

mkdir -p "$TEMP_DIR/cmake"

cp "$PROJECT_ROOT/cmake/CMakeLists.txt" "$TEMP_DIR/cmake/";

cp Dockerfile "$TEMP_DIR/";
```

- **Features**:
  - The script checks for Docker installation.
  - Creates a temporary directory to store the necessary files for compilation.
  - Copies source code and header files to the temporary directory where the Docker image will be built.

##### 2-3. Building the Plugin

The `build.sh` script manages the entire compilation process. It uses Docker to create an isolated environment and automatically runs the `compile.sh` script within the container. The process includes:
1. Creating a Docker image with all dependencies.
2. Running the container with the build environment.
3. Compiling the plugin using CMake.
4. Copying the compiled files to the `build` folder in the project directory.

##### 2-4. `compile.sh`

The `compile.sh` script is responsible for configuring and compiling the project using CMake:

```bash
#!/bin/bash

rm -rf ../build
mkdir -p ../build
cd ../build
cmake ../cmake -DCMAKE_BUILD_TYPE=Release
make -j$(nproc) VERBOSE=1
strip -s spc-integration.so
echo "Checking binary dependencies:"
ldd spc-integration.so
```

- **Features**:
    - Removes any previous build directory and creates a new one.
    - Uses CMake to configure the project, specifying the build type as "Release" for optimizations.
    - The `make` command compiles the project, utilizing all available cores (`-j$(nproc)`).
    - After compilation, the plugin is "strip" to remove debugging information.
    - The script checks the dependencies of the generated binary using `ldd`.

#### 3. Dockerfile

The `Dockerfile` defines the build environment. A typical configuration for this project might look like:

```dockerfile
FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++-8 \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN cmake . && make
```

- **Features**:
    - **FROM ubuntu:18.04**: Sets the base image to Ubuntu 18.04 - **RUN apt-get update && apt-get install -y**: Updates the package list and installs the necessary dependencies.
    - **WORKDIR /app**: Sets the working directory inside the container.
    - **COPY . .**: Copies the files from the current directory to the working directory in the container.
    - **RUN cmake . && make**: Executes CMake to compile the project inside the container.

> [!IMPORTANT]
> Using a Dockerfile ensures that the build environment is reproducible and isolated, avoiding dependency conflicts that may occur on local systems. This approach is especially useful when different developers or servers have varied environment configurations.