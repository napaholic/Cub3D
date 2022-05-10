#include "../inc/Cub3D.h"

int	utils_check_txt_path(char *path)
{
	int	i;

	i = 0;
	//초반 공백 지나가기
	while (utils_white_space(path[i]))
		++i;
	//NO SO WE EA 아니면 실패
	if ((path[i] != 'N' && path[i] != 'S' && path[i] != 'W' && path[i] != 'E') || \
		(path[i + 1] != 'O' && path[i + 1] != 'E' && path[i + 1] != 'A'))
		return (0);
	//NO SO WE EA 지나가기
	i += 2;
	//공백 지나가기
	while (utils_white_space(path[i]))
		++i;
	// ./으로 시작하지 않는 path는 실패
	if (path[i] != '.' && path[i + 1] != '/')
		return (0);
	//path지나가기
	while (utils_isprint(path[i]) && !utils_white_space(path[i]) && path[i] != '\0')
		++i;
	//path뒤에 빈 공간 지나가기
	while (utils_white_space(path[i]))
		++i;
	//'\0'으로 안끝나고 더 있으면 잘못된 path
	if (path[i] != '\0')
		return (0);
	return (1);
}

int	read_txt_path(char *line, int first, int second, int idx, t_info *info)
{
	char	*path;

	if (!utils_check_txt_path(line))
	{
		printf("Error\n wrong path: %s\n", line);
		exit(1);
	}
	while (utils_white_space(line[idx]))
		++idx;
	//파일 실행권한, 확장명 확인(xpm)
	if (first == 'N' && second == 'O')
		return (texture_set(info, path, TEX_WALL_N));
	if (first == 'S' && second == 'O')
		return (texture_set(info, path, TEX_WALL_S));
	if (first == 'E' && second == 'A')
		return (texture_set(info, path, TEX_WALL_E));
	if (first == 'W' && second == 'E')
		return (texture_set(info, path, TEX_WALL_W));
	else
		return (0);
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