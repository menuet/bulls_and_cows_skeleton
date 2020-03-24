
cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

enable_testing()

project(bulls_and_cows LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
    add_compile_options(/wd4100)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-Werror -Wall -Wno-unused-parameter)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-missing-prototypes
            -Wno-c++2a-compat
            -Wno-documentation-unknown-command
            -Wno-inconsistent-missing-destructor-override
            -Wno-signed-enum-bitfield
            -Wno-deprecated
            -Wno-undefined-func-template
            )
    endif()
endif()

if(
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" OR
    ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows"))
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(thirdparties)
add_subdirectory(src/bulls_and_cows_lib)
add_subdirectory(src/bulls_and_cows_prg)
add_subdirectory(src/bulls_and_cows_ut)
