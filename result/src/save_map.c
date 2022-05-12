/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:07:07 by yeju              #+#    #+#             */
/*   Updated: 2022/05/12 19:38:09 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	save_map_get_size(char *line_map, t_info *info) //wid, hei는 malloc때 쓰이기 때문에 -1해서 저장됨
{
	int	i;
	int	wid;
	int	wid2;
	int	hei;

	i = 0;
	wid = 0;
	wid2 = 0;
	hei = 0;
	while (line_map[i] != '\0')
	{
		if (line_map[i] == '\n')
			++hei;
		i++;
	}
	info->map->map_height = hei;
	i = 0;
	while (hei--)
	{
		//test code
		// printf(" linemap: \n%s\n", line_map);
		// printf(" 1: %d\n", wid);
		// printf(" 2: %d\n", wid2);
		info->map->map_width = wid2;
		wid = 0;
		while (line_map[i++] != '\n')
			wid++;
		if (wid2 < wid)
			wid2 = wid;
	}
	//test code
	// printf("hei: %d\n", info->map->map_height);
	// printf("wid: %d\n", info->map->map_width);
	return ;
}

void	set_pos(char **world_map, t_info *info)
{
	int	wid;
	int	hei;

	hei = 0;
	while (hei < info->map->map_height)
	{
		wid = 0;
		while (wid < info->map->map_width)
		{
			if (world_map[hei][wid] == 'N' || world_map[hei][wid] == 'W' || \
				world_map[hei][wid] == 'E' || world_map[hei][wid] == 'S')
				{
					info->pos->pos_x = (double)wid;
					info->pos->pos_y = (double)hei;
				}
			wid++;
		}
		hei++;
	}
	//test code
	printf("posx: %f\n", info->pos->pos_x);
	printf("posy: %f\n", info->pos->pos_y);
}

char	**save_map(char *line_map, t_info *info)
{
	int	idx;

	idx = 0;
	free(info->map->world_map); //init할때 했던 malloc 풀기
	save_map_get_size(line_map, info); //map size 재기
	//malloc
	info->map->world_map = (char **)malloc(sizeof(char *) * info->map->map_height);
	utils_bzero(info->map->world_map, sizeof(char *) * info->map->map_height);
	while (idx++ < info->map->map_height)
	{
		info->map->world_map[idx] = (char *)malloc(sizeof(char) * info->map->map_width);
		utils_bzero(info->map->world_map[idx], sizeof(char) * info->map->map_width);
	}
	//malloc한 **map에 map저장
	info->map->world_map = utils_split(line_map, '\n');
	//test code
	// for (int i = 0; i < info->map->map_height + 2; i++)
	// 	printf("%s ", world_map[i]);

	//set pos
	set_pos(info->map->world_map, info); //pos도 당연히 인덱스값이라 -1상태
	if (info->pos->pos_x == -20.0 || info->pos->pos_y == -20.0)
	{
		printf("Error\n pos setting");
		exit(1);
	}


	//map check
	// save_map_check(map);
	
	//set pos? & 잘못된 pos일 경우
	info->map->world_map = 0;
	free(line_map);
	return (info->map->world_map);
}