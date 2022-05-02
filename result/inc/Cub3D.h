/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:28:46 by yeju              #+#    #+#             */
/*   Updated: 2022/05/02 21:22:24 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* include headers */
#include "../mlx/mlx.h"
#include "../gnl/get_next_line.h"
#include <math.h>
#include <fcntl.h> //file open

/*일단추가한헤더...*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <string.h>

/* mlx */
# define X_KEY_PRESS 2
# define X_KEY_RELEASE 3
# define X_KEY_EXIT	17

/* key */
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

/* display */
#define width 640
#define height 480

/*일단 추가한 고정길이... -> 직접 재는걸로 변경 필요~*/
// #define texWidth 64
// #define texHeight 64
// #define mapWidth 24
// #define mapHeight 24

/* image struct */
typedef struct	s_img
{
	void	*img;
	int		*data;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

/* mlx struct */
typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct	s_map
{
	char *line_map;
	char **world_map;
	unsigned int mapWidth;
	unsigned int mapHeight;
}				t_map;

/* main struct */
typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double	moveSpeed;
	double	rotSpeed;
	int		buf[height][width];
	int		**texture;
	// bool	key_chk[4] = {0, };
	
	t_mlx	*mlx;
	t_img	*img;
	t_map	*map;


}				t_info;

/* Cub3D.c */
// int **save_int(char **map);

/* init_map.c */
void init_map(t_info *info);
void get_map_size(t_info *info);
char	**read_world_map(char *argv);
 char	*read_line_map(char *argv);

/* utils */
int	ft_strlen(char *str);
void	error_exit(char *str);

# endif