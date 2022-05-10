/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:31:53 by yeju              #+#    #+#             */
/*   Updated: 2022/05/10 16:31:21 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	raycasting(t_info *info)
{
	(void)info;
	return 1;
}

int	loop(t_info *info)
{
	if (!raycasting(info))
		exit(1);
	key_update(info);
	return (0);
}

void    hook_set(t_info *info)
{
	mlx_hook(info->win, X_KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win, X_KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win, X_CLICK_EXIT, 0, close_win, info);
	mlx_loop_hook(info->mlx, loop, info);
	mlx_loop(info->mlx);
}
