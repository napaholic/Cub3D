/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:07:07 by yeju              #+#    #+#             */
/*   Updated: 2022/05/12 18:38:37 by yeju             ###   ########.fr       */
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

char	**save_map(char *line_map, t_info *info)
{
	free(info->map->world_map); //init할때 했던 malloc 풀기
	save_map_get_size(line_map, info);
	//malloc
	//map check
	//set pos? & 잘못된 pos일 경우
	info->map->world_map = 0;
	free(line_map);
	return (info->map->world_map);
}