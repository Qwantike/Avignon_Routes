# Version minimale requise de CMake
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(ColdWallet)

# Spécification du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Inclure les répertoires nécessaires
include_directories(
    ${CMAKE_SOURCE_DIR}/libs/json-develop/single_include  # Bibliothèque JSON
    ${CMAKE_SOURCE_DIR}/include                           # Répertoire des fichiers d'en-tête de ton projet
)

# Ajouter les fichiers source à compiler
set(SOURCES
    src/main.cpp
    src/rawToJson.cpp
    src/arc.cpp
    src/node.cpp
    src/gestionnaireRue.cpp
    src/listeArc.cpp
    src/ensembleArc.cpp
    src/ensembleNode.cpp
    src/graphe.cpp
    src/tris.cpp
    src/pile.cpp
    src/maillon.cpp
    src/file.cpp
)

# Créer l'exécutable à partir des fichiers sources
add_executable(Routes_Avignon ${SOURCES})
