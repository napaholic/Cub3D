/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:31:53 by yeju              #+#    #+#             */
/*   Updated: 2022/05/11 12:52:35 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void    cal_vec(t_info *info)
{
	floor_cast(info);
	wall_cast(info);
	return ;
}


int	raycasting(t_info *info)
{
	cal_vec(info);
	draw(info);
	(void)info;
	return 1;
}

int	render(t_info *info)
{
	if (!raycasting(info)) //cal, draw
		exit(1);
	key_update(info);
	return (0);
}

void	hook_set(t_info *info)
{
	mlx_hook(info->win, X_KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win, X_KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win, X_CLICK_EXIT, 0, close_win, info);
	mlx_loop_hook(info->mlx, render, info);
	mlx_loop(info->mlx);
}
