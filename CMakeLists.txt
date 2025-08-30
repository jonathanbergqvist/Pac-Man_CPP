# CMakeList.txt : CMake project for Pac-Man_CPP, include source and define project specific logic here.

cmake_minimum_required (VERSION 3.16)

project ("Pac-Man_CPP")

set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (Pac-Man_CPP "src/Main.cpp" "src/Main.h" "src/GameLogic.cpp" "src/GameLogic.h" "src/Pacman.cpp" "src/Pacman.h" "src/Ghost.cpp" "src/Ghost.h" "src/GUI.cpp" "src/GUI.h" "src/TextureHandler.h" "src/TextureHandler.cpp")

target_link_libraries(Pac-Man_CPP PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)

# Add the Images folder to the Cmake build folder
file(COPY ${CMAKE_SOURCE_DIR}/Images DESTINATION ${CMAKE_BINARY_DIR})