/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:59:50 by yeju              #+#    #+#             */
/*   Updated: 2022/05/10 16:45:11 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	player_move_front(t_info *info)
{
	double	mvx;
	double	mvy;

	mvx = info->pos->dir_x * info->pos->move_speed;
	mvy = info->pos->dir_y * info->pos->move_speed;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
}

void	player_move_back(t_info *info)
{
	double	mvx;
	double	mvy;

	mvx = -1 * info->pos->dir_x * info->pos->move_speed;
	mvy = -1 * info->pos->dir_y * info->pos->move_speed;
	if (info->map->world_map[(int)info->pos->pos_y][(int)(info->pos->pos_x + mvx)] == '0')
	{
		info->pos->pos_x += mvx;
	}
	if (info->map->world_map[(int)(info->pos->pos_y + mvy)][(int)info->pos->pos_x] == '0')
	{
		info->pos->pos_y += mvy;
	}
}

void	rotate_left(t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->pos->dir_x;
	info->pos->dir_x = info->pos->dir_x * cos(info->pos->rot_speed) - info->pos->dir_y * sin(info->pos->rot_speed);
	info->pos->dir_y = old_dir_x * sin(info->pos->rot_speed) + info->pos->dir_y * cos(info->pos->rot_speed);
	old_plane_x = info->pos->plane_x;
	info->pos->plane_x = info->pos->plane_x * cos(info->pos->rot_speed) - info->pos->plane_y * sin(info->pos->rot_speed);
	info->pos->plane_y = old_plane_x * sin(info->pos->rot_speed) + info->pos->plane_y * cos(info->pos->rot_speed);
}

void	rotate_right(t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = info->pos->dir_x;
	info->pos->dir_x = info->pos->dir_x * cos(-info->pos->rot_speed) - info->pos->dir_y * sin(-info->pos->rot_speed);
	info->pos->dir_y = old_dir_x * sin(-info->pos->rot_speed) + info->pos->dir_y * cos(-info->pos->rot_speed);
	old_plane_x = info->pos->plane_x;
	info->pos->plane_x = info->pos->plane_x * cos(-info->pos->rot_speed) - info->pos->plane_y * sin(-info->pos->rot_speed);
	info->pos->plane_y = old_plane_x * sin(-info->pos->rot_speed) + info->pos->plane_y * cos(-info->pos->rot_speed);
}

int	key_update(t_info *info)
{
	if (info->key->w == 1)
		player_move_front(info);
	if (info->key->a == 1)
	//	player_move_left(info);
	if (info->key->s == 1)
		player_move_back(info);
	if (info->key->d == 1)
	//	player_move_right(info);
	if (info->key->left == 1)
		rotate_left(info);
	if (info->key->right == 1)
		rotate_right(info);
	if (info->key->e == 1)
		rotate_mouse(info);
	return (1);
}
