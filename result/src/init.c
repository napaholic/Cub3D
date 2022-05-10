/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:17:02 by yeju              #+#    #+#             */
/*   Updated: 2022/05/10 16:06:38 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	init_textures(t_info *info, int num)
{
	int	idx;

	idx = 0;
	if (!(info->txt = (t_img **)malloc(sizeof(t_img *) * num - 1)))
		return (0);
	while (idx < num)
	{
		if (!(info->txt[idx] = (t_img *)malloc(sizeof(t_img) * 1)))
			return (0);
		utils_bzero(info->txt[idx], sizeof(t_img));
		++idx;
	}
	return (1);
}

int	init_map(t_info *info, char *map_name)
{
	if (!(info->map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	utils_bzero(info->map, sizeof(t_map));
	info->map->map_name = map_name;
	info->map->map_height = 0;
	info->map->map_width = 0;
	return (1);
}

int	init_key(t_info *info)
{
	if (!(info->key = (t_key *)malloc(sizeof(t_key))))
		return (0);
	utils_bzero(info->key, sizeof(t_key));
	info->key->w = 0;
	info->key->a = 0;
	info->key->s = 0;
	info->key->d = 0;
	info->key->left = 0;
	info->key->right = 0;
	return (1);
}

int	init_player(t_info *info)
{
	if (!(info->pos = (t_pos *)malloc(sizeof(t_pos))))
		return (0);
	utils_bzero(info->pos, sizeof(t_pos));
	info->pos->pos_x = -20.0;
	info->pos->pos_y = -20.0;
	info->pos->dir_x = 1.0;
	info->pos->dir_y = 0.0;
	info->pos->plane_x = -20.0;
	info->pos->plane_y = -20.0;
	info->pos->move_speed = 0.10;
	info->pos->rot_speed = 0.10;
	return (1);
}

int	init_win_img(t_info *info)
{
	char	*map;

	map = read_map(info->map->map_name, info);
	if (!map)
		return (0);
	// translate_map(map, info); //mapparse
	if (!(info->win = mlx_new_window(info->mlx, info->win_wid, info->win_hei, "cub3D")))
		return (0);
	if (!(info->img/*= image_new(info, info->win_wid, info->win_hei)*/))
		return (0);
	return (1);
}

int	init_info(t_info *info, char *argv)
{
	if (!init_textures(info, 4) || !init_map(info, argv) || \
	!init_key(info) || !init_player(info) || !init_win_img(info))
		return (0);
	return (1);
}

t_info	*init_info_mlx(void)
{
	t_info	*info;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		exit(1);
	utils_bzero(info, sizeof(t_info));
	info->mlx = mlx_init();
	if (!info->mlx)
		return (0);
	info->win_wid = 640;
	info->win_hei = 480;
	return (info);
}