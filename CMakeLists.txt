cmake_minimum_required(VERSION 3.20)
project(TP2_chargement_graphe_C C)

set(CMAKE_C_STANDARD 99)

add_executable(TP2_chargement_graphe_C Graphe.h main.c cellule.h fifo.c fifo.h)
