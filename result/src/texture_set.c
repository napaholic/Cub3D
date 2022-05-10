/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:19:46 by yeju              #+#    #+#             */
/*   Updated: 2022/05/10 16:32:28 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	read_map_path(char *line, char fir, char sec, t_info *info)
{
	(void)line;
	char *path = NULL;
	//잘못된 path 체크하기 (안들어왔다거나 파일이 없다거나)
	if (fir == 'N' && sec == 'O')
		return (texture_set(info, path, TEX_WALL_N)); //0
	if (fir == 'W' && sec == 'E')
		return (texture_set(info, path, TEX_WALL_W)); //3
	if (fir == 'E' && sec == 'A')
		return (texture_set(info, path, TEX_WALL_E)); //2
	if (fir == 'S' && sec == 'O')
		return (texture_set(info, path, TEX_WALL_S)); //1
	else
		return (0);
}

int	texture_set(t_info *info, char *path, int idx)
{
	if (!(info->txt[idx]->img = mlx_xpm_file_to_image(info->mlx, path, \
		&info->txt[idx]->img_width, &info->txt[idx]->img_height)))
		return (0);
	info->txt[idx]->data = mlx_get_data_addr(info->txt[idx]->img, \
		&info->txt[idx]->bits_per_pixel, &info->txt[idx]->size_line, &info->txt[idx]->endian);
	free(path);
	return (1);
}

int	read_map_color(char *line, char fc, t_info *info)
{
	(void)line;
	(void)info;
	if (fc == 'F')
		return (1);
		//set floor color
	if (fc == 'C')
		return (1);
		//set floor color
	//error return (3)
	return (1);
}