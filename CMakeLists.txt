cmake_minimum_required(VERSION 3.26)
project(PIA_terrain)

set(CMAKE_CXX_STANDARD 23)

add_executable(PIA_terrain main.cpp
        path/Path.cpp
        structures/TerrainMap.cpp
        structures/Point.cpp
        structures/Point.h
        path/PlanePath.h
        path/PlanePath.cpp
        path/CarPath.h
        path/CarPath.cpp
        path/BoatPath.cpp
        path/BoatPath.h
        path/SurfacePath.cpp
        path/SurfacePath.h
        path/TrainPath.cpp
        path/TrainPath.h)
