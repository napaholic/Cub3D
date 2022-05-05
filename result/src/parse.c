#include "../inc/Cub3D.h"

void set_info_pos(t_info *info)
{
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	return ;
}

void init_info(t_info *info)
{
	set_info_pos(info);
	init_map(info);
	init_mlx(info);
	init_key(info);
	return ;
}

void set_data(t_info *info)
{
	(void)info;
}

void load_texture(t_info *info)
{
	(void)info;
	//texture 구성
}