cmake_minimum_required(VERSION 3.10)

project(jjvm)

set(CMAKE_INCL subdirs upd_list)
set(DIRS src)
set(JJVM_EXEC jjvm)

#
file(GLOB_RECURSE JVM_SRC src/**.cpp)

message("${JVM_SRC}")

add_executable(${JJVM_EXEC} ${JVM_SRC})
target_include_directories(${JJVM_EXEC} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
#
#
# foreach(DIR ${DIRS})
#     add_subdirectory(${DIR})
# endforeach()
# 
# set(TARGETS)
# list(APPEND TARGETS ${JJVM} ${JJVM_LIB})

# foreach(TARGET IN LISTS TARGETS)
#     target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/include/)
# #     target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/3rd_party)
# endforeach()
# 
# foreach(TARGET ${JJVM})
#     target_link_libraries(${TARGET} PUBLIC ${JJVM_LIB})
# endforeach()
# 
# add_executable(${JJVM_EXEC}
# vm/main.cpp
# vm/vm.cpp
# src/memory.cpp
# src/jjvm_class_parser.cpp
# src/instractions.cpp
# src/jjvm.cpp
# src/ClassFile.cpp
# src/jjvm_handlers.cpp)

# target_include_directories(${JJVM_EXEC} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)