/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:19:46 by yeju              #+#    #+#             */
/*   Updated: 2022/05/05 13:19:59 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	read_map_path(char *line, char fir, char sec, t_info *info)
{
	(void)line;
	(void)info;
	if(fir == 'N')
		if (sec == 'O')
			return (2);
			//set tileset NO (info, line)
	if(fir == 'W')
		if (sec == 'E')
			return (2);
			//set tileset NO (info, line)
	if(fir == 'E')
		if (sec == 'A')
			return (2);
			//set tileset NO (info, line)
	if(fir == 'S')
		if (sec == 'O')
			return (2);
			//set tileset NO (info, line)
	//error return (3)
	return (2);
}

int	read_map_color(char *line, char fc, t_info *info)
{
	(void)line;
	(void)info;
	if(fc == 'F')
		return (1);
		//set floor color
	if(fc == 'C')
		return (1);
		//set floor color
	//error return (3)
	return (1);
}

int	read_map_setting(char *line, int i, t_info *info)
{
	int first;
	int second;
	int rst;

	if (line[i] && line[i + 1])
	{
		first = line[i];
		second = line[i + 1];
	}
	else
		return (3);
	if (first == 'N' || first == 'W' || first == 'E' || first == 'S')
		rst = read_map_path(line, line[i], line[i + 1], info);
	else if (first == 'F' || first == 'C')
		rst = read_map_color(line, line[i], info);
	else
		return (3);
	return (rst);
}