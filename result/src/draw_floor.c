#include "../inc/Cub3D.h"

void    render_floor(t_floordata *floor, t_info *info, int cur_x, int cur_y)
{
	int color;

	color = info->txt[floor->floorTexture][info->txt[floor->floorTexture]->img_width * floor->dX + floor->dY];
	color = (color >> 1) & 8355711;
	info->buf[cur_y][cur_x] = color;
	color = info->txt[floor->floorTexture][info->txt[floor->floorTexture]->img_height * floor->dX + floor->dY];
	color = (color >> 1) & 8355711;
	info->buf[height - cur_y - 1][cur_x] = color;
}