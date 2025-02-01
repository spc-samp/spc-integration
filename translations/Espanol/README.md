# spc-integration  

El **SPC Integration** es un plugin desarrollado para SA-MP (San Andreas Multiplayer) y open.mp (Open Multiplayer) que recopila información del servidor, como IP, puerto, URL del sitio y una URL de imagen configurable. Esta información se envía al sitio de SPC (SA-MP Programming Community), donde se almacenan los datos de los servidores.  

## Idiomas  

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)  
- English: [README](../English/README.md)  
- Français: [README](../Francais/README.md)  
- Italiano: [README](../Italiano/README.md)  
- Polski: [README](../Polski/README.md)  
- Русский: [README](../Русский/README.md)  
- Svenska: [README](../Svenska/README.md)  
- Türkçe: [README](../Turkce/README.md)

## Índice  

- [spc-integration](#spc-integration)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Funcionalidades Principales](#funcionalidades-principales)
    - [1. Recopilación de Información del Servidor](#1-recopilación-de-información-del-servidor)
    - [2. Validación de URL](#2-validación-de-url)
    - [3. Integración con Backend](#3-integración-con-backend)
    - [4. Compatibilidad Multiplataforma](#4-compatibilidad-multiplataforma)
  - [Cómo Usar el Plugin](#cómo-usar-el-plugin)
    - [1. Descarga](#1-descarga)
    - [2. Instalación](#2-instalación)
    - [3. Configuración](#3-configuración)
    - [4. Verificación](#4-verificación)
  - [Estructura del Proyecto](#estructura-del-proyecto)
  - [Detalles del Código](#detalles-del-código)
    - [1. Recopilación de Información del Servidor](#1-recopilación-de-información-del-servidor-1)
      - [Estructura Principal](#estructura-principal)
      - [Recopilación de IP del Servidor](#recopilación-de-ip-del-servidor)
      - [Lectura del Puerto del Servidor](#lectura-del-puerto-del-servidor)
      - [URLs de imagen y Sitio Web](#urls-de-imagen-y-sitio-web)
      - [Estado de Configuración](#estado-de-configuración)
      - [Inicialización](#inicialización)
      - [Características Principales](#características-principales)
    - [2. Validación de URL de imagen](#2-validación-de-url-de-imagen)
      - [Visión General de la Arquitectura](#visión-general-de-la-arquitectura)
      - [Validación Protegida por Timeout](#validación-protegida-por-timeout)
      - [Flujo de Validación Completa](#flujo-de-validación-completa)
      - [Validación de Componentes de la URL](#validación-de-componentes-de-la-url)
      - [Validación del Contenido de la Imagen](#validación-del-contenido-de-la-imagen)
      - [Implementación Multiplataforma](#implementación-multiplataforma)
      - [Características Principales](#características-principales-1)
    - [3. Cliente HTTP](#3-cliente-http)
      - [Estructura y Funcionamiento](#estructura-y-funcionamiento)
      - [Implementación en Windows (WinHTTP)](#implementación-en-windows-winhttp)
      - [Implementación en Linux (OpenSSL)](#implementación-en-linux-openssl)
      - [Procesamiento de Respuesta](#procesamiento-de-respuesta)
      - [Características Principales](#características-principales-2)
    - [4. Codificación Base64](#4-codificación-base64)
      - [Definición de la Interfaz](#definición-de-la-interfaz)
      - [Alfabeto Base64 e Implementación](#alfabeto-base64-e-implementación)
      - [Inicialización y Buffers](#inicialización-y-buffers)
      - [Bucle Principal de Codificación](#bucle-principal-de-codificación)
      - [Manejo del Relleno (Padding)](#manejo-del-relleno-padding)
      - [Características Principales](#características-principales-3)
    - [5. Logging](#5-logging)
      - [Definición de la Interfaz](#definición-de-la-interfaz-1)
      - [Definición del Tipo de Función](#definición-del-tipo-de-función)
      - [Declaración del Puntero de Función](#declaración-del-puntero-de-función)
      - [Características Principales](#características-principales-4)
    - [6. Punto de Entrada del Plugin](#6-punto-de-entrada-del-plugin)
      - [Principales Funciones de Entrada](#principales-funciones-de-entrada)
    - [7. Definiciones e Inclusiones](#7-definiciones-e-inclusiones)
      - [Definiciones del Plugin](#definiciones-del-plugin)
      - [Estructura Base de las Inclusiones](#estructura-base-de-las-inclusiones)
      - [Inclusiones Específicas para Windows](#inclusiones-específicas-para-windows)
      - [Inclusiones Específicas para Unix/Linux](#inclusiones-específicas-para-unixlinux)
      - [Características Principales](#características-principales-5)
  - [Back-End](#back-end)
    - [1. Recepción de Datos](#1-recepción-de-datos)
    - [2. Validación de la Solicitud](#2-validación-de-la-solicitud)
    - [3. Validación de Directorios](#3-validación-de-directorios)
    - [4. Procesamiento de URLs](#4-procesamiento-de-urls)
    - [5. Almacenamiento de Datos](#5-almacenamiento-de-datos)
    - [6. Formato del Archivo JSON](#6-formato-del-archivo-json)
    - [7. Sistema de Respaldo](#7-sistema-de-respaldo)
    - [8. Manejo de Errores](#8-manejo-de-errores)
  - [Definiciones Importantes](#definiciones-importantes)
    - [1. BACKEND\_HOST y BACKEND\_PATH](#1-backend_host-y-backend_path)
    - [2. upload\_dir en Backend](#2-upload_dir-en-backend)
    - [Seguridad y Privacidad](#seguridad-y-privacidad)
  - [Compilación](#compilación)
    - [Compilación para Windows](#compilación-para-windows)
      - [1. Requisitos](#1-requisitos)
      - [2. Pasos para la Compilación](#2-pasos-para-la-compilación)
        - [2-1. Abrir el Proyecto en Visual Studio](#2-1-abrir-el-proyecto-en-visual-studio)
        - [2-2. Configurar el Proyecto](#2-2-configurar-el-proyecto)
        - [2-3. Compilar el Proyecto](#2-3-compilar-el-proyecto)
      - [2-4. Verificando la Compilación](#2-4-verificando-la-compilación)
    - [Compilación para Linux](#compilación-para-linux)
      - [1. Requisitos](#1-requisitos-1)
      - [2. Pasos para la Compilación](#2-pasos-para-la-compilación-1)
        - [2-1. Construyendo la Imagen Docker](#2-1-construyendo-la-imagen-docker)
        - [2-2. `build.sh`](#2-2-buildsh)
        - [2-3. Construyendo el Plugin](#2-3-construyendo-el-plugin)
        - [2-4. `compile.sh`](#2-4-compilesh)
      - [3. Dockerfile](#3-dockerfile)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Concedidos](#1-permisos-concedidos)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Restricciones y Limitaciones](#3-restricciones-y-limitaciones)
      - [4. Propiedad Intelectual](#4-propiedad-intelectual)
      - [5. Exención de Garantías y Limitación de Responsabilidad](#5-exención-de-garantías-y-limitación-de-responsabilidad)

## Funcionalidades Principales  

### 1. Recopilación de Información del Servidor  
   - El plugin recopila automáticamente la IP y el puerto del servidor en ejecución.  
   - Identifica si el servidor es SA-MP u open.mp y recopila la URL del sitio correspondiente, si está disponible.  
   - Permite configurar una URL de imagen personalizada mediante el parámetro `spc_integration_image`, que debe agregarse al archivo de configuración del servidor.  

### 2. Validación de URL  
   - Antes de enviar la URL de la imagen al backend, el plugin valida si la URL proporcionada es accesible y corresponde a un formato de imagen válido (JPEG, PNG, GIF, etc.).  
   - Esto garantiza que solo se envíen URLs de imágenes válidas, evitando creaciones o actualizaciones innecesarias en el JSON.  

### 3. Integración con Backend  
   - El plugin envía la información recopilada a un backend mediante una solicitud HTTP POST.  
   - El backend valida la solicitud, asegurando que la `API_KEY` proporcionada coincida con la clave configurada en el backend. Esto es crucial para la seguridad, ya que evita el procesamiento de solicitudes no autorizadas.  
   - Si los datos son válidos, el backend crea un archivo JSON en formato `IP-Port.json`, almacenando la información del servidor.  

### 4. Compatibilidad Multiplataforma  
   - Soporta compilación para Linux (usando Docker, CMake y GCC 8) y Windows (usando Visual Studio 2022).  
   - Funciona tanto para SA-MP como para open.mp, permitiendo que todos los servidores utilicen el plugin.  

## Cómo Usar el Plugin  

### 1. Descarga  

- Descarga la versión más reciente del plugin en la sección [releases](https://github.com/spc-samp/spc-integration/releases).  
- Elige el archivo adecuado para tu sistema operativo:  
  - Windows: `spc-integration.dll`  
  - Linux: `spc-integration.so`  

### 2. Instalación  

1. Extrae el archivo descargado.  
2. Coloca el plugin en la carpeta `plugins` de tu servidor.  
3. Configura el servidor para cargar el plugin:  
   - **Para SA-MP**: Agrega en tu `server.cfg`:  
     ```  
     plugins spc-integration  
     ```  
   - **Para open.mp**: Agrega `"spc-integration"` a la lista `legacy_plugins` en tu `config.json`:  
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
> Si ya tienes otros plugins instalados, asegúrate de cargar spc-integration después de ellos.  

### 3. Configuración  

Debes configurar la URL de la imagen que se mostrará para tu servidor. Elige una de las opciones según tu plataforma:  

- **1. server.cfg (SA-MP)**  
    ```  
    spc_integration_image https://example.com/image.png  
    ```  

- **2. config.json (open.mp)**  
    ```json  
    {  
        "spc_integration_image": "https://example.com/image.png"  
    }  
    ```  

> [!IMPORTANT]  
> La URL de la imagen debe ser válida y accesible públicamente.  

### 4. Verificación  

1. Inicia tu servidor.  
2. Verifica los registros del servidor. Si ves un mensaje similar a este, el plugin funciona correctamente:  
    ```  
    [SPC Integration]: Information sent to the server data storage of the SPC:  
    -- Server IP: '127.0.0.1'  
    -- Server Port: '7777'  
    -- Image URL configured: 'https://example.com/image.png'  
    -- Web URL configured: 'https://example.com'  
    ```  

## Estructura del Proyecto  

La estructura del proyecto se organiza de la siguiente manera:  
```  
└── src/  
    ├── cmake/  
    │   ├── CMakeLists.txt               // Archivo de configuración de CMake  
    │   └── compile.sh                   // Script de compilación para Linux  
    │  
    ├── docker/  
    │   ├── build.sh                     // Script para construir la imagen Docker  
    │   └── Dockerfile                   // Archivo Docker para compilación en Linux  
    │  
    ├── sdk/  
    │   └── (SDK de SA-MP)               // SDK necesario para el desarrollo del plugin  
    │  
    ├── amx_defines.h                    // Definiciones relacionadas con AMX  
    ├── base64_encoder.cpp               // Implementación del codificador Base64  
    ├── base64_encoder.h                 // Cabecera del codificador Base64  
    ├── http_client.cpp                  // Implementación del cliente HTTP  
    ├── http_client.h                    // Cabecera del cliente HTTP  
    ├── http_linux.cpp                   // Implementación específica para Linux del cliente HTTP  
    ├── http_response.cpp                // Implementación de la respuesta HTTP  
    ├── http_response.h                  // Cabecera de la respuesta HTTP  
    ├── http_windows.cpp                 // Implementación específica para Windows del cliente HTTP  
    ├── inclusions.h                     // Inclusiones comunes y definiciones globales  
    ├── logger.h                         // Cabecera para logging  
    ├── main.cpp                         // Punto de entrada del plugin  
    ├── plugin_defines.h                 // Definiciones específicas del plugin  
    ├── server_info.cpp                  // Implementación para recopilar información del servidor  
    ├── server_info.h                    // Cabecera para recopilar información del servidor  
    ├── spc-integration.sln              // Archivo de solución de Visual Studio  
    ├── spc-integration.vcxproj          // Archivo de proyecto de Visual Studio  
    ├── spc-integration.vcxproj.filters  // Configuración de filtros del proyecto Visual Studio  
    ├── url_validator.cpp                // Implementación del validador de URL  
    └── url_validator.h                  // Cabecera del validador de URL  
```  

## Detalles del Código  

A continuación se presenta un análisis detallado de los componentes principales del código de **SPC Integration**. Cada sección se explica en profundidad para comprender el funcionamiento del plugin y su integración con el backend.  

### 1. Recopilación de Información del Servidor  

| **Archivos**      |  
|-------------------|  
| `server_info.h`   |  
| `server_info.cpp` |  

- La clase `Server_Info` es responsable de recopilar y gestionar información esencial del servidor, incluyendo IP, puerto, URLs de integración y sitio web. El sistema soporta dos formatos de archivo de configuración: server.cfg (SA-MP) y config.json (open.mp).  

#### Estructura Principal  

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

#### Recopilación de IP del Servidor

```cpp
bool Server_Info::Get_Server_IP() {
    #ifdef _WIN32
        // Windows: Usa WinSock API
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            return false;
            
        char hostname[256];

        if (gethostname(hostname, sizeof(hostname)) == 0) {
            // Código para obtener IP en Windows
            // ...
        }
    #else
        // Linux: Usa getifaddrs
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

#### Lectura del Puerto del Servidor

```cpp
bool Server_Info::Get_Server_Port() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Lee del archivo server.cfg (SA-MP)
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
        // Lee del archivo config.json (open.mp)
        std::ifstream config(CONFIG_FILE_OPEN);
        std::string json_content((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
        // Procesa JSON para encontrar el puerto
        // ...
    }
    return false;
}
```

#### URLs de imagen y Sitio Web

El sistema gestiona dos tipos de URLs:  
1. URL de Imagen (`image_url`): Dirección de la URL de imagen del servidor.  
2. URL del Sitio Web (`web_url`): Dirección del sitio web del servidor.  

```cpp
bool Server_Info::Get_Image_URL() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Busca "spc_integration_image" en el archivo
        if (/* URL encontrada */)
            image_config_status = Config_Status::Success;
        else
            image_config_status = Config_Status::Empty;
    }
    // Similar para CONFIG_FILE_OPEN
}

bool Server_Info::Get_Web_URL() {
    // Proceso similar a Get_Image_URL(), pero busca "weburl" o "website"
}
```

#### Estado de Configuración

El sistema utiliza enumeraciones para controlar el estado de las configuraciones:

```cpp
enum class Config_Status {
    Success,        // Configuración encontrada y válida
    Not_Found,      // Configuración no encontrada
    Empty,          // Configuración encontrada pero vacía
    Web_Not_Found,  // URL del sitio web no encontrada
    Web_Empty       // URL del sitio web vacía
};
```

#### Inicialización

El proceso de inicialización es gestionado por el método `Initialize()`:

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

#### Características Principales

1. **Recopilación de Información**:  
    - Detección automática de la IP del servidor.  
    - Lectura del puerto configurado.  
    - Soporte para URLs de imagen y sitio web.  
    - Validación de toda la información recopilada.  

2. **Compatibilidad**:  
    - Soporte para múltiples sistemas operativos.  
    - Compatibilidad con SA-MP y open.mp.  
    - Lectura de diferentes formatos de configuración.  

3. **Gestión de Estado**:  
    - Sistema robusto de estado para configuraciones.  
    - Control granular de errores y estados.  
    - Validación individualizada de cada componente.  

4. **Procesamiento de Datos**:  
    - Limpieza automática de cadenas.  
    - Detección y eliminación de espacios en blanco.  
    - Validación de URLs y configuraciones.

### 2. Validación de URL de imagen

| **Archivos**        |
|---------------------|
| `url_validator.h`   |
| `url_validator.cpp` |

- El sistema de validación de URL es un componente crítico de seguridad que realiza una validación exhaustiva de las URLs de imágenes a través de múltiples capas de verificación. No solo valida el formato de la URL, sino que también verifica si la URL apunta a un archivo de imagen válido.

#### Visión General de la Arquitectura

El proceso de validación se implementa en la clase `URL_Validator` y sigue un flujo de validación en múltiples etapas:

- **Validación Inicial** (`Is_Valid`).
- **Gestión de Timeout** (`Validate_With_Timeout`).
- **Proceso de Validación Completa** (`Perform_Full_Validation`).
- **Verificación del Contenido de la Imagen** (`Validate_Image_Headers`).

#### Validación Protegida por Timeout

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
    // ... manejo de excepciones
}
```

- El sistema implementa un mecanismo de timeout utilizando `std::async` para evitar bloqueos en URLs lentas o no responsivas. El proceso de validación fallará automáticamente si excede `VALIDATION_TIMEOUT` segundos (definido como 10 segundos en el código).

#### Flujo de Validación Completa

El método `Perform_FullValidation` implementa una serie de verificaciones:

```cpp
bool URL_Validator::Perform_Full_Validation(const std::string& url) {
    // Validación de longitud
    if (url.empty() || url.length() > 2048)
        return (Log_Printf("[SPC Integration]: Error: URL is empty or too long (maximum 2048 characters)."), false);

    // Validación de protocolo
    if (!Has_Valid_Scheme(url))
        return (Log_Printf("[SPC Integration]: Error: URL must start with 'http://' or 'https://'."), false);

    // Validación de estructura
    if (!Has_Valid_HostAndPath(url))
        return (Log_Printf("[SPC Integration]: Error: URL must contain a valid hostname and path."), false);

    // Validación de caracteres
    if (!Has_Valid_Characters(url))
        return (Log_Printf("[SPC Integration]: Error: URL contains invalid characters."), false);

    // Validación de imagen
    if (!Validate_Image_Headers(url))
        return (Log_Printf("[SPC Integration]: Error: The URL content is not a valid image."), false);

    Log_Printf("[SPC Integration]: Validation successfully completed!");

    return true;
}
```

#### Validación de Componentes de la URL

El sistema incluye validadores especializados para diferentes componentes de la URL:

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

#### Validación del Contenido de la Imagen

El sistema realiza la validación real de la imagen verificando los encabezados del archivo:

```cpp
bool URL_Validator::Check_Image_Magic_Numbers(const std::vector<unsigned char>& data) {
    if (data.size() < 4)
        return false;

    // Soporta múltiples formatos de imagen:
    // JPEG: FF D8 FF
    if (data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF)
        return true;

    // PNG: 89 50 4E 47 0D 0A 1A 0A
    if (data.size() >= 8 && data[0] == 0x89 && data[1] == 0x50 /* ... */)
        return true;

    // Formatos adicionales: GIF, BMP, WebP
    // ...
}
```

#### Implementación Multiplataforma

El sistema incluye implementaciones específicas para cada plataforma para obtener datos de imagen:

- **Windows**: Utiliza la API WinHTTP (`Fetch_Image_Data_Windows`).
- **Linux**: Utiliza OpenSSL y programación de sockets (`Fetch_Image_Data_Linux`).

Ambas implementaciones:
- Establecen conexiones seguras (HTTPS).
- Solicitan solo la porción del encabezado de la imagen (primeros 16 bytes).
- Gestionan la limpieza de conexión y recursos.

#### Características Principales

1. **Validación Exhaustiva**:
    - Formato y estructura de la URL.
    - Seguridad del protocolo (soporte para HTTPS).
    - Validación de dominio y ruta.
    - Validación del conjunto de caracteres.
    - Verificación del formato de la imagen.

2. **Funciones de Seguridad**:
    - Protección contra timeout.
    - Límite máximo de longitud de la URL.
    - Conexiones seguras multiplataforma.
    - Validación de imagen eficiente en memoria.

3. **Formatos de Imagen Soportados**:
    - JPEG
    - PNG
    - GIF
    - BMP
    - WebP

4. **Manejo de Errores**:
    - Registro detallado en cada etapa de validación.
    - Gestión eficiente del timeout.
    - Manejo de errores específico de la plataforma.
    - Liberación de recursos en todos los escenarios.

### 3. Cliente HTTP

| **Archivos**        |
|---------------------|
| `http_client.h`     |
| `http_client.cpp`   |
| `http_windows.cpp`  |
| `http_linux.cpp`    |
| `http_response.h`   |
| `http_response.cpp` |

- El cliente HTTP es responsable de enviar la información recopilada al backend a través de HTTPS. La implementación es multiplataforma, utilizando WinHTTP en Windows y OpenSSL/sockets en Linux, garantizando una comunicación segura a través de SSL/TLS.

#### Estructura y Funcionamiento

El archivo principal `http_client.h` define la interfaz de la clase:

```cpp
class HTTP_Client {
    public:
        static bool Send_Request(const std::string& host, const std::string& path,
            const std::string& data, const std::string& action);
    private:
        #ifdef _WIN32
            static bool Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data);
        #else
            static bool Send_Request_Linux(const std::string& host, const std::string& path, const std::string& data);
        #endif
};
```

La implementación en `http_client.cpp` selecciona automáticamente la implementación correcta:

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

#### Implementación en Windows (WinHTTP)

En `http_windows.cpp`, la implementación utiliza la API WinHTTP:

```cpp
bool HTTP_Client::Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data) {
    HINTERNET spc_session = WinHttpOpen(L"SPC-INTEGRATION/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    // Configura timeout de 60 segundos
    DWORD timeout = 60000;

    WinHttpSetOption(spc_session, WINHTTP_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

    // Conecta y envía solicitud HTTPS
    HINTERNET spc_connect = WinHttpConnect(spc_session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    
    // ... resto de la implementación en Windows
}
```

#### Implementación en Linux (OpenSSL)

En `http_linux.cpp`, la implementación usa OpenSSL con sockets:

```cpp
bool HTTP_Client::Send_Request_Linux(const std::string& host, const std::string& path, const std::string& data) {
    // Inicializa OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Configura contexto SSL
    const SSL_METHOD* method = SSLv23_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    // Crea y configura socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;

    // ... resto de la implementación en Linux
}
```

#### Procesamiento de Respuesta

La clase `HTTP_Response` en `http_response.h` procesa las respuestas del servidor:

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

La implementación en `http_response.cpp` maneja diferentes tipos de respuesta:

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
    // ... otros tipos de error

    Log_Printf("%s %s: %s", prefix, error_prefix, message.c_str());
}
```

#### Características Principales

1. **Comunicación Segura**:
    - HTTPS (puerto 443) con SSL/TLS.
    - Timeout de 60 segundos para conexión, envío y recepción.
    - Content-Type: `application/x-www-form-urlencoded` con UTF-8.

2. **Manejo de Errores**:
    - Verifica cada etapa de la comunicación.
    - Libera recursos adecuadamente.
    - Registro detallado por tipo de error:
        - Errores de servidor: Sugiere verificar configuraciones.
        - Errores de autenticación: Indica verificar API key.
        - Errores de validación: Recomienda revisar configuraciones.

3. **Formato de Respuesta JSON**:
    ```json
    {
        "success": true/false,
        "message": "Mensaje de respuesta"
    }
    ```

### 4. Codificación Base64  

| **Archivos**         |
|----------------------|
| `base64_encoder.h`   |
| `base64_encoder.cpp` |

- La codificación Base64 se utiliza para codificar la URL de la imagen antes de enviarla al backend. Esto es especialmente útil cuando la URL contiene caracteres especiales que pueden no ser tratados correctamente en una solicitud HTTP.  

#### Definición de la Interfaz  

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

- La interfaz se define utilizando guardas de inclusión para evitar múltiples definiciones. La clase utiliza un método estático `Encode` que acepta una cadena como entrada y devuelve su versión codificada.  

#### Alfabeto Base64 e Implementación  

```cpp
#include "base64_encoder.h"

const std::string Base64_Encoder::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
```

- El alfabeto Base64 se define como una cadena constante que contiene 64 caracteres diferentes. Esta cadena se utiliza como tabla de búsqueda durante el proceso de codificación.  

#### Inicialización y Buffers  

```cpp
// ... "Alfabeto Base64 e Implementación" ...

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

- Se inicializan dos arreglos de caracteres: uno para almacenar los 3 bytes de entrada y otro para los 4 caracteres Base64 resultantes. La cadena de entrada se convierte en un arreglo de caracteres para su procesamiento byte a byte.  

#### Bucle Principal de Codificación  

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Inicialización y Buffers" ...

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

- El bucle principal procesa la entrada en grupos de 3 bytes, convirtiéndolos en 4 caracteres Base64 mediante operaciones bit a bit. Cada grupo de 24 bits se divide en cuatro grupos de 6 bits.  

#### Manejo del Relleno (Padding)  

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Bucle Principal de Codificación" ...

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

- Para entradas que no son múltiplos de 3 bytes, es necesario agregar relleno. Los bytes restantes se llenan con ceros y se codifican, y el carácter '=' se agrega para completar el grupo de 4 caracteres.  

#### Características Principales  

1. **Procesamiento de Datos**:  
    - Conversión de grupos de 3 bytes en 4 caracteres Base64.  
    - Manipulación bit a bit para extracción precisa de los valores.  
    - Manejo automático del relleno para tamaños no múltiplos de 3.  

2. **Diseño y Arquitectura**:  
    - Implementación modular con una clara separación de responsabilidades.  
    - Uso de métodos estáticos para facilitar el acceso.  
    - Encapsulación del alfabeto Base64 como miembro privado.  

3. **Optimización y Rendimiento**:  
    - Procesamiento eficiente byte a byte.  
    - Uso de arreglos fijos para minimizar asignaciones de memoria.  
    - Operaciones bit a bit optimizadas para una conversión rápida.  

4. **Robustez y Confiabilidad**:  
    - Manejo seguro de cadenas de cualquier tamaño.  
    - Garantía de salida siempre válida en Base64.  
    - Preservación de la integridad de los datos durante la codificación.  

### 5. Logging  

| **Archivos** |
|--------------|
| `logger.h`   |

- El sistema de logging es una parte fundamental del plugin, ya que permite a los desarrolladores monitorear el comportamiento del plugin e identificar problemas. El uso de logs ayuda en la depuración y el mantenimiento del código.  

#### Definición de la Interfaz  

```cpp
#ifndef LOGGER_H
    #define LOGGER_H

    typedef void (*Log_Printf_t)(const char* Format, ...);
    extern Log_Printf_t Log_Printf;
#endif
```

- El sistema de logging se define a través de un puntero a función que utiliza argumentos variables, permitiendo flexibilidad en el formato de los mensajes. La declaración `extern` indica que la implementación real de la función será proporcionada en tiempo de ejecución.  

#### Definición del Tipo de Función  

```cpp
typedef void (*Log_Printf_t)(const char* Format, ...);
```

El tipo `Log_Printf_t` define la firma de la función de logging:  
- `void`: La función no devuelve valor.  
- `const char* Format`: El primer parámetro es una cadena de formato.  
- `...`: Permite argumentos variables para formateo dinámico.  

#### Declaración del Puntero de Función  

```cpp
extern Log_Printf_t Log_Printf;
```

El puntero `Log_Printf` se declara como externo, permitiendo que:  
- La implementación real sea proporcionada por la aplicación host.  
- El plugin utilice la infraestructura de logging existente.  
- Los mensajes se integren con el sistema de logging principal.  

#### Características Principales  

1. **Flexibilidad de Implementación**:  
    - Soporte para argumentos variables para formateo dinámico.  
    - Posibilidad de integración con diferentes sistemas de logging.  
    - La implementación puede ser proporcionada en tiempo de ejecución.  

2. **Integración con el Sistema Host**:  
    - Uso de la infraestructura de logging existente.  
    - Los mensajes pueden dirigirse a diferentes salidas.  
    - Consistencia con el logging de la aplicación principal.  

3. **Facilidad de Uso**:  
    - Interfaz simple y familiar (similar a printf).  
    - Puede utilizarse en cualquier parte del código.  
    - No requiere configuración adicional en el código del plugin.

### 6. Punto de Entrada del Plugin  

| **Archivos** |  
|--------------|  
| `main.cpp`   |  

- El punto de entrada del plugin es donde comienza la ejecución del mismo. Este archivo es responsable de:  
    - Inicializar funciones esenciales de AMX.  
    - Recopilar y validar información del servidor.  
    - Verificar configuraciones en el archivo server.cfg/config.json.  
    - Enviar datos al backend de SPC.  

#### Principales Funciones de Entrada  

```cpp
// Carga inicial del plugin.
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** Plugin_Data) {
    // Inicializa funciones de AMX y el sistema de registro.
    // Recopila información del servidor.
    // Valida URLs de la imagen y el sitio web.
    // Envía datos al backend.
    // Muestra información de estado.
}

// Descarga del plugin.
PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    // Finaliza el plugin.
}

// Recursos soportados.
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

// Carga de scripts AMX.
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* Amx) {
    return AMX_ERR_NONE;
}

// Descarga de scripts AMX.
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* Amx) {
    return AMX_ERR_NONE;
}
```

1. **Proceso de Inicialización**:  
    - Inicializa funciones esenciales de AMX y el sistema de registro.  
    - Recopila información del servidor a través de la clase `Server_Info`.  
    - Verifica la existencia y validez de los parámetros:  
        - `spc_integration_image` en el archivo de configuración.  
        - `weburl/website` en el archivo de configuración.  
    - Valida las URLs proporcionadas.  
    - Intenta enviar los datos al backend (primero como "create", luego como "update" si es necesario).  
    - Muestra información detallada sobre el estado de la inicialización.  

2. **Validaciones y Verificaciones**:  
    - Verifica la presencia y validez de la URL de la imagen.  
    - Verifica la presencia y validez de la URL del sitio web.  
    - Valida las URLs usando la clase `URL_Validator`.  
    - Intenta la reconexión automática en caso de fallo en el envío inicial.  

3. **Retroalimentación y Registro**:  
    - Muestra un banner informativo con detalles del plugin y enlaces sociales.  
    - Proporciona mensajes detallados sobre errores de configuración.  
    - Muestra el estado final de la inicialización con la información del servidor.  

### 7. Definiciones e Inclusiones  

| **Archivos**         |  
|----------------------|  
| `plugin_defines.h`   |  
| `inclusions.h`       |  

- Estos archivos contienen definiciones e inclusiones necesarias para el funcionamiento del plugin, estableciendo constantes importantes y garantizando compatibilidad multiplataforma.  

#### Definiciones del Plugin  

```cpp
#ifndef PLUGIN_DEFINES_H
    #define PLUGIN_DEFINES_H
    
    #define PLUGIN_VERSION "1.0.0"
    #define BACKEND_HOST "example_site.com" // Sin el protocolo 'https://' o 'http://'.
    #define BACKEND_PATH "/backend_directory/spc-integration.php"
    #define API_KEY "YOUR_SECURE_KEY_TO_ACCESS_PHP"
    #define CONFIG_FILE_SAMP "server.cfg"
    #define CONFIG_FILE_OPEN "config.json"
#endif
```

El archivo de definiciones contiene constantes cruciales para el funcionamiento del plugin:  
- Versión del plugin.  
- Configuraciones del backend para la comunicación.  
- Clave de API para autenticación.  
- Nombres de los archivos de configuración.  

#### Estructura Base de las Inclusiones  

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

Inclusión de las bibliotecas estándar de C++ necesarias para:  
- Manipulación de strings y archivos.  
- Expresiones regulares.  
- Operaciones asíncronas.  
- Manipulación de tiempo.  

#### Inclusiones Específicas para Windows  

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

Soporte específico para sistemas Windows:  
- APIs de red de Windows.  
- Bibliotecas HTTP de Windows.  
- Configuraciones de enlace.  

#### Inclusiones Específicas para Unix/Linux  

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

Soporte específico para sistemas Unix/Linux:  
- APIs de red POSIX.  
- Soporte para SSL a través de OpenSSL.  
- Interfaces de red.  

#### Características Principales  

1. **Configuración del Backend**:  
    - Host y path configurables para flexibilidad en la implementación.  
    - Clave de API para autenticación segura.  
    - Versionado explícito del plugin.  

2. **Compatibilidad Multiplataforma**:  
    - Soporte nativo para Windows y Unix/Linux.  
    - Abstracción de APIs específicas del sistema.  
    - Implementaciones condicionales para cada plataforma.  

3. **Seguridad y Comunicación**:  
    - Soporte para SSL/TLS para comunicación segura.  
    - Autenticación mediante clave de API.  
    - Bibliotecas robustas para redes.  

4. **Gestión de Recursos**:  
    - Soporte para operaciones asíncronas.  
    - Manipulación eficiente de strings y archivos.  
    - Control de tiempo y temporización.

## Back-End

El backend es responsable de recibir la información enviada por el plugin y almacenarla en un archivo JSON. Aquí tienes una explicación detallada de su funcionamiento:

### 1. Recepción de Datos
  - El plugin envía una solicitud HTTP POST que contiene la información del servidor (IP, puerto, URL del sitio y URL de la imagen).
  - El backend valida la solicitud, asegurándose de que la `API_KEY` proporcionada coincida con la clave configurada en el backend.
  - Esto es crucial para la seguridad, ya que impide que se procesen solicitudes no autorizadas.
  - Soporta URLs tanto en formato normal como codificadas en base64.

### 2. Validación de la Solicitud
   - El backend verifica si la `API_KEY` proporcionada en la solicitud es válida.
   - Utiliza la función `hash_equals()` para una comparación segura de las claves.
   - Si la clave no es válida, devuelve un error de autenticación.
   - El código a continuación ilustra esta validación:
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

### 3. Validación de Directorios
  - Verifica la existencia de los directorios necesarios:
      - `exemple_directory` como directorio base.
      - `exemple_servers` como ubicación de almacenamiento.
  - Confirma los permisos de escritura en el directorio de carga.
  - Devuelve mensajes de error específicos en caso de que alguna validación falle.

### 4. Procesamiento de URLs
   - Funciones específicas para procesar URLs de imagen y web.
   - Soporte para URLs normales y codificadas en base64.
   - Validación de la decodificación base64 cuando se utiliza.
   - Manejo de errores para URLs inválidas.

### 5. Almacenamiento de Datos
   - Crea archivos JSON únicos en el formato `IP-Port.json`.
   - Sanea los nombres de los archivos para seguridad.
   - Define permisos apropiados (chmod 0644).
   - Implementa un sistema de respaldo para actualizaciones.
   - El código a continuación muestra el proceso de almacenamiento:
        ```php
        $filename = preg_replace('/[^a-zA-Z0-9\-\.]/', '', $server_ip . '-' . $server_port . '.json');
        $file_path = 'exemple_directory/' . $filename;

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

### 6. Formato del Archivo JSON
   - Estructura clara y organizada de los datos.
   - Utiliza formato pretty-print para una mejor legibilidad.
   - Preserva el formato de las URLs con barras no escapadas.
   - Ejemplo del contenido del archivo JSON:
        ```json
        {
            "spc_integration_image": "https://example.com/image.png",
            "spc_web_url": "https://example.com"
        }
        ```

### 7. Sistema de Respaldo
   - Crea un respaldo automático antes de las actualizaciones.
   - Restaura los datos originales en caso de fallos.
   - Elimina los archivos de respaldo después de operaciones exitosas.
   - Garantiza la integridad de los datos durante las actualizaciones.

### 8. Manejo de Errores
   - Mensajes de error detallados y específicos.
   - Validaciones en cada etapa del proceso.
   - Respuestas consistentes en formato JSON.
   - Tipos de error tratados:
       - Fallos de autenticación.
       - Problemas con los directorios.
       - Errores en las operaciones de archivos.
       - Fallos de validación.
       - Restricciones de método HTTP.

## Definiciones Importantes

### 1. BACKEND_HOST y BACKEND_PATH

En el archivo `plugin_defines.h`, encontrarás las siguientes definiciones:

```cpp
#define BACKEND_HOST "example_site.com" // Sin el protocolo 'https://' o 'http://'.
#define BACKEND_PATH "/backend_directory/spc-integration.php"
```

- **BACKEND_HOST**: Esta definición representa la dirección del servidor donde está hospedado el backend. En el contexto del plugin, este es el lugar al que se enviarán las informaciones del servidor. Es importante señalar que, por razones de seguridad, SPC no divulga la dirección real del backend. Esto se hace para proteger la integridad y seguridad de los datos, evitando que se expongan informaciones sensibles.

- **BACKEND_PATH**: Esta definición especifica la ruta del script PHP que procesará las solicitudes enviadas por el plugin. La ruta debe ser accesible desde `BACKEND_HOST` y debe estar configurada para aceptar solicitudes POST. El script PHP es responsable de validar los datos recibidos y almacenarlos en un archivo JSON.

### 2. upload_dir en Backend

En el script PHP (`spc-integration.php`), la variable `upload_dir` se define de la siguiente forma:

```php
$upload_dir = $base_dir . '/exemple_directory/exemple_servers/';
```

- **upload_dir**: Este directorio es donde se almacenarán los archivos JSON que contienen la información del servidor. El backend verifica si este directorio existe y si es grabable antes de intentar crear o modificar archivos. Si el directorio no existe o no es grabable, el backend devolverá un error, informando que no fue posible almacenar los datos.

### Seguridad y Privacidad

SPC prioriza la seguridad y la privacidad de los datos. Por ello, la dirección real del backend y la `API_KEY` no se divulgan públicamente. El plugin compilado disponible en [releases](https://github.com/spc-samp/spc-integration/releases) utiliza la dirección y la `API_KEY` de SPC para almacenar la información del servidor de forma segura. Esto garantiza que solo se procesen solicitudes autorizadas y que los datos del servidor estén protegidos contra accesos no autorizados.

## Compilación

El **SPC Integration** puede ser compilado en entornos Windows y Linux. Esta sección detalla el proceso de compilación, incluida la configuración del entorno, el uso de Docker, CMake y los scripts de compilación.

### Compilación para Windows

#### 1. Requisitos

Para compilar el plugin en un entorno Windows, se necesitan:

- **Visual Studio 2022**: Visual Studio debe estar instalado con soporte para C++, con la opción para desarrollo de escritorio con C++ seleccionada durante la instalación.

#### 2. Pasos para la Compilación

##### 2-1. Abrir el Proyecto en Visual Studio

1. Abrir Visual Studio 2022.
2. Navegar al archivo `spc-integration.sln` en el proyecto y abrirlo.
3. Visual Studio cargará el proyecto y sus configuraciones.

##### 2-2. Configurar el Proyecto

- La versión de C++ debe estar definida como C++17 en las configuraciones del proyecto en **Project Properties** > **Configuration Properties** > **C/C++** > **Language** > **C++ Language Standard**.

##### 2-3. Compilar el Proyecto

- Con el proyecto configurado, seleccionar "Build" en el menú superior y elegir "Build Solution" o presionar `Ctrl + Shift + B`.
- Visual Studio compilará el proyecto y generará el plugin.

#### 2-4. Verificando la Compilación

- Después de una compilación exitosa, el archivo del plugin (`spc-integration.dll`) estará disponible en la carpeta de salida (generalmente `Debug` o `Release`).

### Compilación para Linux

#### 1. Requisitos

El entorno de compilación requiere las siguientes herramientas:

- **Docker**: Plataforma para crear, implementar y ejecutar aplicaciones en contenedores. Docker se utiliza para crear un entorno de compilación aislado.
- **CMake**: Herramienta de automatización de compilación que utiliza archivos de configuración para generar archivos de proyecto para diferentes sistemas de compilación.
- **GCC 8**: Compilador GNU C++ utilizado para compilar el código del plugin.

#### 2. Pasos para la Compilación

##### 2-1. Construyendo la Imagen Docker

El proceso comienza navegando a la carpeta `docker` y ejecutando el script `build.sh` para construir la imagen Docker y compilar el plugin. Este script crea un entorno de compilación que contiene todas las dependencias necesarias y realiza la compilación automáticamente.

```bash
cd docker
./build.sh
```

##### 2-2. `build.sh`

El script `build.sh` ejecuta las siguientes operaciones:

```bash
#!/bin/bash

dos2unix "$0" 2>/dev/null || true

if ! command -v docker &> /dev/null; then
    echo "Docker no está instalado. Por favor, instale Docker primero."
    exit 1
fi

PROJECT_ROOT="$(dirname "$(pwd)")"

TEMP_DIR=$(mktemp -d)
echo "Creando directorio temporal de trabajo: $TEMP_DIR"

echo "Copiando los archivos requeridos..."
cp -r \
    "$PROJECT_ROOT"/*.cpp \
    "$PROJECT_ROOT"/*.h \
    "$PROJECT_ROOT/sdk" \
    "$TEMP_DIR/"

mkdir -p "$TEMP_DIR/cmake"

cp "$PROJECT_ROOT/cmake/CMakeLists.txt" "$TEMP_DIR/cmake/"

cp Dockerfile "$TEMP_DIR/";
```

- **Características**:
  - El script verifica la instalación de Docker
  - Crea un directorio temporal para almacenar los archivos necesarios para la compilación
  - Los archivos de código fuente y encabezados se copian al directorio temporal, donde se construirá la imagen Docker

##### 2-3. Construyendo el Plugin

El script `build.sh` gestiona todo el proceso de compilación. Utiliza Docker para crear un entorno aislado y ejecuta el script `compile.sh` automáticamente dentro del contenedor. El proceso incluye:
1. Creación de una imagen Docker con todas las dependencias
2. Ejecución del contenedor con el entorno de compilación
3. Compilación del plugin usando CMake
4. Copia de los archivos compilados a la carpeta `build` en el directorio del proyecto

##### 2-4. `compile.sh`

El script `compile.sh` es responsable de la configuración y compilación del proyecto usando CMake:

```bash
#!/bin/bash

rm -rf ../build
mkdir -p ../build
cd ../build
cmake ../cmake -DCMAKE_BUILD_TYPE=Release
make -j$(nproc) VERBOSE=1
strip -s spc-integration.so
echo "Verificando las dependencias del binario:"
ldd spc-integration.so
```

- **Características**:
    - Elimina cualquier directorio de compilación anterior y crea uno nuevo
    - Utiliza CMake para configurar el proyecto, especificando el tipo de compilación como "Release" para optimizaciones
    - El comando `make` compila el proyecto, utilizando todos los núcleos disponibles (`-j$(nproc)`)
    - Después de la compilación, el plugin es "stripped" para eliminar la información de depuración
    - El script verifica las dependencias del binario generado usando `ldd`

#### 3. Dockerfile

El `Dockerfile` define el entorno de compilación. Ejemplo de configuración típica para este proyecto:

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

- **Características**:
    - **FROM ubuntu:18.04**: Define la imagen base como Ubuntu 18.04
    - **RUN apt-get update && apt-get install -y**: Actualiza la lista de paquetes e instala las dependencias necesarias
    - **WORKDIR /app**: Define el directorio de trabajo dentro del contenedor
    - **COPY . .**: Copia los archivos del directorio actual al directorio de trabajo en el contenedor
    - **RUN cmake . && make**: Ejecuta CMake para compilar el proyecto dentro del contenedor

> [!IMPORTANTE]
> El uso de un Dockerfile garantiza que el entorno de compilación sea reproducible y aislado, evitando conflictos de dependencias que pueden ocurrir en sistemas locales. Este enfoque es especialmente útil cuando diferentes desarrolladores o servidores tienen configuraciones de entorno variadas.

## Licencia

Copyright © **SA-MP Programming Community**

Este software está licenciado bajo los términos de la Licencia Apache, Versión 2.0 ("Licencia"); no puede utilizar este software excepto en conformidad con la Licencia. Puede obtener una copia de la Licencia en: [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)

### Términos y Condiciones de Uso

#### 1. Permisos Concedidos

La presente licencia otorga, de forma gratuita, a cualquier persona que obtenga una copia de este software y archivos de documentación asociados, los siguientes derechos:
* Utilizar, copiar, modificar y distribuir el software en cualquier medio o formato, para cualquier finalidad, comercial o no comercial
* Fusionar, publicar, distribuir, sublicenciar y/o vender copias del software
* Permitir que las personas a quienes se les proporciona el software hagan lo mismo

#### 2. Condiciones Obligatorias

Todas las distribuciones del software o trabajos derivados deben:
* Incluir una copia completa de esta licencia
* Indicar claramente cualquier modificación realizada en el código fuente original
* Preservar todos los avisos de derechos de autor, patentes, marcas registradas y atribuciones
* Proporcionar documentación adecuada de los cambios implementados
* Mantener el aviso de licencia y garantía en todas las copias

#### 3. Restricciones y Limitaciones

* Esta licencia no otorga permiso para usar marcas registradas, logotipos o nombres comerciales de la **SA-MP Programming Community**
* Las contribuciones al código fuente deben ser licenciadas bajo los mismos términos de esta licencia
* El uso de nombres de los contribuyentes para respaldar o promover productos derivados de este software requiere permiso previo específico

#### 4. Propiedad Intelectual

El software y toda la documentación asociada están protegidos por leyes de derechos de autor y tratados internacionales. La **SA-MP Programming Community** retiene todos los derechos, títulos e intereses no expresamente otorgados por esta licencia.

#### 5. Exención de Garantías y Limitación de Responsabilidad

EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍAS DE NINGÚN TIPO, EXPRESAS O IMPLÍCITAS, INCLUYENDO, PERO NO LIMITÁNDOSE A, GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN.

EN NINGÚN CASO LOS AUTORES O TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES POR CUALQUIER RECLAMACIÓN, DAÑOS U OTRAS RESPONSABILIDADES, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE OTRO TIPO, QUE SURJA DE, O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTROS TRATOS EN EL SOFTWARE.

---

Para información detallada sobre la Licencia Apache 2.0, consulte: http://www.apache.org/licenses/LICENSE-2.0
