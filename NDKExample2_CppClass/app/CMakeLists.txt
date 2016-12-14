cmake_minimum_required(VERSION 3.4.1)


add_library(native-lib
            SHARED
            src/main/cpp/native-lib.cpp )

add_library(ShaderProgram
            SHARED
            src/main/cpp/ShaderProgram.cpp )

find_library(log-lib
            log )

target_link_libraries(native-lib
                  ShaderProgram
                  ${log-lib} )

target_link_libraries(ShaderProgram
                    GLESv2
                    ${log-lib} )
