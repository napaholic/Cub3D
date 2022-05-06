#include "../inc/Cub3D.h"
// floor
//color = info->texture[floorTexture][texWidth * ty + tx];
//color = (color >> 1) & 8355711; // make a bit darker
//info->buf[y][x] = color;
////ceiling (symmetrical, at height - y - 1 instead of y)
//color = info->texture[ceilingTexture][texWidth * ty + tx];
//color = (color >> 1) & 8355711; // make a bit darker
//info->buf[height - y - 1][x] = color;
void    render_floor(t_floordata *floor, t_info *info, int cur_x, int cur_y)
{
	int color;

	color = info->texture[floor->floorTexture][texWidth * floor->dX + floor->dY];
	color = (color >> 1) & 8355711;
	info->buf[y][x] = color;
	color = info->texture[floor->floorTexture][texHeight * ty + tx];
	color = (color >> 1) & 8355711;
	info->buf[height - cur_y - 1][cur_x] = color;
}