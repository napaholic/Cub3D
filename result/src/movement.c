#include "../inc/Cub3D.h"

int     empty_chk_map(t_map *map, int x, int y)
{
	if (map->world_map[x][y] == 0)
		return 0;
	return 1;
}

void    rotate_left(t_info *info)
{
	double oldDirX = info->dirX;
	info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
	info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
	double oldPlaneX = info->planeX;
	info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
	info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
}

void    rotate_right(t_info *info)
{
	double oldDirX = info->dirX;
	info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
	info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
	double oldPlaneX = info->planeX;
	info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
	info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
}

void    key_update(t_info *info)
{
	if (info->key->up)
	{
		if (!empty_chk_map(info->map, (int)(info->posX + info->dirX * info->moveSpeed),
		                  (int)(info->posY)))
		info->posX += info->dirX * info->moveSpeed;
		if (!empty_chk_map(info->map, (int)(info->posX),
		                   (int)(info->posY + info->dirY * info->moveSpeed)))
			info->posY += info->dirY * info->moveSpeed;
	}
	if (info->key->down)
	{
		if (!empty_chk_map(info->map, (int)(info->posX - info->dirX * info->moveSpeed),
		                   (int)(info->posY)))
			info->posX -= info->dirX * info->moveSpeed;
		if (!empty_chk_map(info->map, (int)(info->posX),
		                   (int)(info->posY - info->dirY * info->moveSpeed)))
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (info->key->left)
		rotate_left(info);
	if (info->key->right)
		rotate_right(info);
	if (info->key->esc)
	{
		//exit process, need free all allocate var
	}
}