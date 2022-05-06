cmake_minimum_required(VERSION 3.22)
project(Cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(mlx_example)
include_directories(mlx_example/mlx)
include_directories(result/gnl)
include_directories(result/inc)
include_directories(result/mlx)

add_executable(Cub3D
        result/gnl/get_next_line.c
        result/gnl/get_next_line.h
        result/gnl/get_next_line_utils.c
        result/inc/Cub3D.h
        result/mlx/font.c
        result/mlx/mlx.h
        result/mlx/mlx_init_loop.m
        result/mlx/mlx_int.h
        result/mlx/mlx_int_str_to_wordtab.c
        result/mlx/mlx_mouse.m
        result/mlx/mlx_new_image.m
        result/mlx/mlx_new_window.h
        result/mlx/mlx_new_window.m
        result/mlx/mlx_opengl.h
        result/mlx/mlx_opengl.m
        result/mlx/mlx_png.c
        result/mlx/mlx_png.h
        result/mlx/mlx_rgb.c
        result/mlx/mlx_shaders.c
        result/mlx/mlx_xpm.c
        result/src/Cub3D.c
        result/src/init.c
        result/src/engine.c
        result/src/movement.c
        result/src/engine_run.c
        result/src/calculate_floor.c
        result/src/draw_floor.c
        result/src/calculate_ceil.c
        result/src/map_parse.c
        result/src/map_setting.c
        result/src/utils.c
        result/src/parse.c)
