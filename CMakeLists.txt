cmake_minimum_required(VERSION 3.30)

project(miniglib
    VERSION "2.83.3"
    DESCRIPTION "TODO"
    HOMEPAGE_URL "https://github.com/jcbhmr/miniglib"
    LANGUAGES C
)

set(C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall)
endif()

message(STATUS "Binary dir: ${CMAKE_BINARY_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(MSVC)
    if(NOT "Asan" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
    endif()

    set(CMAKE_EXE_LINKER_FLAGS_ASAN "/DEBUG")
    add_compile_options("$<$<CONFIG:Asan>:/DEBUG /fsanitize=address>")
    add_link_options("$<$<CONFIG:Debug>:/NODEFAULTLIB:MSVCRT>")
else()
    # Support for sanitizer build types
    set(CMAKE_C_FLAGS_ASAN
        "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1"
        CACHE STRING "Flags used by the C compiler during AddressSanitizer builds."
        FORCE)
    
    set(CMAKE_C_FLAGS_LSAN
        "-fsanitize=leak -fno-omit-frame-pointer -g -O1"
        CACHE STRING "Flags used by the C compiler during LeakSanitizer builds."
        FORCE)
    
    set(CMAKE_C_FLAGS_MSAN
        "-fsanitize=memory -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer -g -O2"
        CACHE STRING "Flags used by the C compiler during MemorySanitizer builds."
        FORCE)
    
    set(CMAKE_C_FLAGS_UBSAN
        "-fsanitize=undefined"
        CACHE STRING "Flags used by the C compiler during UndefinedBehaviourSanitizer builds."
        FORCE)
endif()

include(CTest)

if(BUILD_TESTING)
    find_package(check REQUIRED)
    enable_testing()

    add_subdirectory(tests)
    add_subdirectory(perf_tests)
endif()
