/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/05 13:23:20 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	render(t_info *info)
{
	key_update(info);
	return (0);
}

void    hook_set(t_info *info)
{
	mlx_hook(info->mlx->winptr, X_KEY_PRESS, 0, &key_press, info);
	mlx_hook(info->mlx->winptr, X_KEY_RELEASE, 0, &key_release, info);
	mlx_hook(info->mlx->winptr, X_CLICK_EXIT, 0, &close_win, 0);
}



void    engine_set(t_info *info)
{
	hook_set(info);
}
