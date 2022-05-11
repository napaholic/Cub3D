/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:28:46 by yeju              #+#    #+#             */
/*   Updated: 2022/05/11 18:32:00 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* include headers */
#include "../mlx/mlx.h"
#include <math.h>
#include <fcntl.h>

/*일단추가한헤더...*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* mlx */
# define X_KEY_PRESS	2
# define X_KEY_RELEASE	3
# define X_CLICK_EXIT	17

/* key */
# define KEY_ESC		53
# define KEY_A			0
# define KEY_D			2
# define KEY_S			1
# define KEY_W			13
# define KEY_E			14
# define KEY_LEFT		123
# define KEY_RIGHT		124

/* texture */
# define TEX_WALL_N		0
# define TEX_WALL_S		1
# define TEX_WALL_E		2
# define TEX_WALL_W		3
# define TEX_FLOOR_1	4
# define TEX_FLOOR_2	5
# define TEX_CEILING	6

/* step_vector */
# define POSITIVE 1
# define NEGATIVE -1

/* image struct */
typedef struct	s_img
{
	void	*img;
	char	*data;
	int		img_width;
	int		img_height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*path;
}				t_img;

/* map struct */
typedef struct	s_map
{
	char	**world_map;
	char	*line_map; //-> 구조체에 안넣고 mapsize구한후 바로 free
	char	*map_name; //->map파일 권한때문에 일단 넣어둠
	int		map_width;
	int		map_height;
}				t_map;

/* key struct */
typedef struct	s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int e;//마우스 시점변환 토글
	int e_delay;//마우스 딜레이
	int	left;
	int	right;
}				t_key;

/* pos struct */
typedef struct	s_pos
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}				t_pos;

/* wall_data struct */
typedef struct	s_wall_data
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_pos_x;
	int		map_pos_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	d_dist_x;
	double	d_dist_y;
	int		side;
	double	perp_wall_dist;
	int		lineheight;
	int		draw_start;
	int		draw_end;
	double	wallx; //@
	int		texX; //@
	double	step_val; //@
	double	tex_pos; //@
	int		hit;
}				t_wall_data;

/* floor_data */
typedef struct	s_floordata
{
	float	ray_dir_x0;
	float	ray_dir_x1;
	float	ray_dir_y0;
	float	ray_dir_y1;
	float	row_distance;
	float	floor_stepX;
	float	floor_stepY;
	float	floorX;
	float	floorY;
	float	cellX;
	float	cellY;
	int		dX;
	int		dY;
	int		floorTexture;
	int		ceiling_texture;
}				t_floordata;


/* main struct */
typedef struct	s_info
{
	//mlx 구조체 여기로 이동
	void	*mlx;
	void	*win;

	//고정으로 바꿔도 되는 창 크기
	int		win_wid;
	int		win_hei;
	int buf[640][480];

	//바닥, 천장 색깔
	int		floor_color;
	int		ceiling_color;
	//텍스쳐 배열
	int     **texture;
	//구조체
	t_pos	*pos;
	t_key	*key;
	t_img	*img;
	t_img	**txt;
	t_map	*map;
}				t_info;

/* 일단 들고온 list
typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
*/

/* Cub3D.c */
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
int		close_win(int keycode, int x, int y, void *param);
void	check_leaks();

/* calc_floor, wall */
void	set_raydir(t_floordata *floor, t_info *info, int y);
void	set_texture_vec(t_floordata *floor, t_info *info);
void	set_texture_num(t_floordata *floor);
void	floor_cast(t_info *info);
void	init_DDA_cast(t_wall_data *wall_data, t_info *info);
void	stepProgress_until_hit(t_wall_data *wall_data, t_info *info);
double	calc_perp_dist(t_wall_data *wall_data, t_info *info);
void	set_DDA(t_wall_data *wall_data, t_info *info, int cur_x);
void	wall_cast(t_info *info);

/* draw_floor */
void    draw(t_info *info);

/* loop_hook.c */
void	hook_set(t_info *info);
int		render(t_info *info);
void	cal_vec(t_info *info);
void	render_floor(t_floordata *floor, t_info *info, int cur_x, int cur_y);
int		raycasting(t_info *info);

/* gnl */
size_t	utils_strlen(const char *s);
size_t	utils_strlcpy(char *dest, const char *src, size_t dstsize);
size_t	utils_strlcat(char *dest, const char *src, size_t dstsize);
char	*utils_strjoin(char *s1, char *s2);
char	*utils_strdup(const char *s1);
int		utils_strchr(char *string);
char	*utils_substr(char const *s, unsigned int start, size_t len);
int		utils_get_size(char *str, int idx);
int		gnl_split(char **string, char **line, int i);
int		gnl_return(char **string, char **line, int read_size);
int		get_next_line(int fd, char **line);

/* init_map.c */
// void	get_map_size(t_info *info);
// char	**read_world_map(char *argv);
// int		read_map_path(char *line, char fir, char sec, t_info *info);
// int		read_map_color(char *line, char fc, t_info *info);
// int		read_map_setting(char *line, int i, t_info *info);
// int		read_map(char *line, char **map, int i, int readed);
// char	*read_line_map(char *argv, t_info info);

/* init.c */
int		init_textures(t_info *info, int num);
int		init_map(t_info *info, char *map_name);
int		init_key(t_info *info);
int		init_player(t_info *info);
int		init_win_img(t_info *info);
int		init_info(t_info *info, char *argv);
t_info	*init_info_mlx(void);

/* map_parse.c */
char	*read_map(char *argv, t_info *info);
int	read_map_sub(char *line, char **map, t_info *info, int gnl_ret);
int		read_map_setting(char *line, int idx, t_info *info);
int		read_color(char *line, int c, int idx, t_info *info);
int		read_txt_path(char *line, int first, int second, int idx, t_info *info);
int	map_check(char *line, char **map, int idx, int gnl_ret);

int		utils_check_txt_execute(char *path);
int		utils_check_txt_path(char *line);
int	utils_check_color(char *line, int c, int idx);
int	texture_set(t_info *info, char *path, int idx);


/* texture_set.c */
int		read_map_path(char *line, char fir, char sec, t_info *info);
int		texture_set(t_info *info, char *pth, int idx);
int		read_map_color(char *line, char fc, t_info *info);

/* mov_cal.c */
int		empty_chk_map(t_map *map, int x, int y);
void	player_move_left(t_info *info);
void	player_move_right(t_info *info);

/* movement.c */
int		player_move_front(t_info *info);
int		player_move_back(t_info *info);
int		rotate_left(t_info *info);
int		rotate_right(t_info *info);
int		key_update(t_info *info);

/* utils */
int		utils_white_space(char c);
void	utils_bzero(void *s, size_t n);
int		utils_read_another(char *line, int i);
int		utils_read(char **map, char *line, t_info *info);
int		utils_isprint(int c);
int		utils_isdigit(int c);

/* wall_cast.c */
void	set_wall_data(t_wall_data *wall_data, t_info *info);
void	set_texture_data(t_wall_data *wall_data, t_info *info);
int		set_color(t_wall_data *wall_data, t_info *info);

/* loop_hook.c */
int		loop(t_info *info);
void	hook_set(t_info *info);

# endif