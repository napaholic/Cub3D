#include "../inc/Cub3D.h"

void    init_DDA_cast(t_wallData *wData, t_info *info)
{
	if (wData->rayDirX < 0)
	{
		wData->stepX = -1;
		wData->sideDistX = (info->pos->posX - wData->map_posX);
	}
	else
	{
		wData->stepX = 1;
		wData->sideDistX = (wData->map_posX + 1.0 - info->pos->posX)
				* wData->d_DistX;
	}
	if (wData->rayDirY < 0)
	{
		wData->stepY = -1;
		wData->sideDistY = (info->pos->posY - wData->map_posY);
	}
	else
	{
		wData->stepY = 1;
		wData->sideDistY = (wData->map_posY + 1.0 - info->pos->posY)
				* wData->d_DistY;
	}
}

void    stepProgress_until_hit(t_wallData *wData, t_info *info)//벽에 맞을때까지 sideDist 증가. sideDist 가 나중에 perpWallDist 에 사용됨.
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (wData->sideDistX < wData->sideDistY)
		{
			wData->sideDistX += wData->d_DistX;
			wData->map_posX += wData->stepX;
			wData->side = 0;
		}
		else
		{
			wData->sideDistY += wData->d_DistY;
			wData->map_posY += wData->stepY;
			wData->side = 1;
		}
		if (info->map->world_map[wData->map_posX][wData->map_posY] > 0)
			hit = 1;
	}
}

double  calc_perp_dist(t_wallData *wData, t_info *info)
{
	double  perp_dist;

	if (wData->side)
		perp_dist = (wData->map_posY - info->pos->posY + (1 - wData->stepY) / 2)
				/ wData->rayDirY;
	else
		perp_dist = (wData->map_posX - info->pos->posX + (1 - wData->stepX) / 2)
				/ wData->rayDirX;
	return (perp_dist);
}

void    set_DDA(t_wallData *wData, t_info *info, int cur_x)
{
	wData->camera_x = 2 * cur_x / (double)width - 1; //카메라공간 x좌표계
	wData->rayDirX = info->pos->dirX + info->pos->planeX * wData->camera_x;
	wData->rayDirY = info->pos->dirY + info->pos->planeY * wData->camera_x;
	wData->map_posX = (int)info->pos->posX;
	wData->map_posY = (int)info->pos->posY;
	wData->d_DistX = fabs(1 / wData->rayDirX);
	wData->d_DistY = fabs(1 / wData->rayDirY);
	wData->map_posX = (int)(info->pos->posX);
	wData->map_posY = (int)(info->pos->posY);
	init_DDA_cast(wData, info);
	stepProgress_until_hit(wData, info);
	wData->perp_wall_dist = calc_perp_dist(wData, info);
}

void    wall_cast(t_info *info)
{
	t_wallData wData;
	int x;
	int y;

	x = -1;
	while (++x < width)
	{
		//1. set_DDA
		set_DDA(&wData, info, x);
		//2. wall_DistCast
		set_wall_data(&wData, info);
		//3. wall_set_texture_data
		set_texture_data(&wData, info);
		y = wData.draw_start - 1;
		while(++y < wData.draw_end)
			info->buf[y][x] = set_color(&wData, info);
	}
}