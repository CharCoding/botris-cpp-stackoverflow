
cmake_minimum_required(VERSION 3.22)

project("botris bot")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add BMI2 flag for compilers that support it
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-mbmi2)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/arch:AVX2)  # MSVC uses a different flag
endif()

if(UNIX AND NOT APPLE)
    option(USE_TLS "" ON)
    option(USE_WS "" ON)

    add_subdirectory("./modules/IXWebSocket")

    find_package(ixwebsocket)
else()
    find_package(ixwebsocket CONFIG REQUIRED)

endif()


set(main_sources
    "src/main.cpp"

    # this is where you put the rest of your sources
)

set(test_sources
    "src/test.cpp"
)

add_executable(main ${main_sources})
add_executable(test ${test_sources})

target_link_libraries(main PRIVATE ixwebsocket::ixwebsocket)
include_directories(src/include)