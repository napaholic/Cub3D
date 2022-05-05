#include "../inc/Cub3D.h"
/*
//FLOOR CASTING
	for(int y = height / 2 + 1; y < height; ++y)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->dirX - info->planeX;
		float rayDirY0 = info->dirY - info->planeY;
		float rayDirX1 = info->dirX + info->planeX;
		float rayDirY1 = info->dirY + info->planeY;
		// Current y position compared to the center of the screen (the horizon)
		int p = y - height / 2;
		// Vertical position of the camera.
		float posZ = 0.5 * height;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;
		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / width;
		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->posX + rowDistance * rayDirX0;
		float floorY = info->posY + rowDistance * rayDirY0;
		for(int x = 0; x < width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);
			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
			floorX += floorStepX;
			floorY += floorStepY;
			// choose texture and draw the pixel
			int checkerBoardPattern = (int)(cellX + cellY) & 1;
			int floorTexture;
			if(checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;
			int ceilingTexture = 6;
			int color;
			// floor
			color = info->texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			info->buf[y][x] = color;
			//ceiling (symmetrical, at height - y - 1 instead of y)
			color = info->texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			info->buf[height - y - 1][x] = color;
		}
	}
 */

void    set_raydir(t_floordata *floor, t_info *info, int y)
{
	floor->ray_dirX0 = info->pos->dirX - info->pos->planeX;
	floor->ray_dirY0 = info->pos->dirY - info->pos->planeY;
	floor->ray_dirX1 = info->pos->dirX + info->pos->planeX;
	floor->ray_dirY1 = info->pos->dirY + info->pos->planeY;
	floor->row_distance = (0.5 * height) / (y - height / 2)
}

void    set_floor_vec(t_floordata *floor, t_info *info)
{
	floor->floor_stepX = floor->row_distance
			*(floor->ray_dirX1 - floor->ray_dirX0) / width;
	floor->floor_stepY = floor->row_distance
			* (floor->ray_dirY1 - floor->ray_dirY0) / width;
	floor->floorX = info->pos->posX + floor->row_distance * floor->ray_dirX0;
	floor->floorY = info->pos->posY + floor->row_distance * floor->ray_dirY0;
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
	int    tile_define = (int)floor->floorX % 2;

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
		//1. floor raycast set raydir
		//1. floor raycast set raydir
		//1. floor raycast set raydir
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



