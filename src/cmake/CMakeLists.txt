cmake_minimum_required(VERSION 3.19)
project(spc-integration)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--hash-style=both")

set(SOURCES 
    ${CMAKE_SOURCE_DIR}/../base64_encoder.cpp
    ${CMAKE_SOURCE_DIR}/../http_client.cpp
    ${CMAKE_SOURCE_DIR}/../http_linux.cpp
    ${CMAKE_SOURCE_DIR}/../http_response.cpp
    ${CMAKE_SOURCE_DIR}/../main.cpp
    ${CMAKE_SOURCE_DIR}/../server_info.cpp
    ${CMAKE_SOURCE_DIR}/../url_validator.cpp
)

add_library(spc-integration SHARED ${SOURCES})

target_include_directories(spc-integration PRIVATE 
    ${CMAKE_SOURCE_DIR}/..
    ${CMAKE_SOURCE_DIR}/../sdk
    /usr/include/i386-linux-gnu
)

if(UNIX)
    target_compile_definitions(spc-integration PRIVATE 
        LINUX=1
        _LINUX=1
    )
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fvisibility=hidden")
    
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++ -Wl,--gc-sections")
    
    target_link_libraries(spc-integration PRIVATE
        pthread
        -static
        -Wl,-Bstatic
        /usr/lib/i386-linux-gnu/libssl.a
        /usr/lib/i386-linux-gnu/libcrypto.a
        -Wl,-Bdynamic
        dl
        z
    )
    
    set_target_properties(spc-integration PROPERTIES
        PREFIX ""
        OUTPUT_NAME "spc-integration"
        SUFFIX ".so"
    )
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")