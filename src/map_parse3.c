/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:49:29 by yeju              #+#    #+#             */
/*   Updated: 2022/05/13 17:49:43 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	read_map_setting(char *line, int idx, t_info *info)
{
	int	ret;
	int	first;
	int	second;

	if (line[idx] && line[idx + 1])
	{
		first = line[idx];
		second = line[idx + 1];
	}
	else
		return (2);
	if (first == 'N' || first == 'W' || first == 'E' || first == 'S')
		ret = read_txt_path(line, first, second, idx, info);
	else if (first == 'F' || first == 'C')
		ret = read_color(line, line[idx], idx, info);
	else
		ret = 2;
	return (ret);
}

int	map_check(char *line, char **map, int idx, int gnl_ret)
{
	if (utils_white_space(line[idx]) || line[idx] == '1' || line[idx] == '0')
	{
		*map = utils_strjoin(*map, line);
		if (gnl_ret != 0 && line[idx])
			*map = utils_strjoin(*map, "\n");
		free(line);
		return (1);
	}
	return (0);
}

int	read_map_sub(char *line, char **map, t_info *info, int gnl_ret)
{
	int	idx;
	int	ret;

	idx = 0;
	while (utils_white_space(line[idx]) == 1)
		++idx;
	ret = read_map_setting(line, idx, info);
	if (ret == 0)
	{
		printf("%s\n", "end?");
		return (0);
	}
	else
	{
		map_check(line, map, idx, gnl_ret);
	}
	return (1);
}

char	*read_map(char *argv, t_info *info)
{
	int		fd;
	int		ret;
	char	*map;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		printf("%s", "ERROR\n cannot open file\n");
		exit(1);
		return (0);
	}
	map = (char *)malloc(sizeof(char) * 2);
	utils_bzero(map, sizeof(char));
	line = (char *)malloc(sizeof(char) * 1);
	utils_bzero(line, sizeof(char));
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		if (line && !read_map_sub(line, &map, info, ret))
			return (0);
		line = NULL;
		if (ret == 0)
			break ;
	}
	free(line);
	return (map);
}
