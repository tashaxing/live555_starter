cmake_minimum_required(VERSION 3.0)

project(live555_starter)

if (WIN32)
    add_definitions(
        -D_CRT_SECURE_NO_WARNINGS
        -D_WINSOCK_DEPRECATED_NO_WARNINGS
        -DNO_GETIFADDRS
    )
else()
    add_definitions(
        -DSOCKLEN_T=socklen_t 
        -D_LARGEFILE_SOURCE=1 
        -D_FILE_OFFSET_BITS=64
    )
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/openssl-1.1.1g/include

    ${CMAKE_CURRENT_SOURCE_DIR}/live/BasicUsageEnvironment/include
    ${CMAKE_CURRENT_SOURCE_DIR}/live/groupsock/include
    ${CMAKE_CURRENT_SOURCE_DIR}/live/UsageEnvironment/include
    ${CMAKE_CURRENT_SOURCE_DIR}/live/liveMedia/include
)

if (WIN32)
    link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/openssl-1.1.1g/prebuild/win
    )
else()
    link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/openssl-1.1.1g/prebuild/linux
    )
endif()

file(GLOB LIVE555_SRC
    live/BasicUsageEnvironment/*.cpp
    live/groupsock/*.cpp 
    live/groupsock/*.c
    live/UsageEnvironment/*.cpp
    live/liveMedia/*.hh 
    live/liveMedia/*.cpp 
    live/liveMedia/*.c
)

file(GLOB STREAM_SERVER_DEMO_SRC
    ${LIVE555_SRC}
    src/*.h
    src/*.cpp
)

add_executable(stream_server_demo
    ${STREAM_SERVER_DEMO_SRC}
)

if (WIN32)
    target_link_libraries(stream_server_demo
        ws2_32
        libssl
        libcrypto
    )
else()
    target_link_libraries(stream_server_demo
        ssl
        crypto
    )
endif()
