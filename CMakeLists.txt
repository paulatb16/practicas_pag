cmake_minimum_required(VERSION 4.0)
project(P1)

set(CMAKE_CXX_STANDARD 20)

file( GLOB MY_FILES *.cpp ) # Código fuente de tu proyecto
file( GLOB GLAD_FILES GLAD/src/*.c ) # Código fuente de GLAD

add_executable( ${PROJECT_NAME} ${MY_FILES}
        ${GLAD_FILES} )
target_include_directories( ${PROJECT_NAME} PUBLIC GLAD/include )

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)


