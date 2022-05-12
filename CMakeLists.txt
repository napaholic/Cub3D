cmake_minimum_required(VERSION 3.22)
project(Cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(mlx_example)
include_directories(mlx_example/mlx)
include_directories(result/gnl)
include_directories(result/inc)
include_directories(result/mlx)

add_executable(Cub3D
        result/inc/Cub3D.h
        result/src/Cub3D.c
        result/src/init.c
        result/src/engine.c
        result/src/movement.c
        result/src/engine_run.c
        result/src/calculate_floor.c
        result/src/draw_floor.c
        result/src/calculate_wall.c
        result/src/map_parse.c
        result/src/map_setting.c
        result/src/utils.c
        result/src/wall_cast.c
        result/src/load_texture.c
        result/src/parse.c)
