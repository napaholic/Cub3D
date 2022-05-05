/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:59:50 by yeju              #+#    #+#             */
/*   Updated: 2022/05/05 13:03:29 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	empty_chk_map(t_map *map, int x, int y)
{
	if (map->world_map[x][y] == 0)
		return (0);
	return (1);
}

void	rotate_left(t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->pos->dirX;
	info->pos->dirX = info->pos->dirX * cos(info->pos->rotSpeed) - info->pos->dirY * sin(info->pos->rotSpeed);
	info->pos->dirY = old_dir_x * sin(info->pos->rotSpeed) + info->pos->dirY * cos(info->pos->rotSpeed);
	old_plane_x = info->pos->planeX;
	info->pos->planeX = info->pos->planeX * cos(info->pos->rotSpeed) - info->pos->planeY * sin(info->pos->rotSpeed);
	info->pos->planeY = old_plane_x * sin(info->pos->rotSpeed) + info->pos->planeY * cos(info->pos->rotSpeed);
}

void	rotate_right(t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->pos->dirX;
	info->pos->dirX = info->pos->dirX * cos(-info->pos->rotSpeed) - info->pos->dirY * sin(-info->pos->rotSpeed);
	info->pos->dirY = old_dir_x * sin(-info->pos->rotSpeed) + info->pos->dirY * cos(-info->pos->rotSpeed);
	old_plane_x = info->pos->planeX;
	info->pos->planeX = info->pos->planeX * cos(-info->pos->rotSpeed) - info->pos->planeY * sin(-info->pos->rotSpeed);
	info->pos->planeY = old_plane_x * sin(-info->pos->rotSpeed) + info->pos->planeY * cos(-info->pos->rotSpeed);
}

void	key_update(t_info *info)
{
	if (info->key->up)
	{
		if (!empty_chk_map(info->map, (int)(info->pos->posX + info->pos->dirX * info->pos->moveSpeed), (int)(info->pos->posY)))
		info->pos->posX += info->pos->dirX * info->pos->moveSpeed;
		if (!empty_chk_map(info->map, (int)(info->pos->posX), (int)(info->pos->posY + info->pos->dirY * info->pos->moveSpeed)))
			info->pos->posY += info->pos->dirY * info->pos->moveSpeed;
	}
	if (info->key->down)
	{
		if (!empty_chk_map(info->map, (int)(info->pos->posX - info->pos->dirX * info->pos->moveSpeed), (int)(info->pos->posY)))
			info->pos->posX -= info->pos->dirX * info->pos->moveSpeed;
		if (!empty_chk_map(info->map, (int)(info->pos->posX), (int)(info->pos->posY - info->pos->dirY * info->pos->moveSpeed)))
			info->pos->posY -= info->pos->dirY * info->pos->moveSpeed;
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
