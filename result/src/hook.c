/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:31:53 by yeju              #+#    #+#             */
/*   Updated: 2022/05/10 13:32:18 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void    hook_set(t_info *info)
{
	mlx_hook(info->win, X_KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win, X_KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win, X_CLICK_EXIT, 0, close_win, info);
	mlx_loop_hook(info->mlx, /*loop함수*/, info);
	mlx_loop(info->mlx);
}
