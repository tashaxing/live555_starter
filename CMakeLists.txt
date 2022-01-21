cmake_minimum_required(VERSION 3.0)

project(live555_starter)

if (WIN32)
    add_definitions(
        -D_CRT_SECURE_NO_WARNINGS
        -D_WINSOCK_DEPRECATED_NO_WARNINGS
    )
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/live/BasicUsageEnvironment/include
    ${CMAKE_CURRENT_SOURCE_DIR}/live/groupsock/include
    ${CMAKE_CURRENT_SOURCE_DIR}/live/UsageEnvironment/include
    ${CMAKE_CURRENT_SOURCE_DIR}/live/liveMedia/include
)

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

