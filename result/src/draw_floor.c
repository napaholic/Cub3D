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

void    draw(t_info *info)
{
	int y;
	int x;

	y = -1;
	while (++y < info->win_hei)
	{
		x = -1;
		while (++x < info->win_wid)
			info->img->data[y * width + x] = info->buf[y][x];
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
}