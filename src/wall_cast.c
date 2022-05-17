/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:09:23 by yeju              #+#    #+#             */
/*   Updated: 2022/05/14 19:13:39 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	set_wall_data(t_wall_data *wall_data, t_info *info)
{
	wall_data->lineheight = (int)(info->win_hei / wall_data->perp_wall_dist);
	wall_data->draw_start = -wall_data->lineheight / \
		2 + ((info->win_hei / 2) * wall_data->camera_x);
	if (wall_data->draw_start < 0)
		wall_data->draw_start = 0;
	wall_data->draw_end = wall_data->lineheight / \
		2 + ((info->win_hei / 2) * wall_data->camera_x);
	if (wall_data->draw_end >= info->win_hei)
		wall_data->draw_end = info->win_hei - 1;
	return ;
}
