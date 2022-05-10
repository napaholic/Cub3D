#include "../inc/Cub3D.h"

int	utils_check_txt_path(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (utils_white_space(line[i]))
		++i;
	if ((line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E') || \
		(line[i + 1] != 'O' && line[i + 1] != 'E' && line[i + 1] != 'A'))
		return (0);
	i += 2;
	while (utils_white_space(line[i]))
		++i;
	if (line[i] != '.' && line[i + 1] != '/')
		return (0);
	while (utils_isprint(line[i]) && !utils_white_space(line[i]) && line[i] != '\0')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

//txt path가 유효한지 확인
int	utils_check_txt_execute(char *path)
{
	int	fd;
	int	len;

	len = utils_strlen(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (0);
	}
	if (path[len - 1] != 'm' || path[len - 2] != 'p' || \
		path[len - 3] != 'x' || path[len - 4] != '.')
		return (0);
	return (1);
}

int	texture_set(t_info *info, char *path, int idx)
{
	(void)info;
	(void)path;
	(void)idx;
	return 0;
}

// texture_set 안에서 utils_check_txt_execute()로 txtpath 확인하기
int	read_txt_path(char *line, int first, int second, int idx, t_info *info)
{
	char	*path;

	if (!utils_check_txt_path(line))
	{
		printf("Error\n wrong path: %s\n", line);
		exit(1);
	}
	path = ""; //path만 따로 저장하는 함수 만들기 ->구조체에해야할지고민
	//test code
	//printf("txt path is: %s\n", path);
	// utils_check_txt_execute(path);
	while (utils_white_space(line[idx]))
		++idx;
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

int	utils_check_color(char *line, int c, int idx)
{
	int	i;

	i = 0;
	while (utils_white_space(line[idx]))
		idx++;
	if (line[idx] == c)
		i = idx + 1;
	while (utils_white_space(line[i]))
		i++;
	while (utils_isdigit(line[i]) || line[i] == ',')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int	read_color(char *line, int c, int idx, t_info *info)
{
	int	rgb;

	rgb = 0;
	//잘못된 형식인지 확인
	if (!utils_check_color(line, c, idx))
	{
		printf("Error\n wrong color\n");
		exit(1);
	}	
	//rgb로 변환해서 rgb에 담기
	// rgb = rgb로 변환해주는 함수()
	
	// 저장해주기
	if (c == 'F')
		info->floor_color = rgb;
	else if (c == 'C')
		info->ceiling_color = rgb;
	free(line); //txt path랑 color다 읽었으니 free
	return (1);
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
	if (ret == 2)
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