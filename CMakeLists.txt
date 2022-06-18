cmake_minimum_required(VERSION 3.14)

project(cpp_algs)

add_executable(main main.cpp)
target_compile_features(main PUBLIC cxx_std_17)
target_compile_definitions(main PUBLIC
        $<$<CONFIG:Debug>:LOGGING SYNC_IO>
        $<$<CONFIG:Release>:>
        $<$<CONFIG:RelWithDebInfo>:LOGGING>
        $<$<CONFIG:MinSizeRel>:>
        )

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(main PRIVATE /Zc:preprocessor)
endif()
