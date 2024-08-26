
cmake_minimum_required(VERSION 3.22)

project("botris bot")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add BMI2 flag for compilers that support it
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-mbmi2 -mlzcnt)
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


add_executable(main ${main_sources})

target_link_libraries(main PRIVATE ixwebsocket::ixwebsocket)
include_directories(src/include)

include(CTest)
add_executable(TestPrintPiece "src/tests/TestPrintPiece.cpp")
add_test(NAME TestPrintPiece COMMAND TestPrintPiece)
add_executable(TestClearLines "src/tests/TestClearLines.cpp")
add_test(NAME TestClearLines COMMAND TestClearLines)
add_executable(TestCheckPiece "src/tests/TestCheckPiece.cpp")
add_test(NAME TestCheckPiece COMMAND TestCheckPiece)
add_executable(TestMoveGen "src/tests/TestMoveGen.cpp")
add_test(NAME TestMoveGen COMMAND TestMoveGen)