
cmake_minimum_required(VERSION 3.12)

project(ProgramaOpengl1)

add_executable(ProgramaOpengl1 
                src/main.cpp)

target_include_directories(ProgramaOpengl1 PRIVATE 
                                              deps/glm 
                                              deps/glfw/include
                                              deps/glew/include
                                              deps/assimp/include)

target_link_directories(ProgramaOpengl1 PRIVATE
                                           deps/glfw/lib-vc2019
                                           deps/glew/lib/Release/x64
                                           deps/assimp/lib)

target_link_libraries(ProgramaOpengl1 PRIVATE glfw3.lib glew32.lib opengl32.lib assimp-vc143-mt.lib)

add_custom_command(TARGET ProgramaOpengl1 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/glew/bin/Release/x64/glew32.dll" "${CMAKE_BINARY_DIR}/glew32.dll")

add_custom_command(TARGET ProgramaOpengl1 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/assimp/bin/assimp-vc143-mt.dll" "${CMAKE_BINARY_DIR}/assimp-vc143-mt.dll")

add_custom_command(TARGET ProgramaOpengl1 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/assimp/bin/poly2tri.dll" "${CMAKE_BINARY_DIR}/poly2tri.dll")

add_custom_command(TARGET ProgramaOpengl1 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/assimp/bin/minizip.dll" "${CMAKE_BINARY_DIR}/minizip.dll")

add_custom_command(TARGET ProgramaOpengl1 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/assimp/bin/pugixml.dll" "${CMAKE_BINARY_DIR}/pugixml.dll")

add_custom_command(TARGET ProgramaOpengl1 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/assimp/bin/zlib1.dll" "${CMAKE_BINARY_DIR}/zlib1.dll")

add_custom_command(TARGET ProgramaOpengl1 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/assimp/bin/draco.dll" "${CMAKE_BINARY_DIR}/draco.dll")


