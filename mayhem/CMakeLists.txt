if(BUILD_FUZZER)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Fuzzer is only supported on Clang")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer-no-link,address,undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize-recover=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
    add_link_options(-fsanitize=fuzzer-no-link,address,undefined)
endif()

include(../AbletonLinkConfig.cmake)

add_executable(Link_fuzz Link_fuzz.cpp)

target_compile_options(Link_fuzz PUBLIC -fsanitize=fuzzer,address,undefined)
target_link_options(Link_fuzz PUBLIC -fsanitize=fuzzer,address,undefined)

#file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testsuite)
#file (COPY testsuite/test-audio.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/testsuite)

target_link_libraries(Link_fuzz PUBLIC Ableton::Link)