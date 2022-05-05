/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:52:04 by yeju              #+#    #+#             */
/*   Updated: 2022/05/05 13:17:20 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	set_pos(t_info *info)
{
	int	wid;
	int	hei;

	wid = -1;
	while (++wid < info->map->mapHeight)
	{
		hei = -1;
		while (++hei < info->map->mapWidth)
		{
			if (info->map->world_map[wid][hei] == 'N')
			{
				info->pos->posX = (double)hei;
				info->pos->posY = (double)wid;
			}
		}
	}
	if (info->pos->posX == -1.0 && info->pos->posY == -1.0)
		printf("pos세팅안됨\n");
	//test code
	// printf("posX: %f\n", info->posX);
	// printf("posY: %f\n", info->posY);
}

void	set_info_pos(t_info *info)
{
	info->pos->dirX = -1.0;
	info->pos->dirY = 0.0;
	info->pos->planeX = 0.0;
	info->pos->planeY = 0.66;
	info->pos->moveSpeed = 0.05;
	info->pos->rotSpeed = 0.05;
	return ;
}

void	set_data(t_info *info)
{
	(void)info;
}

void	load_texture(t_info *info)
{
	(void)info;
	//texture 구성
}
