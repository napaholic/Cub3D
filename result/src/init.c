/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:17:02 by yeju              #+#    #+#             */
/*   Updated: 2022/05/05 13:24:41 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	init_mlx(t_info *info)
{
	info->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!info->mlx)
		return (0);
	utils_bzero(info->mlx, sizeof(t_mlx));
	return (1);
}

int	init_key(t_info *info)
{
	info->key = (t_key *)malloc(sizeof(t_key));
	if (!info->key)
		return (0);
	utils_bzero(info->key, sizeof(t_key));
	info->key->left = 0;
	info->key->right = 0;
	info->key->down = 0;
	info->key->up = 0;
	return (1);
}

int	init_map(t_info *info)
{
	info->map = (t_map *)malloc(sizeof(t_map));
	if (!(info->map))
		return (0);
	utils_bzero(info->map, sizeof(t_map));
	info->map->mapWidth = 0;
	info->map->mapHeight = 0;
	return (1);
}

void	init_info(t_info *info)
{
	set_info_pos(info);
	init_map(info);
	init_mlx(info);
	init_key(info);
	return ;
}
