cmake_minimum_required(VERSION 3.10)
project(LaboSpring2025)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-g -pg -Wall -Wextra -fanalyzer -O3 -march=native -ffast-math -funroll-loops -flto -DNDEBUG")


set(SIMULATION_SOURCES
    Cellule.cxx
    Particule.cxx
    Univers.cxx
    Vecteur.cxx
)

set(CONDITIONS_SOURCES
    conditionsLimites/Reflexion.cxx
    conditionsLimites/Absorption.cxx
    conditionsLimites/Periodique.cxx
    conditionsLimites/ReflexionPotentiel.cxx
)

add_library(simulation ${SIMULATION_SOURCES} ${CONDITIONS_SOURCES})
target_include_directories(simulation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(mainLab2 mainLab2.cxx)
target_link_libraries(mainLab2 simulation)

add_executable(mainLab4 mainLab4.cxx)
target_link_libraries(mainLab4 simulation)


add_executable(comparaisonPerf comparaisonPerf.cxx)
target_link_libraries(comparaisonPerf simulation)

add_executable(mainLab3 mainLab3.cxx)
target_link_libraries(mainLab3 simulation)

add_executable(InteractionPerf InteractionPerf.cxx)
target_link_libraries(InteractionPerf simulation)


add_executable(mainLab6 mainLab6.cxx)
target_link_libraries(mainLab6 simulation)