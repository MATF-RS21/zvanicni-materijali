cmake_minimum_required(VERSION 3.10)
project(app)

include_directories(thirdparty/include/)
include_directories(include/)

add_subdirectory(resources/)
add_subdirectory(thirdparty/)

set(APP_INCLUDES include/FileNotFoundException.h 
                 include/Image.h)

set(APP_SOURCES  src/app.cpp
                 src/FileNotFoundException.cpp
                 src/Image.cpp)

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${APP_INCLUDES})

target_link_libraries(${PROJECT_NAME} stb_image)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (UNIX AND NOT APPLE)
	set(CMAKE_CXX_STANDARD_LIBRARIES "-std=c++17 -lstdc++fs")
endif()

install (TARGETS ${PROJECT_NAME} DESTINATION bin)
