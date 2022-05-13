/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:47:26 by yeju              #+#    #+#             */
/*   Updated: 2022/05/13 17:47:53 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	init_win_img(t_info *info)
{
	char	*map;
	int		init_img_ret;

	map = read_map(info->map->map_name, info);
	if (!map)
		return (0);
	info->map->world_map = save_map(map, info);
	if (!info->map->world_map)
		return (0);
	info->win = mlx_new_window(info->mlx, info->win_wid, \
		info->win_hei, "cub3D");
	if (!info->win)
		return (0);
	init_img_ret = init_img(info, info->win_wid, info->win_hei);
	if (!init_img_ret)
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

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		exit(1);
	utils_bzero(info, sizeof(t_info));
	info->mlx = mlx_init();
	if (!info->mlx)
		return (0);
	info->win_wid = 640;
	info->win_hei = 480;
	return (info);
}
