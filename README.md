# spc-integration

O **SPC Integration** é um plugin desenvolvido para SA-MP (San Andreas Multiplayer) e open.mp (Open Multiplayer) que coleta informações do servidor, como IP, porta, URL do site e uma URL de imagem configurável. Essas informações são enviadas para o site da SPC (SA-MP Programming Community), onde são armazenadas as informações dos servidores.

## Idiomas

- Deutsch: [README](translations/Deutsch/README.md)
- English: [README](translations/English/README.md)
- Español: [README](translations/Espanol/README.md)
- Français: [README](translations/Francais/README.md)
- Italiano: [README](translations/Italiano/README.md)
- Polski: [README](translations/Polski/README.md)
- Русский: [README](translations/Русский/README.md)
- Svenska: [README](translations/Svenska/README.md)
- Türkçe: [README](translations/Turkce/README.md)

## Índice

- [spc-integration](#spc-integration)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Funcionalidades Principais](#funcionalidades-principais)
    - [1. Coleta de Informações do Servidor](#1-coleta-de-informações-do-servidor)
    - [2. Validação de URL](#2-validação-de-url)
    - [3. Integração com Backend](#3-integração-com-backend)
    - [4. Compatibilidade Multiplataforma](#4-compatibilidade-multiplataforma)
  - [Como usar o Plugin](#como-usar-o-plugin)
    - [1. Download](#1-download)
    - [2. Instalação](#2-instalação)
    - [3. Configuração](#3-configuração)
    - [4. Verificação](#4-verificação)
  - [Estrutura do Projeto](#estrutura-do-projeto)
  - [Detalhamento dos Códigos](#detalhamento-dos-códigos)
    - [1. Coleta de Informações do Servidor](#1-coleta-de-informações-do-servidor-1)
      - [Estrutura Principal](#estrutura-principal)
      - [Coleta de IP do Servidor](#coleta-de-ip-do-servidor)
      - [Leitura da Porta do Servidor](#leitura-da-porta-do-servidor)
      - [URLs de imagem e Website](#urls-de-imagem-e-website)
      - [Status de Configuração](#status-de-configuração)
      - [Inicialização](#inicialização)
      - [Características Principais](#características-principais)
    - [2. Validação de URL de imagem](#2-validação-de-url-de-imagem)
      - [Visão Geral da Arquitetura](#visão-geral-da-arquitetura)
      - [Validação Protegida por Timeout](#validação-protegida-por-timeout)
      - [Pipeline de Validação Completa](#pipeline-de-validação-completa)
      - [Validação de Componentes da URL](#validação-de-componentes-da-url)
      - [Validação do Conteúdo da Imagem](#validação-do-conteúdo-da-imagem)
      - [Implementação Multiplataforma](#implementação-multiplataforma)
      - [Características Principais](#características-principais-1)
    - [3. Cliente HTTP](#3-cliente-http)
      - [Estrutura e Funcionamento](#estrutura-e-funcionamento)
      - [Implementação Windows (WinHTTP)](#implementação-windows-winhttp)
      - [Implementação Linux (OpenSSL)](#implementação-linux-openssl)
      - [Processamento de Resposta](#processamento-de-resposta)
      - [Características Principais](#características-principais-2)
    - [4. Codificação Base64](#4-codificação-base64)
      - [Definição da Interface](#definição-da-interface)
      - [Alfabeto Base64 e Implementação](#alfabeto-base64-e-implementação)
      - [Inicialização e Buffers](#inicialização-e-buffers)
      - [Loop Principal de Codificação](#loop-principal-de-codificação)
      - [Tratamento de Padding](#tratamento-de-padding)
      - [Características Principais](#características-principais-3)
    - [5. Logging](#5-logging)
      - [Definição da Interface](#definição-da-interface-1)
      - [Definição do Tipo da Função](#definição-do-tipo-da-função)
      - [Declaração do Ponteiro de Função](#declaração-do-ponteiro-de-função)
      - [Características Principais](#características-principais-4)
    - [6. Ponto de Entrada do Plugin](#6-ponto-de-entrada-do-plugin)
      - [Principais Funções de Entrada](#principais-funções-de-entrada)
    - [7. Definições e Inclusões](#7-definições-e-inclusões)
      - [Definições do Plugin](#definições-do-plugin)
      - [Estrutura Base das Inclusões](#estrutura-base-das-inclusões)
      - [Inclusões Específicas para Windows](#inclusões-específicas-para-windows)
      - [Inclusões Específicas para Unix/Linux](#inclusões-específicas-para-unixlinux)
      - [Características Principais](#características-principais-5)
  - [Back-End](#back-end)
    - [1. Recebimento de Dados](#1-recebimento-de-dados)
    - [2. Validação da Requisição](#2-validação-da-requisição)
    - [3. Validação de Diretórios](#3-validação-de-diretórios)
    - [4. Processamento de URLs](#4-processamento-de-urls)
    - [5. Armazenamento de Dados](#5-armazenamento-de-dados)
    - [6. Formato do Arquivo JSON](#6-formato-do-arquivo-json)
    - [7. Sistema de Backup](#7-sistema-de-backup)
    - [8. Tratamento de Erros](#8-tratamento-de-erros)
  - [Definições Importantes](#definições-importantes)
    - [1. BACKEND\_HOST e BACKEND\_PATH](#1-backend_host-e-backend_path)
    - [2. upload\_dir no Backend](#2-upload_dir-no-backend)
    - [Segurança e Privacidade](#segurança-e-privacidade)
  - [Compilação](#compilação)
    - [Compilação para Windows](#compilação-para-windows)
      - [1. Requisitos](#1-requisitos)
      - [2. Passos para Compilação](#2-passos-para-compilação)
        - [2-1. Abrindo o Projeto no Visual Studio](#2-1-abrindo-o-projeto-no-visual-studio)
        - [2-2. Configurando o Projeto](#2-2-configurando-o-projeto)
        - [2-3. Compilando o Projeto](#2-3-compilando-o-projeto)
      - [2-4. Verificando a Compilação](#2-4-verificando-a-compilação)
    - [Compilação para Linux](#compilação-para-linux)
      - [1. Requisitos](#1-requisitos-1)
      - [2. Passos para Compilação](#2-passos-para-compilação-1)
        - [2-1. Construindo a Imagem Docker](#2-1-construindo-a-imagem-docker)
        - [2-2. `build.sh`](#2-2-buildsh)
        - [2-3. Construindo o Plugin](#2-3-construindo-o-plugin)
        - [2-4. `compile.sh`](#2-4-compilesh)
      - [3. Dockerfile](#3-dockerfile)
  - [Licença](#licença)
    - [Termos e Condições de Uso](#termos-e-condições-de-uso)
      - [1. Permissões Concedidas](#1-permissões-concedidas)
      - [2. Condições Obrigatórias](#2-condições-obrigatórias)
      - [3. Restrições e Limitações](#3-restrições-e-limitações)
      - [4. Propriedade Intelectual](#4-propriedade-intelectual)
      - [5. Isenção de Garantias e Limitação de Responsabilidade](#5-isenção-de-garantias-e-limitação-de-responsabilidade)

## Funcionalidades Principais

### 1. Coleta de Informações do Servidor
   - O plugin coleta automaticamente o IP e a porta do servidor em execução.
   - Identifica se o servidor é SA-MP ou open.mp e coleta a URL do site correspondente, se disponível.
   - Permite a configuração de uma URL de imagem personalizada através do parâmetro `spc_integration_image`, que deve ser adicionado ao arquivo de configuração do servidor.

### 2. Validação de URL
   - Antes de enviar a URL da imagem para o backend, o plugin valida se a URL fornecida é acessível e se corresponde a um formato de imagem válido (JPEG, PNG, GIF, etc.).
   - Isso garante que apenas URLs de imagens válidas sejam enviadas, evitando criações ou atualizações desnecessárias no JSON.

### 3. Integração com Backend
   - O plugin envia as informações coletadas para um backend via requisição HTTP POST.
   - O backend valida a requisição, garantindo que a `API_KEY` fornecida corresponda à chave configurada no backend. Isso é crucial para a segurança, pois impede que requisições não autorizadas sejam processadas.
   - Se os dados forem válidos, o backend cria um arquivo JSON no formato `IP-Port.json`, armazenando as informações do servidor.

### 4. Compatibilidade Multiplataforma
   - Suporta compilação para Linux (usando Docker, CMake e GCC 8) e Windows (usando Visual Studio 2022).
   - Funciona tanto para SA-MP quanto para open.mp, permitindo que todos servidores utilize o plugin.

## Como usar o Plugin

### 1. Download

- Baixe a versão mais recente do plugin na seção [releases](https://github.com/spc-samp/spc-integration/releases).
- Escolha o arquivo adequado para seu sistema operacional:
  - Windows: `spc-integration.dll`
  - Linux: `spc-integration.so`

### 2. Instalação

1. Extraia o arquivo baixado.
2. Coloque o plugin na pasta `plugins` do seu servidor.
3. Configure o servidor para carregar o plugin:
   - **Para SA-MP**: Adicione em seu `server.cfg`:
     ```
     plugins spc-integration
     ```
   - **Para open.mp**: Adicione `"spc-integration"` à lista `legacy_plugins` no seu `config.json`:
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
> Se você já possui outros plugins instalados, certifique-se de carregar o spc-integration após eles.

### 3. Configuração

Você precisa configurar a URL da imagem que será exibida para seu servidor. Escolha uma das opções abaixo de acordo com sua plataforma:

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
> A URL da imagem deve ser válida e acessível publicamente.

### 4. Verificação

1. Inicie seu servidor.
2. Verifique os logs do servidor. Se você ver uma mensagem similar a esta, o plugin está funcionando corretamente:
    ```
    [SPC Integration]: Information sent to the server data storage of the SPC:
    -- Server IP: '127.0.0.1'
    -- Server Port: '7777'
    -- Image URL configured: 'https://example.com/image.png'
    -- Web URL configured: 'https://example.com'
    ```

## Estrutura do Projeto

A estrutura do projeto é organizada da seguinte forma:
```
└── src/
    ├── cmake/
    │   ├── CMakeLists.txt               // Arquivo de configuração do CMake
    │   └── compile.sh                   // Script de compilação para Linux
    │
    ├── docker/
    │   ├── build.sh                     // Script para construir a imagem Docker
    │   └── Dockerfile                   // Arquivo Docker para compilação em Linux
    │
    ├── sdk/
    │   └── (SDK do SA-MP)               // SDK necessário para desenvolvimento do plugin
    │
    ├── amx_defines.h                    // Definições relacionadas ao AMX
    ├── base64_encoder.cpp               // Implementação do codificador Base64
    ├── base64_encoder.h                 // Cabeçalho do codificador Base64
    ├── http_client.cpp                  // Implementação do cliente HTTP
    ├── http_client.h                    // Cabeçalho do cliente HTTP
    ├── http_linux.cpp                   // Implementação específica para Linux do cliente HTTP
    ├── http_response.cpp                // Implementação da resposta HTTP
    ├── http_response.h                  // Cabeçalho da resposta HTTP
    ├── http_windows.cpp                 // Implementação específica para Windows do cliente HTTP
    ├── inclusions.h                     // Inclusões comuns e definições globais
    ├── logger.h                         // Cabeçalho para logging
    ├── main.cpp                         // Ponto de entrada do plugin
    ├── plugin_defines.h                 // Definições específicas do plugin
    ├── server_info.cpp                  // Implementação para coleta de informações do servidor
    ├── server_info.h                    // Cabeçalho para coleta de informações do servidor
    ├── spc-integration.sln              // Arquivo de solução do Visual Studio
    ├── spc-integration.vcxproj          // Arquivo de projeto do Visual Studio
    ├── spc-integration.vcxproj.filters  // Configuração de filtros do projeto Visual Studio
    ├── url_validator.cpp                // Implementação do validador de URL
    └── url_validator.h                  // Cabeçalho do validador de URL
```

## Detalhamento dos Códigos

Abaixo, é apresentada uma análise detalhada dos principais componentes do código do **SPC Integration**. Cada seção do código é explicada em profundidade para que seja possível compreender o funcionamento do plugin e sua integração com o backend.

### 1. Coleta de Informações do Servidor

| **Arquivos**      |
|-------------------|
| `server_info.h`   |
| `server_info.cpp` |

- A classe `Server_Info` é responsável por coletar e gerenciar informações essenciais do servidor, incluindo IP, porta, URLs de integração e website. O sistema suporta dois formatos de arquivo de configuração: server.cfg (SA-MP) e config.json (open.mp).

#### Estrutura Principal

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

#### Coleta de IP do Servidor

```cpp
bool Server_Info::Get_Server_IP() {
    #ifdef _WIN32
        // Windows: Usa WinSock API
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            return false;
            
        char hostname[256];

        if (gethostname(hostname, sizeof(hostname)) == 0) {
            // Código para obter IP no Windows
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

#### Leitura da Porta do Servidor

```cpp
bool Server_Info::Get_Server_Port() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Lê do arquivo server.cfg (SA-MP)
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
        // Lê do arquivo config.json (open.mp)
        std::ifstream config(CONFIG_FILE_OPEN);
        std::string json_content((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
        // Processa JSON para encontrar a porta
        // ...
    }
    return false;
}
```

#### URLs de imagem e Website

O sistema gerencia dois tipos de URLs:
1. URL de Imagem (`image_url`): Endereço da URL de imagem do servidor.
2. URL do Website (`web_url`): Endereço do website do servidor.

```cpp
bool Server_Info::Get_Image_URL() {
    if (File_Exists(CONFIG_FILE_SAMP)) {
        // Procura por "spc_integration_image" no arquivo
        if (/* URL encontrada */)
            image_config_status = Config_Status::Success;
        else
            image_config_status = Config_Status::Empty;
    }
    // Similar para CONFIG_FILE_OPEN
}

bool Server_Info::Get_Web_URL() {
    // Processo similar ao Get_ImageURL(), mas procura por "weburl" ou "website"
}
```

#### Status de Configuração

O sistema utiliza enumerações para controlar o estado das configurações:

```cpp
enum class Config_Status {
    Success,        // Configuração encontrada e válida
    Not_Found,      // Configuração não encontrada
    Empty,          // Configuração encontrada mas vazia
    Web_Not_Found,  // URL do website não encontrada
    Web_Empty       // URL do website vazia
};
```

#### Inicialização

O processo de inicialização é gerenciado pelo método `Initialize()`:

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

#### Características Principais

1. **Coleta de Informações**:
    - Detecção automática do IP do servidor.
    - Leitura da porta configurada.
    - Suporte a URLs de imagem e website.
    - Validação de todas as informações coletadas.

2. **Compatibilidade**:
    - Suporte a múltiplos sistemas operacionais.
    - Compatibilidade com SA-MP e open.mp.
    - Leitura de diferentes formatos de configuração.

3. **Gerenciamento de Estado**:
    - Sistema robusto de status para configurações.
    - Controle granular de erros e estados.
    - Validação individualizada de cada componente.

4. **Processamento de Dados**:
    - Limpeza automática de strings.
    - Detecção e remoção de espaços em branco.
    - Validação de URLs e configurações.

### 2. Validação de URL de imagem

| **Arquivos**        |
|---------------------|
| `url_validator.h`   |
| `url_validator.cpp` |

- O sistema de validação de URL é um componente crítico de segurança que realiza uma validação abrangente de URLs de imagens através de múltiplas camadas de verificação. Ele não apenas valida o formato da URL, mas também verifica se a URL aponta para um arquivo de imagem válido.

#### Visão Geral da Arquitetura

O processo de validação é implementado na classe `URL_Validator` e segue um pipeline de validação em múltiplos estágios:

- **Validação Inicial** (`Is_Valid`).
- **Gerenciamento de Timeout** (`Validate_With_Timeout`).
- **Processo de Validação Completa** (`Perform_Full_Validation`).
- **Verificação do Conteúdo da Imagem** (`Validate_Image_Headers`).

#### Validação Protegida por Timeout

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
    // ... tratamento de exceções
}
```

- O sistema implementa um mecanismo de timeout usando `std::async` para evitar travamentos em URLs lentas ou não responsivas. O processo de validação falhará automaticamente se exceder `VALIDATION_TIMEOUT` segundos (definido como 10 segundos no código).

#### Pipeline de Validação Completa

O método `Perform_FullValidation` implementa uma série de verificações:

```cpp
bool URL_Validator::Perform_Full_Validation(const std::string& url) {
    // Validação de comprimento
    if (url.empty() || url.length() > 2048)
        return (Log_Printf("[SPC Integration]: Error: URL is empty or too long (maximum 2048 characters)."), false);

    // Validação de protocolo
    if (!Has_Valid_Scheme(url))
        return (Log_Printf("[SPC Integration]: Error: URL must start with 'http://' or 'https://'."), false);

    // Validação de estrutura
    if (!Has_Valid_HostAndPath(url))
        return (Log_Printf("[SPC Integration]: Error: URL must contain a valid hostname and path."), false);

    // Validação de caracteres
    if (!Has_Valid_Characters(url))
        return (Log_Printf("[SPC Integration]: Error: URL contains invalid characters."), false);

    // Validação de imagem
    if (!Validate_Image_Headers(url))
        return (Log_Printf("[SPC Integration]: Error: The URL content is not a valid image."), false);

    Log_Printf("[SPC Integration]: Validation successfully completed!");

    return true;
}
```

#### Validação de Componentes da URL

O sistema inclui validadores especializados para diferentes componentes da URL:

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

#### Validação do Conteúdo da Imagem

O sistema realiza a validação real da imagem verificando os cabeçalhos do arquivo:

```cpp
bool URL_Validator::Check_Image_Magic_Numbers(const std::vector<unsigned char>& data) {
    if (data.size() < 4)
        return false;

    // Suporta múltiplos formatos de imagem:
    // JPEG: FF D8 FF
    if (data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF)
        return true;

    // PNG: 89 50 4E 47 0D 0A 1A 0A
    if (data.size() >= 8 && data[0] == 0x89 && data[1] == 0x50 /* ... */)
        return true;

    // Formatos adicionais: GIF, BMP, WebP
    // ...
}
```

#### Implementação Multiplataforma

O sistema inclui implementações específicas para cada plataforma para buscar dados de imagem:

- **Windows**: Usa a API WinHTTP (`Fetch_Image_Data_Windows`).
- **Linux**: Usa OpenSSL e programação de sockets (`Fetch_Image_Data_Linux`).

Ambas as implementações:
- Estabelecem conexões seguras (HTTPS).
- Solicitam apenas a porção do cabeçalho da imagem (primeiros 16 bytes).
- Gerenciam limpeza de conexão e recursos.

#### Características Principais

1. **Validação Abrangente**:
    - Formato e estrutura da URL.
    - Segurança do protocolo (suporte a HTTPS).
    - Validação de domínio e caminho.
    - Validação de conjunto de caracteres.
    - Verificação do formato da imagem.

2. **Recursos de Segurança**:
    - Proteção contra timeout.
    - Limite máximo de comprimento da URL.
    - Conexões seguras multiplataforma.
    - Validação de imagem eficiente em memória.

3. **Formatos de Imagem Suportados**:
    - JPEG
    - PNG
    - GIF
    - BMP
    - WebP

4. **Tratamento de Erros**:
    - Registro detalhado em cada estágio de validação.
    - Gerenciamento elegante de timeout.
    - Tratamento de erros específico da plataforma.
    - Limpeza de recursos em todos os cenários.

### 3. Cliente HTTP

| **Arquivos**        |
|---------------------|
| `http_client.h`     |
| `http_client.cpp`   |
| `http_windows.cpp`  |
| `http_linux.cpp`    |
| `http_response.h`   |
| `http_response.cpp` |

- O cliente HTTP é responsável por enviar as informações coletadas para o backend via HTTPS. A implementação é multiplataforma, utilizando WinHTTP no Windows e OpenSSL/sockets no Linux, garantindo comunicação segura através de SSL/TLS.

#### Estrutura e Funcionamento

O arquivo principal `http_client.h` define a interface da classe:

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

A implementação em `http_client.cpp` seleciona automaticamente a implementação correta:

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

#### Implementação Windows (WinHTTP)

Em `http_windows.cpp`, a implementação usa a API WinHTTP:

```cpp
bool HTTP_Client::Send_Request_Windows(const std::wstring& host, const std::wstring& path, const std::string& data) {
    HINTERNET spc_session = WinHttpOpen(L"SPC-INTEGRATION/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    // Configura timeout de 60 segundos
    DWORD timeout = 60000;

    WinHttpSetOption(spc_session, WINHTTP_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
    WinHttpSetOption(spc_session, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

    // Conecta e envia requisição HTTPS
    HINTERNET spc_connect = WinHttpConnect(spc_session, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    
    // ... resto da implementação Windows
}
```

#### Implementação Linux (OpenSSL)

Em `http_linux.cpp`, a implementação usa OpenSSL com sockets:

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

    // Cria e configura socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;

    // ... resto da implementação Linux
}
```

#### Processamento de Resposta

A classe `HTTP_Response` em `http_response.h` processa as respostas do servidor:

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

A implementação em `http_response.cpp` trata diferentes tipos de resposta:

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
    // ... outros tipos de erro

    Log_Printf("%s %s: %s", prefix, error_prefix, message.c_str());
}
```

#### Características Principais

1. **Comunicação Segura**:
    - HTTPS (porta 443) com SSL/TLS.
    - Timeout de 60 segundos para conexão, envio e recebimento.
    - Content-Type: `application/x-www-form-urlencoded` com UTF-8.

2. **Tratamento de Erros**:
    - Verifica cada etapa da comunicação.
    - Libera recursos adequadamente.
    - Logging detalhado por tipo de erro:
        - Erros de servidor: Sugere verificar configurações.
        - Erros de autenticação: Indica verificar API key.
        - Erros de validação: Recomenda revisar configurações.

3. **Formato da Resposta JSON**:
    ```json
    {
        "success": true/false,
        "message": "Mensagem de resposta"
    }
    ```

### 4. Codificação Base64

| **Arquivos**         |
|----------------------|
| `base64_encoder.h`   |
| `base64_encoder.cpp` |

- A codificação Base64 é utilizada para codificar a URL da imagem antes de enviá-la ao backend. Isso é especialmente útil quando a URL contém caracteres especiais que podem não ser tratados corretamente em uma requisição HTTP.

#### Definição da Interface

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

- A interface é definida usando guardas de inclusão para evitar múltiplas definições. A classe utiliza um método estático `Encode` que aceita uma string como entrada e retorna sua versão codificada.

#### Alfabeto Base64 e Implementação

```cpp
#include "base64_encoder.h"

const std::string Base64_Encoder::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
```

- O alfabeto Base64 é definido como uma string constante contendo 64 caracteres diferentes. Esta string é utilizada como lookup table durante o processo de codificação.

#### Inicialização e Buffers

```cpp
// ... "Alfabeto Base64 e Implementação" ...

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

- São inicializados dois arrays de caracteres: um para armazenar os 3 bytes de entrada e outro para os 4 caracteres Base64 resultantes. A string de entrada é convertida para um array de caracteres para processamento byte a byte.

#### Loop Principal de Codificação

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Inicialização e Buffers" ...

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

- O loop principal processa a entrada em grupos de 3 bytes, convertendo-os em 4 caracteres Base64 através de operações bit a bit. Cada grupo de 24 bits é dividido em quatro grupos de 6 bits.

#### Tratamento de Padding

```cpp
std::string Base64_Encoder::Encode(const std::string& input) {
    // ... "Loop Principal de Codificação" ...

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

- Para entradas que não são múltiplos de 3 bytes, é necessário adicionar padding. Os bytes restantes são preenchidos com zeros e codificados, e o caractere '=' é adicionado para completar o grupo de 4 caracteres.

#### Características Principais

1. **Processamento de Dados**:
    - Conversão de grupos de 3 bytes em 4 caracteres Base64.
    - Manipulação bit a bit para extração precisa dos valores.
    - Tratamento automático de padding para tamanhos não múltiplos de 3.

2. **Design e Arquitetura**:
    - Implementação modular com separação clara de responsabilidades.
    - Uso de métodos estáticos para facilitar o acesso.
    - Encapsulamento do alfabeto Base64 como membro privado.

3. **Otimização e Performance**:
    - Processamento eficiente byte a byte.
    - Uso de arrays fixos para minimizar alocações de memória.
    - Operações bit a bit otimizadas para conversão rápida.

4. **Robustez e Confiabilidade**:
    - Manipulação segura de strings de qualquer tamanho.
    - Garantia de saída sempre válida em Base64.
    - Preservação da integridade dos dados durante a codificação.

### 5. Logging

| **Arquivos** |
|--------------|
| `logger.h`   |

- O sistema de logging é uma parte fundamental do plugin, pois permite que os desenvolvedores monitorem o comportamento do plugin e identifiquem problemas. O uso de logs ajuda na depuração e na manutenção do código.

#### Definição da Interface

```cpp
#ifndef LOGGER_H
    #define LOGGER_H

    typedef void (*Log_Printf_t)(const char* Format, ...);
    extern Log_Printf_t Log_Printf;
#endif
```

- O sistema de logging é definido através de um ponteiro para função que utiliza argumentos variáveis, permitindo flexibilidade na formatação das mensagens. A declaração `extern` indica que a implementação real da função será fornecida em tempo de execução.

#### Definição do Tipo da Função

```cpp
typedef void (*Log_Printf_t)(const char* Format, ...);
```

O tipo `Log_Printf_t` define a assinatura da função de logging:
- `void`: A função não retorna valor
- `const char* Format`: Primeiro parâmetro é uma string de formato
- `...`: Permite argumentos variáveis para formatação dinâmica

#### Declaração do Ponteiro de Função

```cpp
extern Log_Printf_t Log_Printf;
```

O ponteiro `Log_Printf` é declarado como externo, permitindo que:
- A implementação real seja fornecida pela aplicação host.
- O plugin utilize a infraestrutura de logging existente.
- As mensagens sejam integradas ao sistema de logging principal.

#### Características Principais

1. **Flexibilidade de Implementação**:
    - Suporte a argumentos variáveis para formatação dinâmica.
    - Possibilidade de integração com diferentes sistemas de logging.
    - Implementação pode ser fornecida em tempo de execução.

2. **Integração com o Sistema Host**:
    - Utilização da infraestrutura de logging existente.
    - Mensagens podem ser direcionadas para diferentes saídas.
    - Consistência com o logging da aplicação principal.

3. **Facilidade de Uso**:
    - Interface simples e familiar (similar a printf).
    - Pode ser utilizado em qualquer parte do código.
    - Não requer configuração adicional no código do plugin.

### 6. Ponto de Entrada do Plugin

| **Arquivos** |
|--------------|
| `main.cpp`   |

- O ponto de entrada do plugin é onde a execução do plugin começa. Este arquivo é responsável por:
    - Inicializar funções essenciais do AMX.
    - Coletar e validar informações do servidor.
    - Verificar configurações no arquivo server.cfg/config.json.
    - Enviar dados ao backend do SPC.

#### Principais Funções de Entrada

```cpp
// Carregamento inicial do plugin.
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** Plugin_Data) {
    // Inicializa funções do AMX e sistema de logging.
    // Coleta informações do servidor.
    // Valida URLs da imagem e website.
    // Envia dados para o backend.
    // Exibe informações de status.
}

// Descarregamento do plugin.
PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    // Finaliza o plugin.
}

// Recursos suportados.
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

// Carregamento de scripts AMX.
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* Amx) {
    return AMX_ERR_NONE;
}

// Descarregamento de scripts AMX.
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* Amx) {
    return AMX_ERR_NONE;
}
```

1. **Processo de Inicialização**:
    - Inicializa funções essenciais do AMX e sistema de logging.
    - Coleta informações do servidor através da classe `Server_Info`.
    - Verifica a existência e validade dos parâmetros:
        - `spc_integration_image` no arquivo de configuração.
        - `weburl/website` no arquivo de configuração.
    - Valida as URLs fornecidas.
    - Tenta enviar os dados para o backend (primeiro como "create", depois como "update" se necessário).
    - Exibe informações detalhadas sobre o status da inicialização.

2. **Validações e Verificações**:
    - Verifica a presença e validade da URL da imagem.
    - Verifica a presença e validade da URL do website.
    - Valida as URLs usando a classe `URL_Validator`.
    - Tenta reconexão automática em caso de falha no envio inicial.

3. **Feedback e Logging**:
    - Exibe um banner informativo com detalhes do plugin e links sociais.
    - Fornece mensagens detalhadas sobre erros de configuração.
    - Mostra o status final da inicialização com as informações do servidor.

### 7. Definições e Inclusões

| **Arquivos**         |
|----------------------|
| `plugin_defines.h`   |
| `inclusions.h`       |

- Esses arquivos contêm definições e inclusões necessárias para o funcionamento do plugin, estabelecendo constantes importantes e garantindo compatibilidade multiplataforma.

#### Definições do Plugin

```cpp
#ifndef PLUGIN_DEFINES_H
    #define PLUGIN_DEFINES_H
    
    #define PLUGIN_VERSION "1.0.0"
    #define BACKEND_HOST "example_site.com" // Sem o protocolo 'https://' ou 'http://'.
    #define BACKEND_PATH "/backend_directory/spc-integration.php"
    #define API_KEY "YOUR_SECURE_KEY_TO_ACCESS_PHP"
    #define CONFIG_FILE_SAMP "server.cfg"
    #define CONFIG_FILE_OPEN "config.json"
#endif
```

O arquivo de definições contém constantes cruciais para o funcionamento do plugin:
- Versão do plugin.
- Configurações do backend para comunicação.
- Chave de API para autenticação.
- Nomes dos arquivos de configuração.

#### Estrutura Base das Inclusões

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

Inclusão das bibliotecas padrão C++ necessárias para:
- Manipulação de strings e arquivos.
- Expressões regulares.
- Operações assíncronas.
- Manipulação de tempo.

#### Inclusões Específicas para Windows

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

Suporte específico para sistemas Windows:
- APIs de rede Windows.
- Bibliotecas HTTP Windows.
- Configurações de linkagem.

#### Inclusões Específicas para Unix/Linux

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

Suporte específico para sistemas Unix/Linux:
- APIs de rede POSIX.
- Suporte a SSL via OpenSSL.
- Interfaces de rede.

#### Características Principais

1. **Configuração do Backend**:
    - Host e path configuráveis para flexibilidade de implantação.
    - Chave de API para autenticação segura.
    - Versionamento explícito do plugin.

2. **Compatibilidade Multiplataforma**:
    - Suporte nativo a Windows e Unix/Linux.
    - Abstração de APIs específicas do sistema.
    - Implementações condicionais para cada plataforma.

3. **Segurança e Comunicação**:
    - Suporte a SSL/TLS para comunicação segura.
    - Autenticação via chave de API.
    - Bibliotecas robustas para networking.

4. **Gerenciamento de Recursos**:
    - Suporte a operações assíncronas.
    - Manipulação eficiente de strings e arquivos.
    - Controle de tempo e temporização.

## Back-End

O backend é responsável por receber as informações enviadas pelo plugin e armazená-las em um arquivo JSON. Aqui está uma explicação detalhada de seu funcionamento:

### 1. Recebimento de Dados
  - O plugin envia uma requisição HTTP POST contendo as informações do servidor (IP, porta, URL do site e URL da imagem).
  - O backend valida a requisição, garantindo que a `API_KEY` fornecida corresponda à chave configurada no backend.
  - Isso é crucial para a segurança, pois impede que requisições não autorizadas sejam processadas.
  - Suporta URLs tanto em formato normal quanto codificadas em base64.

### 2. Validação da Requisição
   - O backend verifica se a `API_KEY` fornecida na requisição é válida.
   - Utiliza a função `hash_equals()` para comparação segura das chaves.
   - Se a chave não for válida, retorna um erro de autenticação.
   - O código a seguir ilustra essa validação:
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

### 3. Validação de Diretórios
  - Verifica a existência dos diretórios necessários:
      - `exemple_directory` como diretório base.
      - `exemple_servers` como local de armazenamento.
  - Confirma as permissões de escrita no diretório de upload.
  - Retorna mensagens de erro específicas caso alguma validação falhe.

### 4. Processamento de URLs
   - Funções específicas para processar URLs de imagem e web.
   - Suporte a URLs normais e codificadas em base64.
   - Validação da decodificação base64 quando utilizada.
   - Tratamento de erros para URLs inválidas.

### 5. Armazenamento de Dados
   - Cria arquivos JSON únicos no formato `IP-Port.json`.
   - Sanitiza os nomes dos arquivos para segurança.
   - Define permissões apropriadas (chmod 0644).
   - Implementa sistema de backup para atualizações.
   - O código abaixo mostra o processo de armazenamento:
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

### 6. Formato do Arquivo JSON
   - Estrutura clara e organizada dos dados.
   - Utiliza formatação pretty-print para melhor legibilidade.
   - Preserva formatação de URLs com slashes não escapadas.
   - Exemplo do conteúdo do arquivo JSON:
        ```json
        {
            "spc_integration_image": "https://example.com/image.png",
            "spc_web_url": "https://example.com"
        }
        ```

### 7. Sistema de Backup
   - Cria backup automático antes de atualizações.
   - Restaura dados originais em caso de falha.
   - Remove arquivos de backup após operações bem-sucedidas.
   - Garante integridade dos dados durante atualizações.

### 8. Tratamento de Erros
   - Mensagens de erro detalhadas e específicas.
   - Validações em cada etapa do processo.
   - Respostas consistentes em formato JSON.
   - Tipos de erro tratados:
       - Falhas de autenticação.
       - Problemas com diretórios.
       - Erros em operações de arquivo.
       - Falhas de validação.
       - Restrições de método HTTP.

## Definições Importantes

### 1. BACKEND_HOST e BACKEND_PATH

No arquivo `plugin_defines.h`, você encontrará as seguintes definições:

```cpp
#define BACKEND_HOST "example_site.com" // Sem o protocolo 'https://' ou 'http://'.
#define BACKEND_PATH "/backend_directory/spc-integration.php"
```

- **BACKEND_HOST**: Esta definição representa o endereço do servidor onde o backend está hospedado. No contexto do plugin, este é o local para onde as informações do servidor serão enviadas. É importante notar que, por razões de segurança, a SPC não divulga o endereço real do backend. Isso é feito para proteger a integridade e a segurança dos dados, evitando que informações sensíveis sejam expostas.

- **BACKEND_PATH**: Esta definição especifica o caminho do script PHP que processará as requisições enviadas pelo plugin. O caminho deve ser acessível a partir do `BACKEND_HOST` e deve estar configurado para aceitar requisições POST. O script PHP é responsável por validar os dados recebidos e armazená-los em um arquivo JSON.

### 2. upload_dir no Backend

No script PHP (`spc-integration.php`), a variável `upload_dir` é definida da seguinte forma:

```php
$upload_dir = $base_dir . '/exemple_directory/exemple_servers/';
```

- **upload_dir**: Este diretório é onde os arquivos JSON que contêm as informações do servidor serão armazenados. O backend verifica se este diretório existe e se é gravável antes de tentar criar ou modificar arquivos. Se o diretório não existir ou não for gravável, o backend retornará um erro, informando que não foi possível armazenar os dados.

### Segurança e Privacidade

A SPC prioriza a segurança e a privacidade dos dados. Por isso, o endereço real do backend e a `API_KEY` não são divulgados publicamente. O plugin compilado disponibilizado em [releases](https://github.com/spc-samp/spc-integration/releases) utiliza o endereço e a `API_KEY` da SPC para armazenar as informações do servidor de forma segura. Isso garante que apenas requisições autorizadas sejam processadas e que os dados dos servidores sejam protegidos contra acessos não autorizados.

## Compilação

O **SPC Integration** pode ser compilado em ambientes Windows e Linux. Esta seção detalha o processo de compilação, incluindo a configuração do ambiente, o uso de Docker, CMake e scripts de compilação.

### Compilação para Windows

#### 1. Requisitos

Para compilar o plugin em um ambiente Windows, são necessários:

- **Visual Studio 2022**: O Visual Studio deve estar instalado com suporte para C++, com a opção para desenvolvimento de desktop com C++ selecionada durante a instalação.

#### 2. Passos para Compilação

##### 2-1. Abrindo o Projeto no Visual Studio

1. Abrir o Visual Studio 2022.
2. Navegar até o arquivo `spc-integration.sln` no projeto e abri-lo.
3. O Visual Studio carregará o projeto e suas configurações.

##### 2-2. Configurando o Projeto

- A versão do C++ deve estar definida como C++17 nas configurações do projeto em **Project Properties** > **Configuration Properties** > **C/C++** > **Language** > **C++ Language Standard**.

##### 2-3. Compilando o Projeto

- Com o projeto configurado, selecionar "Build" no menu superior e escolher "Build Solution" ou pressionar `Ctrl + Shift + B`.
- O Visual Studio compilará o projeto e gerará o plugin.

#### 2-4. Verificando a Compilação

- Após uma compilação bem-sucedida, o arquivo do plugin (`spc-integration.dll`) estará disponível na pasta de saída (geralmente `Debug` ou `Release`).

### Compilação para Linux

#### 1. Requisitos

O ambiente de compilação requer as seguintes ferramentas:

- **Docker**: Plataforma para criar, implantar e executar aplicativos em contêineres. O Docker é utilizado para criar um ambiente de compilação isolado.
- **CMake**: Ferramenta de automação de compilação que utiliza arquivos de configuração para gerar arquivos de projeto para diferentes sistemas de compilação.
- **GCC 8**: Compilador GNU C++ utilizado para compilar o código do plugin.

#### 2. Passos para Compilação

##### 2-1. Construindo a Imagem Docker

O processo inicia-se navegando até a pasta `docker` e executando o script `build.sh` para construir a imagem Docker e compilar o plugin. Este script cria um ambiente de compilação contendo todas as dependências necessárias e realiza a compilação automaticamente.

```bash
cd docker
./build.sh
```

##### 2-2. `build.sh`

O script `build.sh` executa as seguintes operações:

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

- **Características**:
  - O script verifica a instalação do Docker
  - Cria um diretório temporário para armazenar os arquivos necessários para a compilação
  - Os arquivos de código-fonte e cabeçalhos são copiados para o diretório temporário, onde a imagem Docker será construída

##### 2-3. Construindo o Plugin

O script `build.sh` gerencia todo o processo de compilação. Ele utiliza o Docker para criar um ambiente isolado e executa o script `compile.sh` automaticamente dentro do contêiner. O processo inclui:
1. Criação de uma imagem Docker com todas as dependências
2. Execução do contêiner com o ambiente de compilação
3. Compilação do plugin usando CMake
4. Cópia dos arquivos compilados para a pasta `build` no diretório do projeto

##### 2-4. `compile.sh`

O script `compile.sh` é responsável pela configuração e compilação do projeto usando CMake:

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

- **Características**:
    - Remove qualquer diretório de build anterior e cria um novo
    - Utiliza CMake para configurar o projeto, especificando o tipo de build como "Release" para otimizações
    - O comando `make` compila o projeto, utilizando todos os núcleos disponíveis (`-j$(nproc)`)
    - Após a compilação, o plugin é "stripado" para remover informações de depuração
    - O script verifica as dependências do binário gerado usando `ldd`

#### 3. Dockerfile

O `Dockerfile` define o ambiente de compilação. Exemplo de configuração típica para este projeto:

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
    - **FROM ubuntu:18.04**: Define a imagem base como Ubuntu 18.04
    - **RUN apt-get update && apt-get install -y**: Atualiza a lista de pacotes e instala as dependências necessárias
    - **WORKDIR /app**: Define o diretório de trabalho dentro do contêiner
    - **COPY . .**: Copia os arquivos do diretório atual para o diretório de trabalho no contêiner
    - **RUN cmake . && make**: Executa CMake para compilar o projeto dentro do contêiner

> [!IMPORTANT]
> A utilização de um Dockerfile garante que o ambiente de compilação seja reproduzível e isolado, evitando conflitos de dependências que podem ocorrer em sistemas locais. Esta abordagem é especialmente útil quando diferentes desenvolvedores ou servidores possuem configurações de ambiente variadas.

## Licença

Copyright © **SA-MP Programming Community**

Este software é licenciado sob os termos da Licença Apache, Versão 2.0 ("Licença"); você não pode utilizar este software exceto em conformidade com a Licença. Uma cópia da Licença pode ser obtida em: [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)

### Termos e Condições de Uso

#### 1. Permissões Concedidas

A presente licença concede, gratuitamente, a qualquer pessoa que obtenha uma cópia deste software e arquivos de documentação associados, os seguintes direitos:
* Utilizar, copiar, modificar e distribuir o software em qualquer meio ou formato, para qualquer finalidade, comercial ou não-comercial
* Mesclar, publicar, distribuir, sublicenciar e/ou vender cópias do software
* Permitir que pessoas para as quais o software é fornecido façam o mesmo

#### 2. Condições Obrigatórias

Todas as distribuições do software ou trabalhos derivados devem:
* Incluir uma cópia completa desta licença
* Indicar claramente quaisquer modificações realizadas no código-fonte original
* Preservar todos os avisos de direitos autorais, patentes, marcas registradas e atribuições
* Fornecer documentação adequada das alterações implementadas
* Manter o aviso de licença e garantia em todas as cópias

#### 3. Restrições e Limitações

* Esta licença não concede permissão para uso de marcas registradas, logotipos ou nomes comerciais da **SA-MP Programming Community**
* As contribuições para o código-fonte devem ser licenciadas sob os mesmos termos desta licença
* O uso de nomes dos contribuidores para endossar ou promover produtos derivados deste software requer permissão prévia específica

#### 4. Propriedade Intelectual

O software e toda a documentação associada são protegidos por leis de direitos autorais e tratados internacionais. A **SA-MP Programming Community** retém todos os direitos, títulos e interesses não expressamente concedidos por esta licença.

#### 5. Isenção de Garantias e Limitação de Responsabilidade

O SOFTWARE É FORNECIDO "COMO ESTÁ", SEM GARANTIAS DE QUALQUER NATUREZA, EXPRESSAS OU IMPLÍCITAS, INCLUINDO, MAS NÃO SE LIMITANDO A, GARANTIAS DE COMERCIALIZAÇÃO, ADEQUAÇÃO A UM PROPÓSITO ESPECÍFICO E NÃO VIOLAÇÃO. 

EM NENHUMA CIRCUNSTÂNCIA OS AUTORES OU TITULARES DOS DIREITOS AUTORAIS SERÃO RESPONSÁVEIS POR QUAISQUER REIVINDICAÇÕES, DANOS OU OUTRAS RESPONSABILIDADES, SEJA EM AÇÃO DE CONTRATO, DELITO OU DE OUTRA FORMA, DECORRENTES DE, OU EM CONEXÃO COM O SOFTWARE OU O USO OU OUTRAS NEGOCIAÇÕES NO SOFTWARE.

---

Para informações detalhadas sobre a Licença Apache 2.0, consulte: http://www.apache.org/licenses/LICENSE-2.0