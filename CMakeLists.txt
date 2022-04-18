cmake_minimum_required(VERSION 2.8)
project(test_opengl)

# set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")

# include_directories(/usr/local/include
#                     /usr/local/Cellar/glew/2.2.0_1/include/ 
#                     /usr/local/Cellar/glfw/3.3.7/include/
#                     /usr/local/Cellar/glm/0.9.9.8/include/)
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
set(GLFW_H /usr/local/Cellar/glfw/3.3.7/include)
include_directories(${GLEW_H} ${GLFW_H})

# glfw和glew的头文件目录，这是我的路径，你可以换成你自己的
# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.7/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

aux_source_directory("./" SRCS)

add_executable(test_opengl ${SRCS} ${HDRS})

target_link_libraries(test_opengl "-framework OpenGL")
target_link_libraries(test_opengl "-framework GLUT")