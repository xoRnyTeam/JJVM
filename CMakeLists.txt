cmake_minimum_required(VERSION 3.10)


project(jjvm)

set(JJVM_EXEC jjvm)
add_executable(${JJVM_EXEC} 
                main.cpp
                src/memory.cpp
                src/jjvm_class_parser.cpp
                src/instractions.cpp)
target_include_directories(${JJVM_EXEC} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)