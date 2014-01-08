# TODO: Figure out how to walk this back
cmake_minimum_required(VERSION 2.8)

project (Midnight)

if (WIN32)
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )
else (WIN32)
	list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall" )
endif(WIN32)

# GLFW
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
add_subdirectory(Libraries/glfw-3.0.3)
include_directories(Libraries/glfw-3.0.3/include)

# SOIL
add_subdirectory(Libraries/soil)
include_directories(Libraries/soil/src)

# Devkit
include_directories(Devkit)

# Project
set(${PROJECT_NAME}_SRC
	Code/main.cpp
)

set(${PROJECT_NAME}_INC
	Devkit/Debug.h
	Devkit/Graphics.h
	Devkit/Maths.h
	Devkit/Scene.h
	Devkit/System.h
	Devkit/Zync.h
)

file(GLOB_RECURSE ${PROJECT_NAME}_CODE "Code/*.h")

source_group ("Game" FILES ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_CODE})
source_group ("Zync" FILES ${${PROJECT_NAME}_INC})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build)

add_executable (${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_INC} ${${PROJECT_NAME}_CODE})

# Libraries
target_link_libraries(${PROJECT_NAME} glfw soil ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})