cmake_minimum_required(VERSION 3.20)
project(TrabalhoGb VERSION 1.0)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts ")
set(CMAKE_CXX_FLAGS_RELEASE "-fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts ")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(TrabalhoGb
    src/StringUtils.cpp
    src/IdUtils.cpp
    src/Button.cpp
    src/TabHeader.cpp
    src/Tab.cpp
    src/Browser.cpp
    src/Tokenizer.cpp
    src/HtmlParser.cpp
    src/main.cpp)

add_custom_command(
        TARGET TrabalhoGb POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources/
                $<TARGET_FILE_DIR:TrabalhoGb>/resources/)

target_link_libraries(TrabalhoGb PRIVATE sfml-graphics)

if(WIN32)
    add_custom_command(
        TARGET TrabalhoGb
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll $<TARGET_FILE_DIR:TrabalhoGb>
        VERBATIM)
endif()

