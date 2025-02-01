# spc-integration

Der **SPC Integration** ist ein Plugin, das für SA-MP (San Andreas Multiplayer) und open.mp (Open Multiplayer) entwickelt wurde. Es sammelt Informationen vom Server, wie IP, Port, Website-URL und eine konfigurierbare Bild-URL. Diese Informationen werden an die Website der SPC (SA-MP Programming Community) gesendet, wo die Serverinformationen gespeichert werden.

## Sprachen

- Português: [README](../../)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Inhaltsverzeichnis

- [spc-integration](#spc-integration)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [Hauptfunktionen](#hauptfunktionen)
    - [1. Sammlung von Serverinformationen](#1-sammlung-von-serverinformationen)
    - [2. URL-Validierung](#2-url-validierung)
    - [3. Integration mit dem Backend](#3-integration-mit-dem-backend)
    - [4. Multiplattform-Kompatibilität](#4-multiplattform-kompatibilität)
  - [Verwendung des Plugins](#verwendung-des-plugins)
    - [1. Download](#1-download)
    - [2. Installation](#2-installation)
    - [3. Konfiguration](#3-konfiguration)
    - [4. Überprüfung](#4-überprüfung)
  - [Projektstruktur](#projektstruktur)
  - [Detaillierte Code-Analyse](#detaillierte-code-analyse)
    - [1. Sammlung von Serverinformationen](#1-sammlung-von-serverinformationen-1)
      - [Hauptstruktur](#hauptstruktur)
      - [Sammlung der Server-IP](#sammlung-der-server-ip)
      - [Lesen des Serverports](#lesen-des-serverports)
      - [Bild- und Website-URLs](#bild--und-website-urls)
      - [Konfigurationsstatus](#konfigurationsstatus)
      - [Initialisierung](#initialisierung)
      - [Hauptmerkmale](#hauptmerkmale)
    - [2. Validierung der Bild-URL](#2-validierung-der-bild-url)
      - [Übersicht der Architektur](#übersicht-der-architektur)
      - [Timeout-geschützte Validierung](#timeout-geschützte-validierung)
      - [Vollständige Validierungspipeline](#vollständige-validierungspipeline)
      - [Validierung der URL-Komponenten](#validierung-der-url-komponenten)
      - [Validierung des Bildinhalts](#validierung-des-bildinhalts)
      - [Multiplattform-Implementierung](#multiplattform-implementierung)
      - [Hauptmerkmale](#hauptmerkmale-1)
    - [3. HTTP-Client](#3-http-client)
      - [Struktur und Funktionsweise](#struktur-und-funktionsweise)
      - [Windows-Implementierung (WinHTTP)](#windows-implementierung-winhttp)
      - [Linux-Implementierung (OpenSSL)](#linux-implementierung-openssl)
      - [Verarbeitung der Antwort](#verarbeitung-der-antwort)
      - [Hauptmerkmale](#hauptmerkmale-2)
    - [4. Base64-Kodierung](#4-base64-kodierung)
      - [Definition der Schnittstelle](#definition-der-schnittstelle)
      - [Base64-Alphabet und Implementierung](#base64-alphabet-und-implementierung)
      - [Initialisierung und Puffer](#initialisierung-und-puffer)
      - [Haupt-Codierungsschleife](#haupt-codierungsschleife)
      - [Padding-Behandlung](#padding-behandlung)
      - [Hauptmerkmale](#hauptmerkmale-3)
    - [5. Logging](#5-logging)
      - [Schnittstellendefinition](#schnittstellendefinition)
      - [Definition des Funktionstyps](#definition-des-funktionstyps)
      - [Deklaration des Funktionszeigers](#deklaration-des-funktionszeigers)
      - [Hauptmerkmale](#hauptmerkmale-4)
    - [6. Plugin-Einstiegspunkt](#6-plugin-einstiegspunkt)
      - [Haupteinstiegsfunktionen](#haupteinstiegsfunktionen)
    - [7. Definitionen und Einbindungen](#7-definitionen-und-einbindungen)
      - [Plugin-Definitionen](#plugin-definitionen)
      - [Basisstruktur der Einbindungen](#basisstruktur-der-einbindungen)
      - [Windows-spezifische Einbindungen](#windows-spezifische-einbindungen)
      - [Unix/Linux-spezifische Einbindungen](#unixlinux-spezifische-einbindungen)
      - [Hauptmerkmale](#hauptmerkmale-5)
  - [Back-End](#back-end)
    - [1. Datenempfang](#1-datenempfang)
    - [2. Anfragenvalidierung](#2-anfragenvalidierung)
    - [3. Verzeichnisvalidierung](#3-verzeichnisvalidierung)
    - [4. URL-Verarbeitung](#4-url-verarbeitung)
    - [5. Datenspeicherung](#5-datenspeicherung)
    - [6. JSON-Dateiformat](#6-json-dateiformat)
    - [7. Backup-System](#7-backup-system)
    - [8. Fehlerbehandlung](#8-fehlerbehandlung)
  - [Wichtige Definitionen](#wichtige-definitionen)
    - [1. BACKEND\_HOST und BACKEND\_PATH](#1-backend_host-und-backend_path)
    - [2. upload\_dir im Backend](#2-upload_dir-im-backend)
    - [Sicherheit und Datenschutz](#sicherheit-und-datenschutz)
  - [Kompilierung](#kompilierung)
    - [Windows-Kompilierung](#windows-kompilierung)
      - [1. Anforderungen](#1-anforderungen)
      - [2. Kompilierungsschritte](#2-kompilierungsschritte)
        - [2-1. Projekt in Visual Studio öffnen](#2-1-projekt-in-visual-studio-öffnen)
        - [2-2. Projekt konfigurieren](#2-2-projekt-konfigurieren)
        - [2-3. Projekt kompilieren](#2-3-projekt-kompilieren)
      - [2-4. Kompilierung überprüfen](#2-4-kompilierung-überprüfen)
    - [Linux-Kompilierung](#linux-kompilierung)
      - [1. Anforderungen](#1-anforderungen-1)
      - [2. Kompilierungsschritte](#2-kompilierungsschritte-1)
        - [2-1. Docker-Image erstellen](#2-1-docker-image-erstellen)
        - [2-2. `build.sh`](#2-2-buildsh)
        - [2-3. Plugin erstellen](#2-3-plugin-erstellen)
        - [2-4. `compile.sh`](#2-4-compilesh)
      - [3. Dockerfile](#3-dockerfile)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Einschränkungen und Beschränkungen](#3-einschränkungen-und-beschränkungen)
      - [4. Geistiges Eigentum](#4-geistiges-eigentum)
      - [5. Gewährleistungsausschluss und Haftungsbeschränkung](#5-gewährleistungsausschluss-und-haftungsbeschränkung)

## Hauptfunktionen

### 1. Sammlung von Serverinformationen
   - Das Plugin sammelt automatisch die IP und den Port des laufenden Servers.
   - Es identifiziert, ob der Server SA-MP oder open.mp ist, und sammelt die entsprechende Website-URL, falls verfügbar.
   - Es ermöglicht die Konfiguration einer benutzerdefinierten Bild-URL über den Parameter `spc_integration_image`, der der Serverkonfigurationsdatei hinzugefügt werden muss.

### 2. URL-Validierung
   - Bevor die Bild-URL an das Backend gesendet wird, validiert das Plugin, ob die bereitgestellte URL erreichbar ist und einem gültigen Bildformat (JPEG, PNG, GIF usw.) entspricht.
   - Dies stellt sicher, dass nur gültige Bild-URLs gesendet werden, wodurch unnötige Erstellungen oder Aktualisierungen im JSON vermieden werden.

### 3. Integration mit dem Backend
   - Das Plugin sendet die gesammelten Informationen über eine HTTP-POST-Anfrage an ein Backend.
   - Das Backend validiert die Anfrage und stellt sicher, dass der bereitgestellte `API_KEY` dem im Backend konfigurierten Schlüssel entspricht. Dies ist entscheidend für die Sicherheit, da es verhindert, dass nicht autorisierte Anfragen verarbeitet werden.
   - Wenn die Daten gültig sind, erstellt das Backend eine JSON-Datei im Format `IP-Port.json`, in der die Serverinformationen gespeichert werden.

### 4. Multiplattform-Kompatibilität
   - Unterstützt die Kompilierung für Linux (mit Docker, CMake und GCC 8) und Windows (mit Visual Studio 2022).
   - Funktioniert sowohl für SA-MP als auch für open.mp, sodass alle Server das Plugin nutzen können.

## Verwendung des Plugins

### 1. Download

- Laden Sie die neueste Version des Plugins im Bereich [releases](https://github.com/spc-samp/spc-integration/releases) herunter.
- Wählen Sie die passende Datei für Ihr Betriebssystem:
  - Windows: `spc-integration.dll`
  - Linux: `spc-integration.so`

### 2. Installation

1. Extrahieren Sie die heruntergeladene Datei.
2. Platzieren Sie das Plugin im `plugins`-Ordner Ihres Servers.
3. Konfigurieren Sie den Server, um das Plugin zu laden:
   - **Für SA-MP**: Fügen Sie in Ihrer `server.cfg` Folgendes hinzu:
     ```
     plugins spc-integration
     ```
   - **Für open.mp**: Fügen Sie `"spc-integration"` zur Liste `legacy_plugins` in Ihrer `config.json` hinzu:
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
> Wenn Sie bereits andere Plugins installiert haben, stellen Sie sicher, dass spc-integration nach ihnen geladen wird.

### 3. Konfiguration

Sie müssen die URL des Bildes konfigurieren, das für Ihren Server angezeigt wird. Wählen Sie eine der folgenden Optionen entsprechend Ihrer Plattform:

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
> Die Bild-URL muss gültig und öffentlich zugänglich sein.

### 4. Überprüfung

1. Starten Sie Ihren Server.
2. Überprüfen Sie die Serverlogs. Wenn Sie eine ähnliche Nachricht wie diese sehen, funktioniert das Plugin korrekt:
    ```
    [SPC Integration]: Information sent to the server data storage of the SPC:
    -- Server IP: '127.0.0.1'
    -- Server Port: '7777'
    -- Image URL configured: 'https://example.com/image.png'
    -- Web URL configured: 'https://example.com'
    ```

## Projektstruktur

Die Projektstruktur ist wie folgt organisiert:
```
└── src/
    ├── cmake/
    │   ├── CMakeLists.txt               // CMake-Konfigurationsdatei
    │   └── compile.sh                   // Kompilierungsskript für Linux
    │
    ├── docker/
    │   ├── build.sh                     // Skript zum Erstellen des Docker-Images
    │   └── Dockerfile                   // Docker-Datei für die Kompilierung unter Linux
    │
    ├── sdk/
    │   └── (SA-MP SDK)                  // SDK, das für die Plugin-Entwicklung benötigt wird
    │
    ├── amx_defines.h                    // AMX-bezogene Definitionen
    ├── base64_encoder.cpp               // Implementierung des Base64-Kodierers
    ├── base64_encoder.h                 // Header des Base64-Kodierers
    ├── http_client.cpp                  // Implementierung des HTTP-Clients
    ├── http_client.h                    // Header des HTTP-Clients
    ├── http_linux.cpp                   // Linux-spezifische Implementierung des HTTP-Clients
    ├── http_response.cpp                // Implementierung der HTTP-Antwort
    ├── http_response.h                  // Header der HTTP-Antwort
    ├── http_windows.cpp                 // Windows-spezifische Implementierung des HTTP-Clients
    ├── inclusions.h                     // Gemeinsame Includes und globale Definitionen
    ├── logger.h                         // Header für das Logging
    ├── main.cpp                         // Einstiegspunkt des Plugins
    ├── plugin_defines.h                 // Plugin-spezifische Definitionen
    ├── server_info.cpp                  // Implementierung zur Sammlung von Serverinformationen
    ├── server_info.h                    // Header zur Sammlung von Serverinformationen
    ├── spc-integration.sln              // Visual Studio-Projektmappendatei
    ├── spc-integration.vcxproj          // Visual Studio-Projektdatei
    ├── spc-integration.vcxproj.filters  // Filterkonfiguration des Visual Studio-Projekts
    ├── url_validator.cpp                // Implementierung des URL-Validierers
    └── url_validator.h                  // Header des URL-Validierers
```

## Detaillierte Code-Analyse

Im Folgenden wird eine detaillierte Analyse der Hauptkomponenten des Codes von **SPC Integration** vorgestellt. Jeder Abschnitt des Codes wird ausführlich erklärt, um das Verständnis der Funktionsweise des Plugins und seiner Integration mit dem Backend zu ermöglichen.

### 1. Sammlung von Serverinformationen

| **Dateien**      |
|-------------------|
| `server_info.h`   |
| `server_info.cpp` |

- Die Klasse `Server_Info` ist für das Sammeln und Verwalten wesentlicher Serverinformationen verantwortlich, einschließlich IP, Port, Integrations-URLs und Website. Das System unterstützt zwei Konfigurationsdateiformate: server.cfg (SA-MP) und config.json (open.mp).

#### Hauptstruktur

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

#### Sammlung der Server-IP

```cpp
bool Server_Info::Get_Server_IP() {
    #ifdef _WIN32
        // Windows: Verwendet WinSock API
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            return false;
            
        char hostname[256];

        if (gethostname(hostname, sizeof(hostname)) == 0) {
            // Code zur Ermittlung der IP unter Windows
            // ...
        }
    #else
        // Linux: Verwendet getifaddrs
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

#### Lesen des Serverports

```cpp
bool Server_Info::Get_Server_Port() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Liest aus der server.cfg (SA-MP)
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
        // Liest aus der config.json (open.mp)
        std::ifstream config(CONFIG_FILE_OPEN);
        std::string json_content((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
        // Verarbeitet JSON, um den Port zu finden
        // ...
    }
    return false;
}
```

#### Bild- und Website-URLs

Das System verwaltet zwei Arten von URLs:
1. Bild-URL (`image_url`): Die URL des Serverbildes.
2. Website-URL (`web_url`): Die URL der Serverwebsite.

```cpp
bool Server_Info::Get_Image_URL() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Sucht nach "spc_integration_image" in der Datei
        if (/* URL gefunden */)
            image_config_status = Config_Status::Success;
        else
            image_config_status = Config_Status::Empty;
    }
    // Ähnlich für CONFIG_FILE_OPEN
}

bool Server_Info::Get_Web_URL() {
    // Ähnlicher Prozess wie Get_ImageURL(), sucht jedoch nach "weburl" oder "website"
}
```

#### Konfigurationsstatus

Das System verwendet Aufzählungen, um den Status der Konfigurationen zu steuern:

```cpp
enum class Config_Status {
    Success,        // Konfiguration gefunden und gültig
    Not_Found,      // Konfiguration nicht gefunden
    Empty,          // Konfiguration gefunden, aber leer
    Web_Not_Found,  // Website-URL nicht gefunden
    Web_Empty       // Website-URL leer
};
```

#### Initialisierung

Der Initialisierungsprozess wird durch die Methode `Initialize()` verwaltet:

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

#### Hauptmerkmale

1. **Sammlung von Informationen**:
    - Automatische Erkennung der Server-IP.
    - Lesen des konfigurierten Ports.
    - Unterstützung für Bild- und Website-URLs.
    - Validierung aller gesammelten Informationen.

2. **Kompatibilität**:
    - Unterstützung für mehrere Betriebssysteme.
    - Kompatibilität mit SA-MP und open.mp.
    - Lesen verschiedener Konfigurationsdateiformate.

3. **Statusverwaltung**:
    - Robustes Status-System für Konfigurationen.
    - Granulare Fehler- und Statuskontrolle.
    - Individuelle Validierung jeder Komponente.

4. **Datenverarbeitung**:
    - Automatische Bereinigung von Strings.
    - Erkennung und Entfernung von Leerzeichen.
    - Validierung von URLs und Konfigurationen.

### 2. Validierung der Bild-URL

| **Dateien**        |
|---------------------|
| `url_validator.h`   |
| `url_validator.cpp` |

- Das URL-Validierungssystem ist eine kritische Sicherheitskomponente, die eine umfassende Validierung von Bild-URLs durch mehrere Überprüfungsebenen durchführt. Es validiert nicht nur das URL-Format, sondern überprüft auch, ob die URL auf eine gültige Bilddatei verweist.

#### Übersicht der Architektur

Der Validierungsprozess wird in der Klasse `URL_Validator` implementiert und folgt einem mehrstufigen Validierungspipeline:

- **Erste Validierung** (`Is_Valid`).
- **Timeout-Verwaltung** (`Validate_With_Timeout`).
- **Vollständiger Validierungsprozess** (`Perform_Full_Validation`).
- **Überprüfung des Bildinhalts** (`Validate_Image_Headers`).

#### Timeout-geschützte Validierung

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
    // ... Ausnahmebehandlung
}
```

- Das System implementiert einen Timeout-Mechanismus mit `std::async`, um Hänger bei langsamen oder nicht reagierenden URLs zu vermeiden. Der Validierungsprozess schlägt automatisch fehl, wenn `VALIDATION_TIMEOUT` Sekunden (im Code auf 10 Sekunden festgelegt) überschritten werden.

#### Vollständige Validierungspipeline

Die Methode `Perform_FullValidation` implementiert eine Reihe von Überprüfungen:

```cpp
bool URL_Validator::Perform_Full_Validation(const std::string& url) {
    // Längenvalidierung
    if (url.empty() || url.length() > 2048)
        return (Log_Printf("[SPC Integration]: Error: URL is empty or too long (maximum 2048 characters)."), false);

    // Protokollvalidierung
    if (!Has_Valid_Scheme(url))
        return (Log_Printf("[SPC Integration]: Error: URL must start with 'http://' or 'https://'."), false);

    // Strukturvalidierung
    if (!Has_Valid_HostAndPath(url))
        return (Log_Printf("[SPC Integration]: Error: URL must contain a valid hostname and path."), false);

    // Zeichenvalidierung
    if (!Has_Valid_Characters(url))
        return (Log_Printf("[SPC Integration]: Error: URL contains invalid characters."), false);

    // Bildvalidierung
    if (!Validate_Image_Headers(url))
        return (Log_Printf("[SPC Integration]: Error: The URL content is not a valid image."), false);

    Log_Printf("[SPC Integration]: Validation successfully completed!");

    return true;
}
```

#### Validierung der URL-Komponenten

Das System enthält spezialisierte Validierer für verschiedene URL-Komponenten:

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

#### Validierung des Bildinhalts

Das System führt die eigentliche Bildvalidierung durch, indem es die Dateiköpfe überprüft:

```cpp
bool URL_Validator::Check_Image_Magic_Numbers(const std::vector<unsigned char>& data) {
    if (data.size() < 4)
        return false;

    // Unterstützt mehrere Bildformate:
    // JPEG: FF D8 FF
    if (data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF)
        return true;

    // PNG: 89 50 4E 47 0D 0A 1A 0A
    if (data.size() >= 8 && data[0] == 0x89 && data[1] == 0x50 /* ... */)
        return true;

    // Weitere Formate: GIF, BMP, WebP
    // ...
}
```

#### Multiplattform-Implementierung

Das System enthält plattformspezifische Implementierungen zum Abrufen von Bilddaten:

- **Windows**: Verwendet die WinHTTP-API (`Fetch_Image_Data_Windows`).
- **Linux**: Verwendet OpenSSL und Socket-Programmierung (`Fetch_Image_Data_Linux`).

Beide Implementierungen:
- Stellen sichere Verbindungen (HTTPS) her.
- Fordern nur den Bildkopf (die ersten 16 Bytes) an.
- Verwalten die Bereinigung von Verbindungen und Ressourcen.

#### Hauptmerkmale

1. **Umfassende Validierung**:
    - Format und Struktur der URL.
    - Protokollsicherheit (HTTPS-Unterstützung).
    - Domain- und Pfadvalidierung.
    - Zeichensatzvalidierung.
    - Bildformatüberprüfung.

2. **Sicherheitsfunktionen**:
    - Schutz vor Timeout.
    - Maximale URL-Längenbegrenzung.
    - Sichere Multiplattform-Verbindungen.
    - Effiziente Speichervalidierung von Bildern.

3. **Unterstützte Bildformate**:
    - JPEG
    - PNG
    - GIF
    - BMP
    - WebP

4. **Fehlerbehandlung**:
    - Detaillierte Protokollierung in jeder Validierungsphase.
    - Elegante Timeout-Verwaltung.
    - Plattformspezifische Fehlerbehandlung.
    - Ressourcenbereinigung in allen Szenarien.

### 3. HTTP-Client

| **Dateien**        |
|---------------------|
| `http_client.h`     |
| `http_client.cpp`   |
| `http_windows.cpp`  |
| `http_linux.cpp`    |
| `http_response.h`   |
| `http_response.cpp` |

- Der HTTP-Client ist für das Senden der gesammelten Informationen an das Backend über HTTPS verantwortlich. Die Implementierung ist plattformübergreifend und verwendet WinHTTP unter Windows und OpenSSL/Sockets unter Linux, um eine sichere Kommunikation über SSL/TLS zu gewährleisten.

#### Struktur und Funktionsweise

Die Hauptdatei `http_client.h` definiert die Schnittstelle der Klasse:

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

Die Implementierung in `http_client.cpp` wählt automatisch die richtige Implementierung aus:

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

#### Windows-Implementierung (WinHTTP)

In `http_windows.cpp` verwendet die Implementierung die WinHTTP-API:

```cpp
bool HTTP_Client::Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data) {
    HINTERNET spc_session = WinHttpOpen(L"SPC-INTEGRATION/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    // Timeout von 60 Sekunden konfigurieren
    DWORD timeout = 60000;

    WinHttpSetOption(spc_session, WINHTTP_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

    // Verbindung herstellen und HTTPS-Anfrage senden
    HINTERNET spc_connect = WinHttpConnect(spc_session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    
    // ... Rest der Windows-Implementierung
}
```

#### Linux-Implementierung (OpenSSL)

In `http_linux.cpp` verwendet die Implementierung OpenSSL mit Sockets:

```cpp
bool HTTP_Client::Send_Request_Linux(const std::string& host, const std::string& path, const std::string& data) {
    // OpenSSL initialisieren
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // SSL-Kontext konfigurieren
    const SSL_METHOD* method = SSLv23_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    // Socket erstellen und konfigurieren
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;

    // ... Rest der Linux-Implementierung
}
```

#### Verarbeitung der Antwort

Die Klasse `HTTP_Response` in `http_response.h` verarbeitet die Serverantworten:

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

Die Implementierung in `http_response.cpp` behandelt verschiedene Antworttypen:

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
    // ... andere Fehlertypen

    Log_Printf("%s %s: %s", prefix, error_prefix, message.c_str());
}
```

#### Hauptmerkmale

1. **Sichere Kommunikation**:
    - HTTPS (Port 443) mit SSL/TLS.
    - Timeout von 60 Sekunden für Verbindung, Senden und Empfangen.
    - Content-Type: `application/x-www-form-urlencoded` mit UTF-8.

2. **Fehlerbehandlung**:
    - Überprüft jeden Schritt der Kommunikation.
    - Gibt Ressourcen ordnungsgemäß frei.
    - Detaillierte Protokollierung nach Fehlertyp:
        - Serverfehler: Empfiehlt die Überprüfung der Konfiguration.
        - Authentifizierungsfehler: Zeigt an, dass der API-Schlüssel überprüft werden sollte.
        - Validierungsfehler: Empfiehlt die Überprüfung der Konfiguration.

3. **JSON-Antwortformat**:
    ```json
    {
        "success": true/false,
        "message": "Antwortnachricht"
    }
    ```

### 4. Base64-Kodierung

| **Dateien**         |
|----------------------|
| `base64_encoder.h`   |
| `base64_encoder.cpp` |

- Die Base64-Kodierung wird verwendet, um die Bild-URL zu kodieren, bevor sie an das Backend gesendet wird. Dies ist besonders nützlich, wenn die URL Sonderzeichen enthält, die in einer HTTP-Anfrage möglicherweise nicht korrekt behandelt werden.

#### Definition der Schnittstelle

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

- Die Schnittstelle wird mit Inklusionswächtern definiert, um Mehrfachdefinitionen zu vermeiden. Die Klasse verwendet eine statische Methode `Encode`, die einen String als Eingabe akzeptiert und die kodierte Version zurückgibt.

#### Base64-Alphabet und Implementierung

```cpp
#include "base64_encoder.h"

const std::string Base64_Encoder::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
```

- Das Base64-Alphabet wird als konstante Zeichenkette definiert, die 64 verschiedene Zeichen enthält. Diese Zeichenkette wird während des Kodierungsprozesses als Nachschlagetabelle verwendet.

#### Initialisierung und Puffer

```cpp
// ... "Base64-Alphabet und Implementierung" ...

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

- Es werden zwei Zeichenarrays initialisiert: eines zur Speicherung der 3 Eingabebytes und eines für die 4 resultierenden Base64-Zeichen. Der Eingabestring wird in ein Zeichenarray konvertiert, um byteweise verarbeitet zu werden.

#### Haupt-Codierungsschleife

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Initialisierung und Puffer" ...

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

- Die Hauptschleife verarbeitet die Eingabe in Gruppen von 3 Bytes und konvertiert sie durch Bitoperationen in 4 Base64-Zeichen. Jede 24-Bit-Gruppe wird in vier 6-Bit-Gruppen aufgeteilt.

#### Padding-Behandlung

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Haupt-Codierungsschleife" ...

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

- Für Eingaben, die keine Vielfachen von 3 Bytes sind, muss Padding hinzugefügt werden. Die restlichen Bytes werden mit Nullen aufgefüllt und codiert, und das '='-Zeichen wird hinzugefügt, um die 4-Zeichen-Gruppe zu vervollständigen.

#### Hauptmerkmale

1. **Datenverarbeitung**:
    - Umwandlung von 3-Byte-Gruppen in 4 Base64-Zeichen.
    - Bitweise Manipulation zur präzisen Werteextraktion.
    - Automatische Padding-Behandlung für Größen, die keine Vielfachen von 3 sind.

2. **Design und Architektur**:
    - Modulare Implementierung mit klarer Trennung der Verantwortlichkeiten.
    - Verwendung statischer Methoden für einfachen Zugriff.
    - Kapselung des Base64-Alphabets als privates Mitglied.

3. **Optimierung und Leistung**:
    - Effiziente Byte-für-Byte-Verarbeitung.
    - Verwendung fester Arrays zur Minimierung von Speicherallokationen.
    - Optimierte Bitoperationen für schnelle Konvertierung.

4. **Robustheit und Zuverlässigkeit**:
    - Sichere Handhabung von Strings beliebiger Größe.
    - Garantie für immer gültige Base64-Ausgabe.
    - Erhaltung der Datenintegrität während der Codierung.

### 5. Logging

| **Dateien** |
|-------------|
| `logger.h`  |

- Das Logging-System ist ein grundlegender Teil des Plugins, da es Entwicklern ermöglicht, das Verhalten des Plugins zu überwachen und Probleme zu identifizieren. Die Verwendung von Logs hilft bei der Fehlersuche und Wartung des Codes.

#### Schnittstellendefinition

```cpp
#ifndef LOGGER_H
    #define LOGGER_H

    typedef void (*Log_Printf_t)(const char* Format, ...);
    extern Log_Printf_t Log_Printf;
#endif
```

- Das Logging-System wird über einen Funktionszeiger definiert, der variable Argumente verwendet und Flexibilität bei der Nachrichtenformatierung ermöglicht. Die `extern`-Deklaration zeigt an, dass die tatsächliche Implementierung der Funktion zur Laufzeit bereitgestellt wird.

#### Definition des Funktionstyps

```cpp
typedef void (*Log_Printf_t)(const char* Format, ...);
```

Der Typ `Log_Printf_t` definiert die Signatur der Logging-Funktion:
- `void`: Die Funktion gibt keinen Wert zurück
- `const char* Format`: Erster Parameter ist ein Formatstring
- `...`: Ermöglicht variable Argumente für dynamische Formatierung

#### Deklaration des Funktionszeigers

```cpp
extern Log_Printf_t Log_Printf;
```

Der `Log_Printf`-Zeiger wird als extern deklariert, wodurch:
- Die tatsächliche Implementierung von der Host-Anwendung bereitgestellt werden kann.
- Das Plugin die bestehende Logging-Infrastruktur nutzen kann.
- Die Nachrichten in das Haupt-Logging-System integriert werden können.

#### Hauptmerkmale

1. **Implementierungsflexibilität**:
    - Unterstützung variabler Argumente für dynamische Formatierung.
    - Möglichkeit der Integration mit verschiedenen Logging-Systemen.
    - Implementierung kann zur Laufzeit bereitgestellt werden.

2. **Integration mit dem Host-System**:
    - Nutzung der bestehenden Logging-Infrastruktur.
    - Nachrichten können an verschiedene Ausgaben geleitet werden.
    - Konsistenz mit dem Logging der Hauptanwendung.

3. **Benutzerfreundlichkeit**:
    - Einfache und vertraute Schnittstelle (ähnlich printf).
    - Kann in jedem Teil des Codes verwendet werden.
    - Keine zusätzliche Konfiguration im Plugin-Code erforderlich.

### 6. Plugin-Einstiegspunkt

| **Dateien** |
|-------------|
| `main.cpp`  |

- Der Plugin-Einstiegspunkt ist der Startpunkt der Plugin-Ausführung. Diese Datei ist verantwortlich für:
    - Initialisierung wesentlicher AMX-Funktionen.
    - Sammeln und Validieren von Serverinformationen.
    - Überprüfen der Einstellungen in server.cfg/config.json.
    - Senden von Daten an das SPC-Backend.

#### Haupteinstiegsfunktionen

```cpp
// Initiales Laden des Plugins
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** Plugin_Data) {
    // Initialisiert AMX-Funktionen und Logging-System
    // Sammelt Serverinformationen
    // Validiert Bild- und Website-URLs
    // Sendet Daten ans Backend
    // Zeigt Statusinformationen an
}

// Entladen des Plugins
PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    // Beendet das Plugin
}

// Unterstützte Funktionen
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

// Laden von AMX-Skripten
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* Amx) {
    return AMX_ERR_NONE;
}

// Entladen von AMX-Skripten
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* Amx) {
    return AMX_ERR_NONE;
}
```

1. **Initialisierungsprozess**:
    - Initialisiert wesentliche AMX-Funktionen und das Logging-System.
    - Sammelt Serverinformationen über die `Server_Info`-Klasse.
    - Überprüft das Vorhandensein und die Gültigkeit der Parameter:
        - `spc_integration_image` in der Konfigurationsdatei.
        - `weburl/website` in der Konfigurationsdatei.
    - Validiert die bereitgestellten URLs.
    - Versucht, die Daten an das Backend zu senden (erst als "create", dann als "update" falls nötig).
    - Zeigt detaillierte Informationen über den Initialisierungsstatus an.

2. **Validierungen und Überprüfungen**:
    - Überprüft das Vorhandensein und die Gültigkeit der Bild-URL.
    - Überprüft das Vorhandensein und die Gültigkeit der Website-URL.
    - Validiert die URLs mit der `URL_Validator`-Klasse.
    - Versucht automatische Wiederverbindung bei initialem Sendefehler.

3. **Feedback und Logging**:
    - Zeigt ein informatives Banner mit Plugin-Details und sozialen Links an.
    - Liefert detaillierte Meldungen über Konfigurationsfehler.
    - Zeigt den finalen Initialisierungsstatus mit Serverinformationen an.

### 7. Definitionen und Einbindungen

| **Dateien**          |
|---------------------|
| `plugin_defines.h`  |
| `inclusions.h`      |

- Diese Dateien enthalten Definitionen und Einbindungen, die für das Funktionieren des Plugins notwendig sind, und legen wichtige Konstanten fest sowie gewährleisten plattformübergreifende Kompatibilität.

#### Plugin-Definitionen

```cpp
#ifndef PLUGIN_DEFINES_H
    #define PLUGIN_DEFINES_H
    
    #define PLUGIN_VERSION "1.0.0"
    #define BACKEND_HOST "example_site.com" // Ohne das 'https://' oder 'http://' Protokoll.
    #define BACKEND_PATH "/backend_directory/spc-integration.php"
    #define API_KEY "YOUR_SECURE_KEY_TO_ACCESS_PHP"
    #define CONFIG_FILE_SAMP "server.cfg"
    #define CONFIG_FILE_OPEN "config.json"
#endif
```

Die Definitionsdatei enthält wichtige Konstanten für das Funktionieren des Plugins:
- Plugin-Version.
- Backend-Konfigurationen für die Kommunikation.
- API-Schlüssel für die Authentifizierung.
- Namen der Konfigurationsdateien.

#### Basisstruktur der Einbindungen

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

Einbindung der benötigten C++-Standardbibliotheken für:
- String- und Dateimanipulation.
- Reguläre Ausdrücke.
- Asynchrone Operationen.
- Zeitmanipulation.

#### Windows-spezifische Einbindungen

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

Spezifische Unterstützung für Windows-Systeme:
- Windows-Netzwerk-APIs.
- Windows-HTTP-Bibliotheken.
- Linking-Konfigurationen.

#### Unix/Linux-spezifische Einbindungen

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

Spezifische Unterstützung für Unix/Linux-Systeme:
- POSIX-Netzwerk-APIs.
- SSL-Unterstützung über OpenSSL.
- Netzwerkschnittstellen.

#### Hauptmerkmale

1. **Backend-Konfiguration**:
    - Konfigurierbarer Host und Pfad für Implementierungsflexibilität.
    - API-Schlüssel für sichere Authentifizierung.
    - Explizite Plugin-Versionierung.

2. **Plattformübergreifende Kompatibilität**:
    - Native Unterstützung für Windows und Unix/Linux.
    - Abstraktion systemspezifischer APIs.
    - Bedingte Implementierungen für jede Plattform.

3. **Sicherheit und Kommunikation**:
    - SSL/TLS-Unterstützung für sichere Kommunikation.
    - Authentifizierung über API-Schlüssel.
    - Robuste Netzwerkbibliotheken.

4. **Ressourcenmanagement**:
    - Unterstützung für asynchrone Operationen.
    - Effiziente String- und Dateimanipulation.
    - Zeit- und Timing-Kontrolle.

## Back-End

Das Backend ist dafür verantwortlich, die vom Plugin gesendeten Informationen zu empfangen und in einer JSON-Datei zu speichern. Hier ist eine detaillierte Erklärung seiner Funktionsweise:

### 1. Datenempfang
  - Das Plugin sendet eine HTTP POST-Anfrage mit den Serverinformationen (IP, Port, Website-URL und Bild-URL).
  - Das Backend validiert die Anfrage und stellt sicher, dass der bereitgestellte `API_KEY` dem im Backend konfigurierten Schlüssel entspricht.
  - Dies ist für die Sicherheit wichtig, da es verhindert, dass nicht autorisierte Anfragen verarbeitet werden.
  - Unterstützt URLs sowohl im normalen Format als auch in Base64-kodierter Form.

### 2. Anfragenvalidierung
   - Das Backend überprüft, ob der in der Anfrage bereitgestellte `API_KEY` gültig ist.
   - Verwendet die Funktion `hash_equals()` für sicheren Schlüsselvergleich.
   - Wenn der Schlüssel ungültig ist, wird ein Authentifizierungsfehler zurückgegeben.
   - Der folgende Code veranschaulicht diese Validierung:
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

### 3. Verzeichnisvalidierung
  - Überprüft das Vorhandensein der erforderlichen Verzeichnisse:
      - `exemple_directory` als Basisverzeichnis.
      - `exemple_servers` als Speicherort.
  - Bestätigt die Schreibberechtigungen im Upload-Verzeichnis.
  - Gibt spezifische Fehlermeldungen zurück, wenn eine Validierung fehlschlägt.

### 4. URL-Verarbeitung
   - Spezifische Funktionen zur Verarbeitung von Bild- und Web-URLs.
   - Unterstützung für normale und Base64-kodierte URLs.
   - Validierung der Base64-Dekodierung bei Verwendung.
   - Fehlerbehandlung für ungültige URLs.

### 5. Datenspeicherung
   - Erstellt eindeutige JSON-Dateien im Format `IP-Port.json`.
   - Bereinigt Dateinamen für Sicherheit.
   - Setzt entsprechende Berechtigungen (chmod 0644).
   - Implementiert Backup-System für Aktualisierungen.
   - Der folgende Code zeigt den Speicherprozess:
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

### 6. JSON-Dateiformat
   - Klare und organisierte Datenstruktur.
   - Verwendet Pretty-Print-Formatierung für bessere Lesbarkeit.
   - Behält URL-Formatierung mit nicht-escapeten Schrägstrichen bei.
   - Beispiel für JSON-Dateiinhalt:
        ```json
        {
            "spc_integration_image": "https://example.com/image.png",
            "spc_web_url": "https://example.com"
        }
        ```

### 7. Backup-System
   - Erstellt automatisches Backup vor Aktualisierungen.
   - Stellt Originaldaten bei Fehler wieder her.
   - Entfernt Backup-Dateien nach erfolgreichen Operationen.
   - Gewährleistet Datenintegrität während Aktualisierungen.

### 8. Fehlerbehandlung
   - Detaillierte und spezifische Fehlermeldungen.
   - Validierungen in jedem Prozessschritt.
   - Konsistente Antworten im JSON-Format.
   - Behandelte Fehlertypen:
       - Authentifizierungsfehler.
       - Verzeichnisprobleme.
       - Dateivorgangsfehler.
       - Validierungsfehler.
       - HTTP-Methodenbeschränkungen.

## Wichtige Definitionen

### 1. BACKEND_HOST und BACKEND_PATH

In der Datei `plugin_defines.h` finden Sie die folgenden Definitionen:

```cpp
#define BACKEND_HOST "example_site.com" // Ohne das Protokoll 'https://' oder 'http://'
#define BACKEND_PATH "/backend_directory/spc-integration.php"
```

- **BACKEND_HOST**: Diese Definition repräsentiert die Adresse des Servers, auf dem das Backend gehostet wird. Im Kontext des Plugins ist dies der Ort, an den die Serverinformationen gesendet werden. Wichtig ist zu beachten, dass die SPC aus Sicherheitsgründen die tatsächliche Backend-Adresse nicht offenlegt. Dies dient dem Schutz der Integrität und Sicherheit der Daten und verhindert, dass sensible Informationen offengelegt werden.

- **BACKEND_PATH**: Diese Definition spezifiziert den Pfad des PHP-Skripts, das die vom Plugin gesendeten Anfragen verarbeitet. Der Pfad muss vom `BACKEND_HOST` aus zugänglich sein und muss für die Annahme von POST-Anfragen konfiguriert sein. Das PHP-Skript ist für die Validierung der empfangenen Daten und deren Speicherung in einer JSON-Datei verantwortlich.

### 2. upload_dir im Backend

Im PHP-Skript (`spc-integration.php`) wird die Variable `upload_dir` wie folgt definiert:

```php
$upload_dir = $base_dir . '/exemple_directory/exemple_servers/';
```

- **upload_dir**: Dieses Verzeichnis ist der Ort, an dem die JSON-Dateien mit den Serverinformationen gespeichert werden. Das Backend überprüft, ob dieses Verzeichnis existiert und beschreibbar ist, bevor es versucht, Dateien zu erstellen oder zu modifizieren. Wenn das Verzeichnis nicht existiert oder nicht beschreibbar ist, gibt das Backend einen Fehler zurück und informiert darüber, dass die Daten nicht gespeichert werden konnten.

### Sicherheit und Datenschutz

Die SPC priorisiert die Sicherheit und den Schutz der Daten. Deshalb werden die tatsächliche Backend-Adresse und der `API_KEY` nicht öffentlich zugänglich gemacht. Das kompilierte Plugin, das unter [releases](https://github.com/spc-samp/spc-integration/releases) verfügbar ist, verwendet die SPC-Adresse und den `API_KEY`, um die Serverinformationen sicher zu speichern. Dies gewährleistet, dass nur autorisierte Anfragen verarbeitet werden und die Serverdaten vor unbefugtem Zugriff geschützt sind.

## Kompilierung

Das **SPC Integration** kann in Windows- und Linux-Umgebungen kompiliert werden. Dieser Abschnitt beschreibt detailliert den Kompilierungsprozess, einschließlich der Umgebungskonfiguration, der Verwendung von Docker, CMake und Kompilierungsskripten.

### Windows-Kompilierung

#### 1. Anforderungen

Zur Kompilierung des Plugins in einer Windows-Umgebung wird benötigt:

- **Visual Studio 2022**: Visual Studio muss mit C++-Unterstützung installiert sein, wobei die Option für Desktop-Entwicklung mit C++ während der Installation ausgewählt wurde.

#### 2. Kompilierungsschritte

##### 2-1. Projekt in Visual Studio öffnen

1. Visual Studio 2022 öffnen.
2. Zur Datei `spc-integration.sln` im Projekt navigieren und öffnen.
3. Visual Studio lädt das Projekt und seine Einstellungen.

##### 2-2. Projekt konfigurieren

- Die C++-Version sollte in den Projekteinstellungen unter **Project Properties** > **Configuration Properties** > **C/C++** > **Language** > **C++ Language Standard** auf C++17 eingestellt sein.

##### 2-3. Projekt kompilieren

- Mit konfiguriertem Projekt "Build" im oberen Menü auswählen und "Build Solution" wählen oder `Strg + Umschalt + B` drücken.
- Visual Studio wird das Projekt kompilieren und das Plugin generieren.

#### 2-4. Kompilierung überprüfen

- Nach erfolgreicher Kompilierung wird die Plugin-Datei (`spc-integration.dll`) im Ausgabeordner verfügbar sein (normalerweise `Debug` oder `Release`).

### Linux-Kompilierung

#### 1. Anforderungen

Die Kompilierungsumgebung erfordert folgende Werkzeuge:

- **Docker**: Plattform zum Erstellen, Bereitstellen und Ausführen von Anwendungen in Containern. Docker wird verwendet, um eine isolierte Kompilierungsumgebung zu erstellen.
- **CMake**: Build-Automatisierungstool, das Konfigurationsdateien verwendet, um Projektdateien für verschiedene Build-Systeme zu generieren.
- **GCC 8**: GNU C++-Compiler, der zur Kompilierung des Plugin-Codes verwendet wird.

#### 2. Kompilierungsschritte

##### 2-1. Docker-Image erstellen

Der Prozess beginnt mit der Navigation zum Ordner `docker` und der Ausführung des Skripts `build.sh`, um das Docker-Image zu erstellen und das Plugin zu kompilieren. Dieses Skript erstellt eine Kompilierungsumgebung mit allen erforderlichen Abhängigkeiten und führt die Kompilierung automatisch durch.

```bash
cd docker
./build.sh
```

##### 2-2. `build.sh`

Das Skript `build.sh` führt folgende Operationen aus:

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

cp "$PROJECT_ROOT/cmake/CMakeLists.txt" "$TEMP_DIR/cmake/"

cp Dockerfile "$TEMP_DIR/";
```

- **Eigenschaften**:
  - Das Skript überprüft die Docker-Installation
  - Erstellt ein temporäres Verzeichnis zur Speicherung der für die Kompilierung erforderlichen Dateien
  - Quellcode- und Header-Dateien werden in das temporäre Verzeichnis kopiert, wo das Docker-Image erstellt wird

##### 2-3. Plugin erstellen

Das Skript `build.sh` verwaltet den gesamten Kompilierungsprozess. Es verwendet Docker, um eine isolierte Umgebung zu erstellen und führt das Skript `compile.sh` automatisch innerhalb des Containers aus. Der Prozess umfasst:
1. Erstellung eines Docker-Images mit allen Abhängigkeiten
2. Ausführung des Containers mit der Kompilierungsumgebung
3. Kompilierung des Plugins mittels CMake
4. Kopieren der kompilierten Dateien in den Ordner `build` im Projektverzeichnis

##### 2-4. `compile.sh`

Das Skript `compile.sh` ist für die Konfiguration und Kompilierung des Projekts mit CMake verantwortlich:

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

- **Eigenschaften**:
    - Entfernt vorherige Build-Verzeichnisse und erstellt ein neues
    - Verwendet CMake zur Projektkonfiguration, spezifiziert den Build-Typ als "Release" für Optimierungen
    - Der `make`-Befehl kompiliert das Projekt unter Verwendung aller verfügbaren Kerne (`-j$(nproc)`)
    - Nach der Kompilierung wird das Plugin "gestrippt", um Debug-Informationen zu entfernen
    - Das Skript überprüft die Binärabhängigkeiten mit `ldd`

#### 3. Dockerfile

Das `Dockerfile` definiert die Kompilierungsumgebung. Typisches Konfigurationsbeispiel für dieses Projekt:

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

- **Eigenschaften**:
    - **FROM ubuntu:18.04**: Definiert Ubuntu 18.04 als Basis-Image
    - **RUN apt-get update && apt-get install -y**: Aktualisiert die Paketliste und installiert erforderliche Abhängigkeiten
    - **WORKDIR /app**: Definiert das Arbeitsverzeichnis im Container
    - **COPY . .**: Kopiert Dateien aus dem aktuellen Verzeichnis in das Arbeitsverzeichnis im Container
    - **RUN cmake . && make**: Führt CMake aus, um das Projekt im Container zu kompilieren

> [!IMPORTANT]
> Die Verwendung eines Dockerfiles gewährleistet, dass die Kompilierungsumgebung reproduzierbar und isoliert ist, wodurch Abhängigkeitskonflikte vermieden werden, die in lokalen Systemen auftreten können. Dieser Ansatz ist besonders nützlich, wenn verschiedene Entwickler oder Server unterschiedliche

## Lizenz

Copyright © **SA-MP Programming Community**

Diese Software ist unter den Bedingungen der Apache-Lizenz Version 2.0 (die "Lizenz") lizenziert; Sie dürfen diese Software nur in Übereinstimmung mit der Lizenz verwenden. Eine Kopie der Lizenz erhalten Sie unter: [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)

### Nutzungsbedingungen

#### 1. Gewährte Berechtigungen

Diese Lizenz gewährt jeder Person, die eine Kopie dieser Software und der zugehörigen Dokumentationsdateien erhält, kostenlos folgende Rechte:
* Die Software in jedem Medium oder Format für jeden Zweck, kommerziell oder nicht-kommerziell, zu nutzen, zu kopieren, zu modifizieren und zu verteilen
* Die Software zu verschmelzen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder Kopien zu verkaufen
* Personen, denen die Software zur Verfügung gestellt wird, dies ebenfalls zu ermöglichen

#### 2. Verpflichtende Bedingungen

Alle Verteilungen der Software oder abgeleiteten Werke müssen:
* Eine vollständige Kopie dieser Lizenz enthalten
* Alle Änderungen am ursprünglichen Quellcode deutlich kennzeichnen
* Alle Urheberrechts-, Patent-, Marken- und Zuordnungshinweise bewahren
* Angemessene Dokumentation der implementierten Änderungen bereitstellen
* Den Lizenz- und Gewährleistungshinweis in allen Kopien beibehalten

#### 3. Einschränkungen und Beschränkungen

* Diese Lizenz gewährt keine Erlaubnis zur Nutzung von Markenzeichen, Logos oder Handelsnamen der **SA-MP Programming Community**
* Beiträge zum Quellcode müssen unter denselben Bedingungen dieser Lizenz lizenziert werden
* Die Verwendung von Namen der Mitwirkenden zur Befürwortung oder Bewerbung von aus dieser Software abgeleiteten Produkten erfordert eine spezifische vorherige Genehmigung

#### 4. Geistiges Eigentum

Die Software und alle zugehörige Dokumentation sind durch Urheberrechtsgesetze und internationale Verträge geschützt. Die **SA-MP Programming Community** behält sich alle Rechte, Titel und Interessen vor, die nicht ausdrücklich durch diese Lizenz gewährt werden.

#### 5. Gewährleistungsausschluss und Haftungsbeschränkung

DIE SOFTWARE WIRD "WIE BESEHEN" OHNE JEGLICHE AUSDRÜCKLICHE ODER IMPLIZIERTE GEWÄHRLEISTUNG BEREITGESTELLT, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTFÄHIGKEIT, DER EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND DER NICHTVERLETZUNG VON RECHTEN DRITTER.

IN KEINEM FALL HAFTEN DIE AUTOREN ODER URHEBERRECHTSINHABER FÜR ANSPRÜCHE, SCHÄDEN ODER ANDERE VERPFLICHTUNGEN, OB IN EINER VERTRAGS- ODER HAFTUNGSKLAGE, EINER UNERLAUBTEN HANDLUNG ODER ANDERWEITIG, DIE SICH AUS ODER IN VERBINDUNG MIT DER SOFTWARE ODER DER NUTZUNG ODER ANDEREN GESCHÄFTEN MIT DER SOFTWARE ERGEBEN.

---

Für detaillierte Informationen zur Apache License 2.0 besuchen Sie: http://www.apache.org/licenses/LICENSE-2.0