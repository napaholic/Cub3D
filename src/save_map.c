/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:07:07 by yeju              #+#    #+#             */
/*   Updated: 2022/05/17 19:11:21 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	save_map_get_width(int hei, char *line_map, t_info *info)
{
	int	i;
	int	wid;
	int	wid2;

	i = 0;
	wid = 0;
	wid2 = 0;
	while (hei--)
	{
		info->map->map_width = wid2;
		wid = 0;
		while (line_map[i++] != '\n')
			wid++;
		if (wid2 < wid)
			wid2 = wid;
	}
	return ;
}

void	save_map_get_size(char *line_map, t_info *info)
{
	int	i;
	int	hei;

	i = 0;
	hei = 0;
	while (line_map[i] != '\0')
	{
		if (line_map[i] == '\n')
			++hei;
		i++;
	}
	info->map->map_height = hei;
	save_map_get_width(hei, line_map, info);
	return ;
}

void	set_pos(char **world_map, t_info *info)
{
	int	wid;
	int	hei;
	int	flag;

	flag = 0;
	hei = 0;
	while (hei < info->map->map_height)
	{
		wid = 0;
		while (wid < info->map->map_width)
		{
			if (world_map[hei][wid] == 'N' || world_map[hei][wid] == 'W' || \
				world_map[hei][wid] == 'E' || world_map[hei][wid] == 'S')
			{
				flag += 1;
				info->pos->pos_x = (double)wid;
				info->pos->pos_y = (double)hei;
			}
			if (world_map[hei][wid] == 'N')
				get_direction(info, world_map, hei, wid);
			else if (world_map[hei][wid] == 'W')
				get_direction(info, world_map, hei, wid);
			else if (world_map[hei][wid] == 'E')
				get_direction(info, world_map, hei, wid);
			else if (world_map[hei][wid] == 'S')
				get_direction(info, world_map, hei, wid);
			wid++;
		}
		hei++;
	}
	if (flag != 1)
	{
		printf("%s\n", "have 2 player");
		exit(1);
	}
}

char	**save_map(char *line_map, t_info *info)
{
	int	idx;

	idx = 0;
	free(info->map->world_map);
	save_map_get_size(line_map, info);
	info->map->world_map = (char **)malloc(sizeof(char *) * \
		info->map->map_height);
	utils_bzero(info->map->world_map, sizeof(char *) * info->map->map_height);
	while (idx++ < info->map->map_height)
	{
		info->map->world_map[idx] = (char *)malloc(sizeof(char) * \
			info->map->map_width);
		utils_bzero(info->map->world_map[idx], sizeof(char) * \
			info->map->map_width);
	}
	info->map->world_map = utils_split(line_map, '\n');
	set_pos(info->map->world_map, info);
	if (info->pos->pos_x == -20.0 || info->pos->pos_y == -20.0)
	{
		printf("Error\n pos setting");
		exit(1);
	}
	if (!flood_fill((int)info->pos->pos_x, (int)info->pos->pos_y, info))
	{
		printf("Error\n incorrect map");
		exit(1);
	}
	//test code
	for (int i = 0; i < info->map->map_height+1; i++)
		printf("%s\n", info->map->world_map[i]);
	printf("\n");
	//
	free(line_map);
	return (info->map->world_map);
}