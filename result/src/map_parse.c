#include "../inc/Cub3D.h"

int	read_txt_path(char *line, int first, int second, int idx, t_info *info)
{
	(void)line;
	(void)first;
	(void)second;
	(void)idx;
	(void)info;
	return 0;
}

int	read_color(char *line, int c, int idx, t_info *info)
{
	(void)line;
	(void)c;
	(void)idx;
	(void)info;
	return 0;
}

//반환값: 2:종료,오류 / 1: 정상작동
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

int	read_map_sub(char *line, char **map, t_info *info)
{
	int	idx;
	int	ret;

	(void)map;
	idx = 0;
	while (utils_white_space(line[idx]) == 1)
		++idx;
	if (line[idx] != '\0')
	{
		printf("%s", "Error\n map: incorrect configuration\n");
		exit(1);
	}
	ret = read_map_setting(line, idx, info);
	if (ret == 0)
		return (0);
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
		printf("%s", "ERROR\n file open\n");
		return (0);
	}
	map = (char *)malloc(sizeof(char) * 2);
	utils_bzero(map, sizeof(char));
	line = (char *)malloc(sizeof(char) * 1);
	utils_bzero(line, sizeof(char));
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		if (!read_map_sub(line, &map, info))
			return (0);
		line = NULL;
		if (ret == 0)
			break ;
	}
	free(line);
	return (map);
}