/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:52:00 by yeju              #+#    #+#             */
/*   Updated: 2022/05/10 13:25:35 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	get_map_size(t_info *info)
{
	int	i;
	int	wid;
	int	wid2;
	int	hei;

	i = 0;
	wid = 0;
	wid2 = 0;
	hei = 0;
	while (info->map->line_map[i] != '\0')
	{
		if (info->map->line_map[i] == '\n')
			++hei;
		++i;
	}
	info->map->map_height = hei;
	i = 0;
	while (info->map->line_map[i] != '\0')
	{
		//testcode
		// printf("i : %d ", i);
		// printf("wid : %d ", wid);
		// printf("wid2 : %d\n", wid2);
		wid = 0;
		while (info->map->line_map[i++] != '\n')
			++wid;
		if (wid2 < wid)
			wid2 = wid;
		++i;
		info->map->map_width = wid2;
	}
	return ;
}

int	read_map(char *line, char **map, int i, int readed)
{
	if (line[i] == '1' || line[i] == '0' \
		|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
	{
		*map = utils_strjoin(*map, line);
		if (readed == 0 && line[i])
			*map = utils_strjoin(*map, "\n");
		free(line);
		return (1);
	}
	// i = 0;
	// while (*map)
	// 	++i;
	// *map[i] = '\0';
	return (0);
}

char	*read_line_map(char *argv, t_info info)
{
	int		fd;
	int		ret;
	char	*map;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		printf("%s", "ERROR: file open\n");
	map = (char *)malloc(sizeof(char) * 2);
	utils_bzero(map, sizeof(char));
	line = (char *)malloc(sizeof(char) * 1);
	utils_bzero(line, sizeof(char));
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		utils_read(&map, line, &info);
		line = NULL;
		free(line);
		if (ret == 0)
			break ;
	}
	//test code
	// printf("최종맵: \n%s", map);
	return (map);
}

char	**read_world_map(char *argv)
{
	int		fd;
	char	*tmp;
	int		i;
	char	**map;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		printf("%s", "ERROR\n");
	i = 0;
	while ((get_next_line(fd, &tmp)))
	{
		free(tmp);
		i++;
	}
	free(tmp);
	map = (char **)malloc(sizeof(char *) * (i + 2));
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		printf("%s", "ERROR\n");
	i = 0;
	while ((get_next_line(fd, &map[i])))
		i++;
	map[++i] = 0;
	return (map);
}
