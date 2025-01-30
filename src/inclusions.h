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
#endif