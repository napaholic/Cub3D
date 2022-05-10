#include "../inc/Cub3D.h"

void    set_raydir(t_floordata *floor, t_info *info, int y)
{
	floor->ray_dir_x0 = info->pos->dir_x - info->pos->plane_x;
	floor->ray_dir_y0 = info->pos->dir_y - info->pos->plane_y;
	floor->ray_dir_x1 = info->pos->dir_x + info->pos->plane_x;
	floor->ray_dir_y1 = info->pos->dir_y + info->pos->plane_y;
	floor->row_distance = (0.5 * height) / (y - height / 2);
}

void    set_floor_vec(t_floordata *floor, t_info *info)
{
	floor->floor_stepX = floor->row_distance
			*(floor->ray_dir_x1 - floor->ray_dir_x0) / width;
	floor->floor_stepY = floor->row_distance
			* (floor->ray_dir_y1 - floor->ray_dir_y0) / width;
	floor->floorX = info->pos->posX + floor->row_distance * floor->ray_dir_x0;
	floor->floorY = info->pos->posY + floor->row_distance * floor->ray_dir_y0;
}

void    set_texture_vec(t_floordata *floor)
{
	floor->cellX = (int)(floor->floorX);
	floor->cellY = (int)(floor->floorY);
	floor->dX = (int)(texWidth * (floor->floorX - floor->cellX)) & (texWidth - 1);
	floor->dY = (int)(texWidth * (floor->floorY - floor->cellY)) & (texHeight - 1);
	floor->floorX += floor->floor_stepX;
	floor->floorY += floor->floor_stepY;
}

void    set_texture_num(t_floordata *floor)
{
	int    tile_define = ((int)floor->floorX + (int)floor->floorY) % 2;

	floor->ceiling_texture = texture_ceil;
	if (tile_define)
		floor->floorTexture = floor_tex1;
	else
		floor->floorTexture = floor_tex2;
}

void    floor_cast(t_info *info) {
	t_floordata f_data;
	int x;
	int y;

	y = height / 2 - 1;
	while (++y < height) {

		set_raydir(&f_data, info, y);
		set_floor_vec(&f_data, info);
		x = -1;
		while (++x < width)
		{
			set_texture_vec(&f_data);
			set_texture_num(&f_data);
			render_floor(&f_data, info, x, y);
		}
	}
}



