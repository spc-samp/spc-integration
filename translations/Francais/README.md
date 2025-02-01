# spc-integration

Le **SPC Integration** est un plugin développé pour SA-MP (San Andreas Multiplayer) et open.mp (Open Multiplayer) qui collecte les informations du serveur, telles que l'IP, le port, l'URL du site et une URL d'image configurable. Ces informations sont envoyées au site SPC (SA-MP Programming Community), où les informations des serveurs sont stockées.

## Langues

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Index

- [spc-integration](#spc-integration)
  - [Langues](#langues)
  - [Index](#index)
  - [Fonctionnalités Principales](#fonctionnalités-principales)
    - [1. Collecte d'Informations du Serveur](#1-collecte-dinformations-du-serveur)
    - [2. Validation d'URL](#2-validation-durl)
    - [3. Intégration avec le Backend](#3-intégration-avec-le-backend)
    - [4. Compatibilité Multiplateforme](#4-compatibilité-multiplateforme)
  - [Comment utiliser le Plugin](#comment-utiliser-le-plugin)
    - [1. Téléchargement](#1-téléchargement)
    - [2. Installation](#2-installation)
    - [3. Configuration](#3-configuration)
    - [4. Vérification](#4-vérification)
  - [Structure du Projet](#structure-du-projet)
  - [Détail des Codes](#détail-des-codes)
    - [1. Collecte d'Informations du Serveur](#1-collecte-dinformations-du-serveur-1)
      - [Structure Principale](#structure-principale)
      - [Collecte de l'IP du Serveur](#collecte-de-lip-du-serveur)
      - [Lecture du Port du Serveur](#lecture-du-port-du-serveur)
      - [URLs d'image et Site Web](#urls-dimage-et-site-web)
      - [Statut de Configuration](#statut-de-configuration)
      - [Initialisation](#initialisation)
      - [Caractéristiques Principales](#caractéristiques-principales)
    - [2. Validation d'URL d'image](#2-validation-durl-dimage)
      - [Vue d'ensemble de l'Architecture](#vue-densemble-de-larchitecture)
      - [Validation Protégée par Timeout](#validation-protégée-par-timeout)
      - [Pipeline de Validation Complète](#pipeline-de-validation-complète)
      - [Validation des Composants de l'URL](#validation-des-composants-de-lurl)
      - [Validation du Contenu de l'Image](#validation-du-contenu-de-limage)
      - [Mise en œuvre multiplateforme](#mise-en-œuvre-multiplateforme)
      - [Caractéristiques principales](#caractéristiques-principales-1)
    - [3. Client HTTP](#3-client-http)
      - [Structure et fonctionnement](#structure-et-fonctionnement)
      - [Implémentation Windows (WinHTTP)](#implémentation-windows-winhttp)
      - [Implémentation Linux (OpenSSL)](#implémentation-linux-openssl)
      - [Traitement de la Réponse](#traitement-de-la-réponse)
      - [Caractéristiques principales](#caractéristiques-principales-2)
    - [4. Codification Base64](#4-codification-base64)
      - [Définition de l'Interface](#définition-de-linterface)
      - [Alphabet Base64 et Implémentation](#alphabet-base64-et-implémentation)
      - [Initialisation et Tampons](#initialisation-et-tampons)
      - [Boucle Principale de Codification](#boucle-principale-de-codification)
      - [Traitement du Padding](#traitement-du-padding)
      - [Caractéristiques Principales](#caractéristiques-principales-3)
    - [5. Journalisation](#5-journalisation)
      - [Définition de l'Interface](#définition-de-linterface-1)
      - [Définition du Type de la Fonction](#définition-du-type-de-la-fonction)
      - [Déclaration du Pointeur de Fonction](#déclaration-du-pointeur-de-fonction)
      - [Caractéristiques Principales](#caractéristiques-principales-4)
    - [6. Point d'Entrée du Plugin](#6-point-dentrée-du-plugin)
      - [Principales Fonctions d'Entrée](#principales-fonctions-dentrée)
    - [7. Définitions et Inclusions](#7-définitions-et-inclusions)
      - [Définitions du Plugin](#définitions-du-plugin)
      - [Structure de Base des Inclusions](#structure-de-base-des-inclusions)
      - [Inclusions Spécifiques à Windows](#inclusions-spécifiques-à-windows)
      - [Inclusions Spécifiques à Unix/Linux](#inclusions-spécifiques-à-unixlinux)
      - [Caractéristiques Principales](#caractéristiques-principales-5)
  - [Back-End](#back-end)
    - [1. Réception des Données](#1-réception-des-données)
    - [2. Validation de la Requête](#2-validation-de-la-requête)
    - [3. Validation des Répertoires](#3-validation-des-répertoires)
    - [4. Traitement des URLs](#4-traitement-des-urls)
    - [5. Stockage des Données](#5-stockage-des-données)
    - [6. Format du Fichier JSON](#6-format-du-fichier-json)
    - [7. Système de Sauvegarde](#7-système-de-sauvegarde)
    - [8. Gestion des Erreurs](#8-gestion-des-erreurs)
  - [Définitions Importantes](#définitions-importantes)
    - [1. BACKEND\_HOST et BACKEND\_PATH](#1-backend_host-et-backend_path)
    - [2. upload\_dir dans le Backend](#2-upload_dir-dans-le-backend)
    - [Sécurité et Confidentialité](#sécurité-et-confidentialité)
  - [Compilation](#compilation)
    - [Compilation pour Windows](#compilation-pour-windows)
      - [1. Prérequis](#1-prérequis)
      - [2. Étapes de Compilation](#2-étapes-de-compilation)
        - [2-1. Ouvrir le projet dans Visual Studio](#2-1-ouvrir-le-projet-dans-visual-studio)
        - [2-2. Configurer le projet](#2-2-configurer-le-projet)
        - [2-3. Compiler le projet](#2-3-compiler-le-projet)
      - [2-4. Vérifier la compilation](#2-4-vérifier-la-compilation)
    - [Compilation pour Linux](#compilation-pour-linux)
      - [1. Prérequis](#1-prérequis-1)
      - [2. Étapes de Compilation](#2-étapes-de-compilation-1)
        - [2-1. Construire l'image Docker](#2-1-construire-limage-docker)
        - [2-2. `build.sh`](#2-2-buildsh)
        - [2-3. Construire le Plugin](#2-3-construire-le-plugin)
        - [2-4. `compile.sh`](#2-4-compilesh)
      - [3. Dockerfile](#3-dockerfile)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Droits Accordés](#1-droits-accordés)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Restrictions et Limitations](#3-restrictions-et-limitations)
      - [4. Propriété Intellectuelle](#4-propriété-intellectuelle)
      - [5. Clause de Non-Garantie et Limitation de Responsabilité](#5-clause-de-non-garantie-et-limitation-de-responsabilité)

## Fonctionnalités Principales

### 1. Collecte d'Informations du Serveur
   - Le plugin collecte automatiquement l'IP et le port du serveur en cours d'exécution.
   - Identifie si le serveur est SA-MP ou open.mp et collecte l'URL du site correspondant, si disponible.
   - Permet la configuration d'une URL d'image personnalisée via le paramètre `spc_integration_image`, qui doit être ajouté au fichier de configuration du serveur.

### 2. Validation d'URL
   - Avant d'envoyer l'URL de l'image au backend, le plugin vérifie si l'URL fournie est accessible et si elle correspond à un format d'image valide (JPEG, PNG, GIF, etc.).
   - Cela garantit que seules les URLs d'images valides sont envoyées, évitant des créations ou mises à jour inutiles dans le JSON.

### 3. Intégration avec le Backend
   - Le plugin envoie les informations collectées vers un backend via une requête HTTP POST.
   - Le backend valide la requête, s'assurant que la `API_KEY` fournie correspond à la clé configurée dans le backend. Cela est crucial pour la sécurité, car cela empêche le traitement des requêtes non autorisées.
   - Si les données sont valides, le backend crée un fichier JSON au format `IP-Port.json`, stockant les informations du serveur.

### 4. Compatibilité Multiplateforme
   - Supporte la compilation pour Linux (utilisant Docker, CMake et GCC 8) et Windows (utilisant Visual Studio 2022).
   - Fonctionne aussi bien pour SA-MP que pour open.mp, permettant à tous les serveurs d'utiliser le plugin.

## Comment utiliser le Plugin

### 1. Téléchargement

- Téléchargez la version la plus récente du plugin dans la section [releases](https://github.com/spc-samp/spc-integration/releases).
- Choisissez le fichier approprié pour votre système d'exploitation:
  - Windows: `spc-integration.dll`
  - Linux: `spc-integration.so`

### 2. Installation

1. Extrayez le fichier téléchargé.
2. Placez le plugin dans le dossier `plugins` de votre serveur.
3. Configurez le serveur pour charger le plugin:
   - **Pour SA-MP**: Ajoutez dans votre `server.cfg`:
     ```
     plugins spc-integration
     ```
   - **Pour open.mp**: Ajoutez `"spc-integration"` à la liste `legacy_plugins` dans votre `config.json`:
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
> Si vous avez déjà d'autres plugins installés, assurez-vous de charger le spc-integration après eux.

### 3. Configuration

Vous devez configurer l'URL de l'image qui sera affichée pour votre serveur. Choisissez l'une des options ci-dessous selon votre plateforme:

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
> L'URL de l'image doit être valide et accessible publiquement.

### 4. Vérification

1. Démarrez votre serveur.
2. Vérifiez les logs du serveur. Si vous voyez un message similaire à celui-ci, le plugin fonctionne correctement:
    ```
    [SPC Integration]: Information sent to the server data storage of the SPC:
    -- Server IP: '127.0.0.1'
    -- Server Port: '7777'
    -- Image URL configured: 'https://example.com/image.png'
    -- Web URL configured: 'https://example.com'
    ```

## Structure du Projet

La structure du projet est organisée comme suit:
```
└── src/
    ├── cmake/
    │   ├── CMakeLists.txt               // Fichier de configuration CMake
    │   └── compile.sh                   // Script de compilation pour Linux
    │
    ├── docker/
    │   ├── build.sh                     // Script pour construire l'image Docker
    │   └── Dockerfile                   // Fichier Docker pour compilation sous Linux
    │
    ├── sdk/
    │   └── (SDK du SA-MP)               // SDK nécessaire pour le développement du plugin
    │
    ├── amx_defines.h                    // Définitions liées à l'AMX
    ├── base64_encoder.cpp               // Implémentation de l'encodeur Base64
    ├── base64_encoder.h                 // En-tête de l'encodeur Base64
    ├── http_client.cpp                  // Implémentation du client HTTP
    ├── http_client.h                    // En-tête du client HTTP
    ├── http_linux.cpp                   // Implémentation spécifique Linux du client HTTP
    ├── http_response.cpp                // Implémentation de la réponse HTTP
    ├── http_response.h                  // En-tête de la réponse HTTP
    ├── http_windows.cpp                 // Implémentation spécifique Windows du client HTTP
    ├── inclusions.h                     // Inclusions communes et définitions globales
    ├── logger.h                         // En-tête pour le logging
    ├── main.cpp                         // Point d'entrée du plugin
    ├── plugin_defines.h                 // Définitions spécifiques au plugin
    ├── server_info.cpp                  // Implémentation pour la collecte d'informations du serveur
    ├── server_info.h                    // En-tête pour la collecte d'informations du serveur
    ├── spc-integration.sln              // Fichier solution Visual Studio
    ├── spc-integration.vcxproj          // Fichier projet Visual Studio
    ├── spc-integration.vcxproj.filters  // Configuration des filtres du projet Visual Studio
    ├── url_validator.cpp                // Implémentation du validateur d'URL
    └── url_validator.h                  // En-tête du validateur d'URL
```

## Détail des Codes

Ci-dessous, une analyse détaillée des principaux composants du code du **SPC Integration**. Chaque section du code est expliquée en profondeur pour permettre de comprendre le fonctionnement du plugin et son intégration avec le backend.

### 1. Collecte d'Informations du Serveur

| **Fichiers**      |
|-------------------|
| `server_info.h`   |
| `server_info.cpp` |

- La classe `Server_Info` est responsable de la collecte et de la gestion des informations essentielles du serveur, incluant IP, port, URLs d'intégration et site web. Le système supporte deux formats de fichier de configuration: server.cfg (SA-MP) et config.json (open.mp).

#### Structure Principale

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

#### Collecte de l'IP du Serveur

```cpp
bool Server_Info::Get_Server_IP() {
    #ifdef _WIN32
        // Windows: Utilise WinSock API
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            return false;
            
        char hostname[256];

        if (gethostname(hostname, sizeof(hostname)) == 0) {
            // Code pour obtenir l'IP sous Windows
            // ...
        }
    #else
        // Linux: Utilise getifaddrs
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

#### Lecture du Port du Serveur

```cpp
bool Server_Info::Get_Server_Port() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Lit depuis le fichier server.cfg (SA-MP)
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
        // Lit depuis le fichier config.json (open.mp)
        std::ifstream config(CONFIG_FILE_OPEN);
        std::string json_content((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
        // Traite le JSON pour trouver le port
        // ...
    }
    return false;
}
```

#### URLs d'image et Site Web

Le système gère deux types d'URLs:
1. URL d'Image (`image_url`): Adresse de l'URL d'image du serveur.
2. URL du Site Web (`web_url`): Adresse du site web du serveur.

```cpp
bool Server_Info::Get_Image_URL() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Recherche "spc_integration_image" dans le fichier
        if (/* URL trouvée */)
            image_config_status = Config_Status::Success;
        else
            image_config_status = Config_Status::Empty;
    }
    // Similaire pour CONFIG_FILE_OPEN
}

bool Server_Info::Get_Web_URL() {
    // Processus similaire à Get_ImageURL(), mais recherche "weburl" ou "website"
}
```

#### Statut de Configuration

Le système utilise des énumérations pour contrôler l'état des configurations:

```cpp
enum class Config_Status {
    Success,        // Configuration trouvée et valide
    Not_Found,      // Configuration non trouvée
    Empty,          // Configuration trouvée mais vide
    Web_Not_Found,  // URL du site web non trouvée
    Web_Empty       // URL du site web vide
};
```

#### Initialisation

Le processus d'initialisation est géré par la méthode `Initialize()`:

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

#### Caractéristiques Principales

1. **Collecte d'Informations**:
    - Détection automatique de l'IP du serveur.
    - Lecture du port configuré.
    - Support des URLs d'image et site web.
    - Validation de toutes les informations collectées.

2. **Compatibilité**:
    - Support de multiples systèmes d'exploitation.
    - Compatibilité avec SA-MP et open.mp.
    - Lecture de différents formats de configuration.

3. **Gestion d'État**:
    - Système robuste de statuts pour les configurations.
    - Contrôle granulaire des erreurs et états.
    - Validation individualisée de chaque composant.

4. **Traitement des Données**:
    - Nettoyage automatique des chaînes.
    - Détection et suppression des espaces blancs.
    - Validation des URLs et configurations.

### 2. Validation d'URL d'image

| **Fichiers**        |
|---------------------|
| `url_validator.h`   |
| `url_validator.cpp` |

- Le système de validation d'URL est un composant critique de sécurité qui effectue une validation complète des URLs d'images à travers plusieurs couches de vérification. Il ne valide pas seulement le format de l'URL, mais vérifie également si l'URL pointe vers un fichier image valide.

#### Vue d'ensemble de l'Architecture

Le processus de validation est implémenté dans la classe `URL_Validator` et suit un pipeline de validation en plusieurs étapes:

- **Validation Initiale** (`Is_Valid`).
- **Gestion du Timeout** (`Validate_With_Timeout`).
- **Processus de Validation Complète** (`Perform_Full_Validation`).
- **Vérification du Contenu de l'Image** (`Validate_Image_Headers`).

#### Validation Protégée par Timeout

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
    // ... traitement des exceptions
}
```

- Le système implémente un mécanisme de timeout en utilisant `std::async` pour éviter les blocages sur des URL lentes ou non réactives. Le processus de validation échouera automatiquement si le délai de `VALIDATION_TIMEOUT` secondes (défini à 10 secondes dans le code) est dépassé.

#### Pipeline de Validation Complète

La méthode `Perform_FullValidation` implémente une série de vérifications:

```cpp
bool URL_Validator::Perform_Full_Validation(const std::string& url) {
    // Validation de la longueur
    if (url.empty() || url.length() > 2048)
        return (Log_Printf("[SPC Integration]: Error: URL is empty or too long (maximum 2048 characters)."), false);

    // Validation du protocole
    if (!Has_Valid_Scheme(url))
        return (Log_Printf("[SPC Integration]: Error: URL must start with 'http://' or 'https://'."), false);

    // Validation de la structure
    if (!Has_Valid_HostAndPath(url))
        return (Log_Printf("[SPC Integration]: Error: URL must contain a valid hostname and path."), false);

    // Validation des caractères
    if (!Has_Valid_Characters(url))
        return (Log_Printf("[SPC Integration]: Error: URL contains invalid characters."), false);

    // Validation de l'image
    if (!Validate_Image_Headers(url))
        return (Log_Printf("[SPC Integration]: Error: The URL content is not a valid image."), false);

    Log_Printf("[SPC Integration]: Validation successfully completed!");

    return true;
}
```

#### Validation des Composants de l'URL

Le système inclut des validateurs spécialisés pour différents composants de l'URL:

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

#### Validation du Contenu de l'Image

Le système effectue la validation réelle de l'image en vérifiant les en-têtes du fichier:

```cpp
bool URL_Validator::Check_Image_Magic_Numbers(const std::vector<unsigned char>& data) {
    if (data.size() < 4)
        return false;

    // Prend en charge plusieurs formats d'image:
    // JPEG: FF D8 FF
    if (data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF)
        return true;

    // PNG: 89 50 4E 47 0D 0A 1A 0A
    if (data.size() >= 8 && data[0] == 0x89 && data[1] == 0x50 /* ... */)
        return true;

    // Formats supplémentaires: GIF, BMP, WebP
    // ...
}
```

#### Mise en œuvre multiplateforme

Le système inclut des implémentations spécifiques pour chaque plateforme afin de récupérer les données d'image:

- **Windows**: Utilise l'API WinHTTP (`Fetch_Image_Data_Windows`).
- **Linux**: Utilise OpenSSL et la programmation de sockets (`Fetch_Image_Data_Linux`).

Les deux implémentations:
- Établissent des connexions sécurisées (HTTPS).
- Demandent uniquement la portion d'en-tête de l'image (premiers 16 octets).
- Gèrent le nettoyage de la connexion et des ressources.

#### Caractéristiques principales

1. **Validation complète**:
    - Format et structure de l'URL.
    - Sécurité du protocole (prise en charge de HTTPS).
    - Validation du domaine et du chemin.
    - Validation du jeu de caractères.
    - Vérification du format de l'image.

2. **Fonctionnalités de sécurité**:
    - Protection contre les timeout.
    - Limite maximale de la longueur de l'URL.
    - Connexions sécurisées multiplateformes.
    - Validation efficace des images en mémoire.

3. **Formats d'image pris en charge**:
    - JPEG
    - PNG
    - GIF
    - BMP
    - WebP

4. **Gestion des erreurs**:
    - Enregistrement détaillé à chaque étape de la validation.
    - Gestion élégante des timeout.
    - Traitement des erreurs spécifiques à la plateforme.
    - Nettoyage des ressources dans tous les scénarios.

### 3. Client HTTP

| **Fichiers**        |
|---------------------|
| `http_client.h`     |
| `http_client.cpp`   |
| `http_windows.cpp`  |
| `http_linux.cpp`    |
| `http_response.h`   |
| `http_response.cpp` |

- Le client HTTP est responsable de l'envoi des informations collectées vers le backend via HTTPS. L'implémentation est multiplateforme, utilisant WinHTTP sur Windows et OpenSSL/sockets sur Linux, garantissant une communication sécurisée via SSL/TLS.

#### Structure et fonctionnement

Le fichier principal `http_client.h` définit l'interface de la classe:

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

L'implémentation dans `http_client.cpp` sélectionne automatiquement l'implémentation correcte:

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

#### Implémentation Windows (WinHTTP)

Dans `http_windows.cpp`, l'implémentation utilise l'API WinHTTP:

```cpp
bool HTTP_Client::Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data) {
    HINTERNET spc_session = WinHttpOpen(L"SPC-INTEGRATION/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    // Configure le timeout de 60 secondes
    DWORD timeout = 60000;

    WinHttpSetOption(spc_session, WINHTTP_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

    // Connexion et envoi de la requête HTTPS
    HINTERNET spc_connect = WinHttpConnect(spc_session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    
    // ... reste de l'implémentation Windows
}
```

#### Implémentation Linux (OpenSSL)

Dans `http_linux.cpp`, l'implémentation utilise OpenSSL avec des sockets:

```cpp
bool HTTP_Client::Send_Request_Linux(const std::string& host, const std::string& path, const std::string& data) {
    // Initialise OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Configure le contexte SSL
    const SSL_METHOD* method = SSLv23_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    // Crée et configure le socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;

    // ... reste de l'implémentation Linux
}
```

#### Traitement de la Réponse

La classe `HTTP_Response` dans `http_response.h` traite les réponses du serveur:

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

L'implémentation dans `http_response.cpp` traite différents types de réponse:

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
    // ... autres types d'erreur

    Log_Printf("%s %s: %s", prefix, error_prefix, message.c_str());
}
```

#### Caractéristiques principales

1. **Communication sécurisée**:
    - HTTPS (port 443) avec SSL/TLS.
    - Timeout de 60 secondes pour la connexion, l'envoi et la réception.
    - Content-Type: `application/x-www-form-urlencoded` avec UTF-8.

2. **Gestion des erreurs**:
    - Vérifie chaque étape de la communication.
    - Libère les ressources de manière appropriée.
    - Journalisation détaillée par type d'erreur:
        - Erreurs du serveur: Suggère de vérifier la configuration.
        - Erreurs d'authentification: Indique de vérifier la clé API.
        - Erreurs de validation: Recommande de revoir les configurations.

3. **Format de réponse JSON**:
    ```json
    {
        "success": true/false,
        "message": "Message de réponse"
    }
    ```

### 4. Codification Base64

| **Fichiers**         |
|----------------------|
| `base64_encoder.h`   |
| `base64_encoder.cpp` |

- La codification Base64 est utilisée pour encoder l'URL de l'image avant de l'envoyer au backend. Cela est particulièrement utile lorsque l'URL contient des caractères spéciaux qui peuvent ne pas être correctement traités dans une requête HTTP.

#### Définition de l'Interface

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

- L'interface est définie à l'aide de gardes d'inclusion pour éviter les définitions multiples. La classe utilise une méthode statique `Encode` qui accepte une chaîne comme entrée et retourne sa version codée.

#### Alphabet Base64 et Implémentation

```cpp
#include "base64_encoder.h"

const std::string Base64_Encoder::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
```

- L'alphabet Base64 est défini comme une chaîne constante contenant 64 caractères différents. Cette chaîne est utilisée comme une table de recherche lors du processus d'encodage.

#### Initialisation et Tampons

```cpp
// ... "Alphabet Base64 et Implémentation" ...

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

- Deux tableaux de caractères sont initialisés: l'un pour stocker les 3 octets d'entrée et l'autre pour les 4 caractères Base64 résultants. La chaîne d'entrée est convertie en un tableau de caractères pour un traitement octet par octet.

#### Boucle Principale de Codification

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Initialisation et Tampons" ...

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

- La boucle principale traite l'entrée en groupes de 3 octets, les convertissant en 4 caractères Base64 par des opérations bit à bit. Chaque groupe de 24 bits est divisé en quatre groupes de 6 bits.

#### Traitement du Padding

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Boucle Principale de Codification" ...

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

- Pour les entrées qui ne sont pas des multiples de 3 octets, il est nécessaire d'ajouter un padding. Les octets restants sont remplis de zéros et encodés, et le caractère '=' est ajouté pour compléter le groupe de 4 caractères.

#### Caractéristiques Principales

1. **Traitement des Données**:
    - Conversion de groupes de 3 octets en 4 caractères Base64.
    - Manipulation bit à bit pour l'extraction précise des valeurs.
    - Traitement automatique du padding pour des tailles non multiples de 3.

2. **Conception et Architecture**:
    - Implémentation modulaire avec séparation claire des responsabilités.
    - Utilisation de méthodes statiques pour faciliter l'accès.
    - Encapsulation de l'alphabet Base64 en tant que membre privé.

3. **Optimisation et Performance**:
    - Traitement efficace octet par octet.
    - Utilisation de tableaux fixes pour minimiser les allocations de mémoire.
    - Opérations bit à bit optimisées pour une conversion rapide.

4. **Robustesse et Fiabilité**:
    - Traitement sûr des chaînes de n'importe quelle taille.
    - Garantie d'une sortie toujours valide en Base64.
    - Préservation de l'intégrité des données lors de l'encodage.

### 5. Journalisation

| **Fichiers** |
|--------------|
| `logger.h`   |

- Le système de journalisation est une partie fondamentale du plugin, car il permet aux développeurs de surveiller le comportement du plugin et d'identifier les problèmes. L'utilisation des journaux aide à déboguer et à maintenir le code.

#### Définition de l'Interface

```cpp
#ifndef LOGGER_H
    #define LOGGER_H

    typedef void (*Log_Printf_t)(const char* Format, ...);
    extern Log_Printf_t Log_Printf;
#endif
```

- Le système de journalisation est défini par un pointeur de fonction qui utilise des arguments variables, permettant ainsi une flexibilité dans la mise en forme des messages. La déclaration `extern` indique que l'implémentation réelle de la fonction sera fournie au moment de l'exécution.

#### Définition du Type de la Fonction

```cpp
typedef void (*Log_Printf_t)(const char* Format, ...);
```

Le type `Log_Printf_t` définit la signature de la fonction de journalisation:
- `void`: La fonction ne retourne aucune valeur
- `const char* Format`: Le premier paramètre est une chaîne de format
- `...`: Permet des arguments variables pour un formatage dynamique

#### Déclaration du Pointeur de Fonction

```cpp
extern Log_Printf_t Log_Printf;
```

Le pointeur `Log_Printf` est déclaré comme externe, ce qui permet:
- L'implémentation réelle d'être fournie par l'application hôte.
- Le plugin d'utiliser l'infrastructure de journalisation existante.
- Les messages d'être intégrés au système de journalisation principal.

#### Caractéristiques Principales

1. **Flexibilité d'Implémentation**:
    - Prise en charge des arguments variables pour un formatage dynamique.
    - Possibilité d'intégration avec différents systèmes de journalisation.
    - L'implémentation peut être fournie au moment de l'exécution.

2. **Intégration avec le Système Hôte**:
    - Utilisation de l'infrastructure de journalisation existante.
    - Les messages peuvent être dirigés vers différentes sorties.
    - Cohérence avec la journalisation de l'application principale.

3. **Facilité d'Utilisation**:
    - Interface simple et familière (similaire à printf).
    - Peut être utilisée dans n'importe quelle partie du code.
    - Ne nécessite pas de configuration supplémentaire dans le code du plugin.

### 6. Point d'Entrée du Plugin

| **Fichiers** |
|--------------|
| `main.cpp`   |

- Le point d'entrée du plugin est l'endroit où l'exécution du plugin commence. Ce fichier est responsable de:
    - Initialiser les fonctions essentielles du AMX.
    - Collecter et valider les informations du serveur.
    - Vérifier les configurations dans le fichier server.cfg/config.json.
    - Envoyer des données au backend du SPC.

#### Principales Fonctions d'Entrée

```cpp
// Chargement initial du plugin.
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** Plugin_Data) {
    // Initialise les fonctions AMX et le système de journalisation.
    // Collecte les informations du serveur.
    // Valide les URLs de l'image et du site web.
    // Envoie les données au backend.
    // Affiche les informations de statut.
}

// Déchargement du plugin.
PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    // Finalise le plugin.
}

// Ressources supportées.
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

// Chargement des scripts AMX.
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* Amx) {
    return AMX_ERR_NONE;
}

// Déchargement des scripts AMX.
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* Amx) {
    return AMX_ERR_NONE;
}
```

1. **Processus d'Initialisation**:
    - Initialise les fonctions essentielles du AMX et le système de journalisation.
    - Collecte les informations du serveur via la classe `Server_Info`.
    - Vérifie l'existence et la validité des paramètres:
        - `spc_integration_image` dans le fichier de configuration.
        - `weburl/website` dans le fichier de configuration.
    - Valide les URLs fournies.
    - Tente d'envoyer les données au backend (d'abord comme "create", puis comme "update" si nécessaire).
    - Affiche des informations détaillées sur l'état de l'initialisation.

2. **Validations et Vérifications**:
    - Vérifie la présence et la validité de l'URL de l'image.
    - Vérifie la présence et la validité de l'URL du site web.
    - Valide les URLs à l'aide de la classe `URL_Validator`.
    - Tente une reconnexion automatique en cas d'échec de l'envoi initial.

3. **Feedback et Journalisation**:
    - Affiche une bannière informative avec des détails sur le plugin et des liens sociaux.
    - Fournit des messages détaillés sur les erreurs de configuration.
    - Affiche le statut final de l'initialisation avec les informations du serveur.

### 7. Définitions et Inclusions

| **Fichiers**          |
|-----------------------|
| `plugin_defines.h`    |
| `inclusions.h`        |

- Ces fichiers contiennent des définitions et des inclusions nécessaires au fonctionnement du plugin, établissant des constantes importantes et garantissant la compatibilité multiplateforme.

#### Définitions du Plugin

```cpp
#ifndef PLUGIN_DEFINES_H
    #define PLUGIN_DEFINES_H
    
    #define PLUGIN_VERSION "1.0.0"
    #define BACKEND_HOST "example_site.com" // Sans le protocole 'https://' ou 'http://'.
    #define BACKEND_PATH "/backend_directory/spc-integration.php"
    #define API_KEY "YOUR_SECURE_KEY_TO_ACCESS_PHP"
    #define CONFIG_FILE_SAMP "server.cfg"
    #define CONFIG_FILE_OPEN "config.json"
#endif
```

Le fichier de définitions contient des constantes cruciales pour le fonctionnement du plugin:
- Version du plugin.
- Paramètres du backend pour la communication.
- Clé d'API pour l'authentification.
- Noms des fichiers de configuration.

#### Structure de Base des Inclusions

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

Inclusion des bibliothèques standard C++ nécessaires pour:
- La gestion des chaînes de caractères et des fichiers.
- Les expressions régulières.
- Les opérations asynchrones.
- La gestion du temps.

#### Inclusions Spécifiques à Windows

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

Support spécifique pour les systèmes Windows:
- APIs de réseau Windows.
- Bibliothèques HTTP Windows.
- Paramètres de liaison.

#### Inclusions Spécifiques à Unix/Linux

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

Support spécifique pour les systèmes Unix/Linux:
- APIs réseau POSIX.
- Support SSL via OpenSSL.
- Interfaces réseau.

#### Caractéristiques Principales

1. **Configuration du Backend**:
    - Hôte et chemin configurables pour une flexibilité de déploiement.
    - Clé d'API pour une authentification sécurisée.
    - Version explicite du plugin.

2. **Compatibilité Multiplateforme**:
    - Support natif pour Windows et Unix/Linux.
    - Abstraction des APIs spécifiques au système.
    - Implémentations conditionnelles pour chaque plateforme.

3. **Sécurité et Communication**:
    - Support SSL/TLS pour une communication sécurisée.
    - Authentification via clé d'API.
    - Bibliothèques robustes pour les réseaux.

4. **Gestion des Ressources**:
    - Support des opérations asynchrones.
    - Gestion efficace des chaînes et fichiers.
    - Contrôle du temps et de la temporisation.

## Back-End

Le backend est responsable de la réception des informations envoyées par le plugin et de leur stockage dans un fichier JSON. Voici une explication détaillée de son fonctionnement:

### 1. Réception des Données
  - Le plugin envoie une requête HTTP POST contenant les informations du serveur (IP, port, URL du site et URL de l'image).
  - Le backend valide la requête, s'assurant que la `API_KEY` fournie correspond à la clé configurée dans le backend.
  - Cela est crucial pour la sécurité, car cela empêche le traitement des requêtes non autorisées.
  - Il prend en charge les URL tant en format normal qu'en base64.

### 2. Validation de la Requête
   - Le backend vérifie si la `API_KEY` fournie dans la requête est valide.
   - Il utilise la fonction `hash_equals()` pour comparer les clés en toute sécurité.
   - Si la clé n'est pas valide, un message d'erreur d'authentification est retourné.
   - Le code suivant illustre cette validation:
        ```php
        function Validate_Request($provided_key) {
            global $api_key;

            return hash_equals($api_key, $provided_key);
        }

        if (!Validate_Request($api_key_provided)) {
            $response = [
                'success' => false,
                'message' => 'Erreur d\'authentification: Clé API invalide. Veuillez vérifier votre configuration.'
            ];
            echo json_encode($response);

            exit;
        }
        ```

### 3. Validation des Répertoires
  - Vérifie l'existence des répertoires nécessaires:
      - `exemple_directory` comme répertoire de base.
      - `exemple_servers` comme emplacement de stockage.
  - Confirme les autorisations d'écriture dans le répertoire de téléchargement.
  - Retourne des messages d'erreur spécifiques en cas de validation échouée.

### 4. Traitement des URLs
   - Fonctions spécifiques pour traiter les URLs d'image et web.
   - Prise en charge des URLs normales et codées en base64.
   - Validation de la décodification en base64 lorsque utilisée.
   - Gestion des erreurs pour les URLs invalides.

### 5. Stockage des Données
   - Crée des fichiers JSON uniques au format `IP-Port.json`.
   - Assainit les noms de fichiers pour plus de sécurité.
   - Définit des autorisations appropriées (chmod 0644).
   - Implémente un système de sauvegarde pour les mises à jour.
   - Le code ci-dessous montre le processus de stockage:
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
                'message' => 'Les données du serveur ont été créées avec succès pour ' . $server_ip . ':' . $server_port
            ];
        }
        else {
            $response = [
                'success' => false,
                'message' => 'Erreur serveur: Impossible de créer le fichier de données du serveur. Veuillez signaler ce problème à l\'équipe (SPC).'
            ];
        }
        ```

### 6. Format du Fichier JSON
   - Structure claire et organisée des données.
   - Utilise la mise en forme pretty-print pour une meilleure lisibilité.
   - Préserve le formatage des URLs avec des barres obliques non échappées.
   - Exemple du contenu du fichier JSON:
        ```json
        {
            "spc_integration_image": "https://example.com/image.png",
            "spc_web_url": "https://example.com"
        }
        ```

### 7. Système de Sauvegarde
   - Crée une sauvegarde automatique avant les mises à jour.
   - Restaure les données originales en cas d'échec.
   - Supprime les fichiers de sauvegarde après des opérations réussies.
   - Garantit l'intégrité des données pendant les mises à jour.

### 8. Gestion des Erreurs
   - Messages d'erreur détaillés et spécifiques.
   - Validations à chaque étape du processus.
   - Réponses cohérentes au format JSON.
   - Types d'erreurs traités:
       - Échecs d'authentification.
       - Problèmes avec les répertoires.
       - Erreurs lors des opérations de fichier.
       - Échecs de validation.
       - Restrictions de méthode HTTP.

## Définitions Importantes

### 1. BACKEND_HOST et BACKEND_PATH

Dans le fichier `plugin_defines.h`, vous trouverez les définitions suivantes:

```cpp
#define BACKEND_HOST "example_site.com" // Sans le protocole 'https://' ou 'http://'.
#define BACKEND_PATH "/backend_directory/spc-integration.php"
```

- **BACKEND_HOST**: Cette définition représente l'adresse du serveur où le backend est hébergé. Dans le contexte du plugin, il s'agit de l'endroit où les informations du serveur seront envoyées. Il est important de noter que, pour des raisons de sécurité, la SPC ne divulgue pas l'adresse réelle du backend. Cela est fait pour protéger l'intégrité et la sécurité des données, afin d'éviter que des informations sensibles ne soient exposées.

- **BACKEND_PATH**: Cette définition spécifie le chemin du script PHP qui traitera les requêtes envoyées par le plugin. Le chemin doit être accessible depuis le `BACKEND_HOST` et doit être configuré pour accepter les requêtes POST. Le script PHP est responsable de la validation des données reçues et de leur stockage dans un fichier JSON.

### 2. upload_dir dans le Backend

Dans le script PHP (`spc-integration.php`), la variable `upload_dir` est définie comme suit:

```php
$upload_dir = $base_dir . '/exemple_directory/exemple_servers/';
```

- **upload_dir**: Ce répertoire est où les fichiers JSON contenant les informations du serveur seront stockés. Le backend vérifie si ce répertoire existe et s'il est accessible en écriture avant de tenter de créer ou de modifier des fichiers. Si le répertoire n'existe pas ou n'est pas accessible en écriture, le backend renverra une erreur indiquant qu'il n'a pas pu stocker les données.

### Sécurité et Confidentialité

La SPC privilégie la sécurité et la confidentialité des données. C'est pourquoi l'adresse réelle du backend et la `API_KEY` ne sont pas publiées publiquement. Le plugin compilé fourni dans [releases](https://github.com/spc-samp/spc-integration/releases) utilise l'adresse et la `API_KEY` de la SPC pour stocker les informations du serveur de manière sécurisée. Cela garantit que seules les requêtes autorisées sont traitées et que les données des serveurs sont protégées contre les accès non autorisés.

## Compilation

Le **SPC Integration** peut être compilé dans des environnements Windows et Linux. Cette section détaille le processus de compilation, y compris la configuration de l'environnement, l'utilisation de Docker, CMake et des scripts de compilation.

### Compilation pour Windows

#### 1. Prérequis

Pour compiler le plugin dans un environnement Windows, vous aurez besoin de:

- **Visual Studio 2022**: Visual Studio doit être installé avec le support pour C++, avec l'option pour le développement de bureau en C++ sélectionnée lors de l'installation.

#### 2. Étapes de Compilation

##### 2-1. Ouvrir le projet dans Visual Studio

1. Ouvrir Visual Studio 2022.
2. Naviguer jusqu'au fichier `spc-integration.sln` dans le projet et l'ouvrir.
3. Visual Studio chargera le projet et ses configurations.

##### 2-2. Configurer le projet

- La version de C++ doit être définie sur C++17 dans les configurations du projet sous **Project Properties** > **Configuration Properties** > **C/C++** > **Language** > **C++ Language Standard**.

##### 2-3. Compiler le projet

- Une fois le projet configuré, sélectionnez "Build" dans le menu supérieur et choisissez "Build Solution" ou appuyez sur `Ctrl + Shift + B`.
- Visual Studio compilera le projet et générera le plugin.

#### 2-4. Vérifier la compilation

- Après une compilation réussie, le fichier du plugin (`spc-integration.dll`) sera disponible dans le dossier de sortie (généralement `Debug` ou `Release`).

### Compilation pour Linux

#### 1. Prérequis

L'environnement de compilation nécessite les outils suivants:

- **Docker**: Plateforme pour créer, déployer et exécuter des applications dans des conteneurs. Docker est utilisé pour créer un environnement de compilation isolé.
- **CMake**: Outil d'automatisation de la compilation qui utilise des fichiers de configuration pour générer des fichiers de projet pour différents systèmes de compilation.
- **GCC 8**: Compilateur GNU C++ utilisé pour compiler le code du plugin.

#### 2. Étapes de Compilation

##### 2-1. Construire l'image Docker

Le processus commence par la navigation dans le dossier `docker` et l'exécution du script `build.sh` pour construire l'image Docker et compiler le plugin. Ce script crée un environnement de compilation contenant toutes les dépendances nécessaires et effectue automatiquement la compilation.

```bash
cd docker
./build.sh
```

##### 2-2. `build.sh`

Le script `build.sh` exécute les opérations suivantes:

```bash
#!/bin/bash

dos2unix "$0" 2>/dev/null || true

if ! command -v docker &> /dev/null; then
    echo "Docker n'est pas installé. Veuillez installer Docker d'abord."
    exit 1
fi

PROJECT_ROOT="$(dirname "$(pwd)")"

TEMP_DIR=$(mktemp -d)
echo "Création du répertoire de travail temporaire: $TEMP_DIR"

echo "Copie des fichiers nécessaires..."
cp -r \
    "$PROJECT_ROOT"/*.cpp \
    "$PROJECT_ROOT"/*.h \
    "$PROJECT_ROOT/sdk" \
    "$TEMP_DIR/"

mkdir -p "$TEMP_DIR/cmake"

cp "$PROJECT_ROOT/cmake/CMakeLists.txt" "$TEMP_DIR/cmake/"

cp Dockerfile "$TEMP_DIR/";
```

- **Caractéristiques**:
  - Le script vérifie si Docker est installé
  - Crée un répertoire temporaire pour stocker les fichiers nécessaires à la compilation
  - Les fichiers source et d'en-tête sont copiés dans le répertoire temporaire, où l'image Docker sera construite

##### 2-3. Construire le Plugin

Le script `build.sh` gère l'ensemble du processus de compilation. Il utilise Docker pour créer un environnement isolé et exécute automatiquement le script `compile.sh` à l'intérieur du conteneur. Le processus comprend:
1. Création d'une image Docker avec toutes les dépendances
2. Exécution du conteneur avec l'environnement de compilation
3. Compilation du plugin avec CMake
4. Copie des fichiers compilés dans le dossier `build` du répertoire du projet

##### 2-4. `compile.sh`

Le script `compile.sh` est responsable de la configuration et de la compilation du projet avec CMake:

```bash
#!/bin/bash

rm -rf ../build
mkdir -p ../build
cd ../build
cmake ../cmake -DCMAKE_BUILD_TYPE=Release
make -j$(nproc) VERBOSE=1
strip -s spc-integration.so
echo "Vérification des dépendances binaires:"
ldd spc-integration.so
```

- **Caractéristiques**:
    - Supprime tout répertoire de build précédent et en crée un nouveau
    - Utilise CMake pour configurer le projet, spécifiant le type de build comme "Release" pour les optimisations
    - La commande `make` compile le projet, en utilisant tous les cœurs disponibles (`-j$(nproc)`)
    - Après la compilation, le plugin est "stripé" pour supprimer les informations de débogage
    - Le script vérifie les dépendances du binaire généré à l'aide de `ldd`

#### 3. Dockerfile

Le `Dockerfile` définit l'environnement de compilation. Exemple de configuration typique pour ce projet:

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

- **Caractéristiques**:
    - **FROM ubuntu:18.04**: Définit l'image de base comme Ubuntu 18.04
    - **RUN apt-get update && apt-get install -y**: Met à jour la liste des paquets et installe les dépendances nécessaires
    - **WORKDIR /app**: Définit le répertoire de travail à l'intérieur du conteneur
    - **COPY . .**: Copie les fichiers du répertoire actuel vers le répertoire de travail dans le conteneur
    - **RUN cmake . && make**: Exécute CMake pour compiler le projet à l'intérieur du conteneur

> [!IMPORTANT]
> L'utilisation d'un Dockerfile garantit que l'environnement de compilation soit reproductible et isolé, évitant ainsi les conflits de dépendances qui peuvent survenir dans les systèmes locaux. Cette approche est particulièrement utile lorsque différents développeurs ou serveurs ont des configurations d'environnement variées.

## Licence

Copyright © **SA-MP Programming Community**

Ce logiciel est sous licence Apache, Version 2.0 (la "Licence"); vous ne pouvez pas utiliser ce logiciel sauf en conformité avec la Licence. Vous pouvez obtenir une copie de la Licence sur: [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)

### Conditions Générales d'Utilisation

#### 1. Droits Accordés

La présente licence accorde gratuitement à toute personne obtenant une copie de ce logiciel et des fichiers de documentation associés les droits suivants:
* Utiliser, copier, modifier et distribuer le logiciel sur tout support ou format, à toute fin, commerciale ou non-commerciale
* Fusionner, publier, distribuer, sous-licencier et/ou vendre des copies du logiciel
* Permettre aux personnes à qui le logiciel est fourni de faire de même

#### 2. Conditions Obligatoires

Toutes les distributions du logiciel ou des travaux dérivés doivent:
* Inclure une copie complète de cette licence
* Indiquer clairement toutes modifications apportées au code source original
* Préserver tous les avis de droits d'auteur, brevets, marques déposées et attributions
* Fournir une documentation appropriée des modifications implémentées
* Maintenir l'avis de licence et de garantie dans toutes les copies

#### 3. Restrictions et Limitations

* Cette licence n'accorde pas la permission d'utiliser les marques déposées, logos ou noms commerciaux de la **SA-MP Programming Community**
* Les contributions au code source doivent être licenciées sous les mêmes termes que cette licence
* L'utilisation des noms des contributeurs pour approuver ou promouvoir des produits dérivés de ce logiciel nécessite une autorisation préalable spécifique

#### 4. Propriété Intellectuelle

Le logiciel et toute la documentation associée sont protégés par les lois sur les droits d'auteur et les traités internationaux. La **SA-MP Programming Community** conserve tous les droits, titres et intérêts non expressément accordés par cette licence.

#### 5. Clause de Non-Garantie et Limitation de Responsabilité

LE LOGICIEL EST FOURNI "EN L'ÉTAT", SANS GARANTIE D'AUCUNE SORTE, EXPRESSE OU IMPLICITE, Y COMPRIS, MAIS SANS S'Y LIMITER, LES GARANTIES DE COMMERCIALISATION, D'ADÉQUATION À UN USAGE PARTICULIER ET DE NON-VIOLATION.

EN AUCUN CAS LES AUTEURS OU LES TITULAIRES DES DROITS D'AUTEUR NE SERONT RESPONSABLES DE TOUTE RÉCLAMATION, DOMMAGE OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS LE CADRE D'UN CONTRAT, D'UN DÉLIT OU AUTREMENT, DÉCOULANT DE OU EN LIEN AVEC LE LOGICIEL OU L'UTILISATION OU D'AUTRES TRANSACTIONS DANS LE LOGICIEL.

---

Pour des informations détaillées sur la Licence Apache 2.0, consultez: http://www.apache.org/licenses/LICENSE-2.0