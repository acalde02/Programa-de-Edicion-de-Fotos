cmake_minimum_required(VERSION 3.10)
project(TrabajoFinal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluye carpeta de headers si están separados
include_directories(src)
include_directories(src/stb)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/Image.cpp
    src/Pixel.cpp
)

# Ejecutable final
add_executable(proyecto_final ${SOURCES})

# Enlaza filesystem si hace falta (algunos GCC lo requieren explícitamente)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(proyecto_final stdc++fs)
endif()
