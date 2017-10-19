cmake_minimum_required (VERSION 2.8)
project (PokemonGymScanPoint)

#version number
set (PokemonGymScanPoint_VERSION_MAJOR 1)
set (PokemonGymScanPoint_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 11)

#indicate the entry point for the executable
add_executable (PokemonGymScanPoint ScanMain.cpp)
add_executable (PokemonGymScanAll ScanAll.cpp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -ggdb -O2")

install (TARGETS PokemonGymScanPoint PokemonGymScanAll DESTINATION bin)
