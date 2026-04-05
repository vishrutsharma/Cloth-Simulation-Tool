cmake_minimum_required(VERSION 3.10)
project(VerletIntegration)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL2_DIR "C:/Vishrut/Paths/SDL2")

find_package(SDL2 REQUIRED CONFIG
    HINTS ${SDL2_DIR}/lib/cmake/SDL2
)

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(main ${SRC_FILES})

target_link_options(main PRIVATE -mconsole)

target_include_directories(main PUBLIC
    ${SDL2_DIR}/include
)


target_link_libraries(main PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
)


#cmake -S . -B build
#cmake --build build
#.\build\main.exe