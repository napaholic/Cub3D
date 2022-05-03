#include "../inc/Cub3D.h"

void utils_bzero(void *s, size_t n)
{
	char *dest;
	size_t i;

	dest = s;
	i = 0;
	while(i++ < n)
		*dest++ = 0;
}

//이 함수를 malloc, bzero로 바꾸기
void init_map(t_info *info)
{
	info->map->mapWidth = 0;
	info->map->mapHeight = 0;
	return ;
}

//index로 세기 때문에 0이면 1칸 있는거
void get_map_size(t_info *info)
{
	int i;
	int wid;
	int wid2;
	int hei;

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
	info->map->mapHeight = hei; //개행으로 끝났을 때 1이 안늘어남
	i = 0;
	while (info->map->line_map[i] != '\0')
	{
		//testcode
		// printf("i : %d ", i);
		// printf("wid : %d ", wid);
		// printf("wid2 : %d\n", wid2);
		wid = 0;
		while (info->map->line_map[i] != '\n')
		{
			++wid;
			++i;
		}
		if (wid2 < wid)
		{
			wid2 = wid;
		}
		++i;
		info->map->mapWidth = wid2;
	}
	return ;
}

char **read_world_map(char *argv)
{
	int fd;
	char *tmp;
	int i;
	char **map;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		printf("%s", "ERROR: file open\n");
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
		printf("%s", "ERROR: file open\n");
	i = 0;
	while ((get_next_line(fd, &map[i])))
		i++;
	map[++i] = 0;
	return (map);
}

//그럼 map안에있는 NO는 어떻게하지...?!
int read_map_path(char *line, char fir, char sec, t_info *info)
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

int read_map_color(char *line, char fc, t_info *info)
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

int read_map_setting(char *line, int i, t_info *info)
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

int read_map(char *line, char **map, int i, int readed)
{
	if (line[i] == '1' || line[i] == '0' \
		|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
	{
		*map = ft_strjoin(*map, line);
		if (readed == 0 && line[i])
			*map = ft_strjoin(*map, "\n");
		free(line);
		return (1);
	}
	// i = 0;
	// while (*map)
	// 	++i;
	// *map[i] = '\0';
	return (0);
}

int white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int read_another(char *line, int i)
{
	if (line[i])
	{
		if (line[i] != '\0' && line[i] != '\n')
		{
			free(line);
			printf("%s", "ERROR: unknown identifier\n");
		}
	}
	return (1);
}

int utils_read(char **map, char *line, t_info *info)
{
	int i;
	int readed = 0;

	(void)info;
	i = 0;
	while (white_space(line[i]) == 1)
		i++;
	/*
	readed = read_map_setting(line, i, info); //NO, SP, WE, EA, F, C
	if (readed == 3) //error
		return (0);
	if (readed == 2 || readed == 1) //path, color
		return (0); //return은아님
	*/
	if (readed == 0) //map
	{
		if (read_map(line, map, i, readed))
			return (1);
		else //\n, \0: free line
		{
			read_another(line, i);
		}
	}
	return (1);
}

char *read_line_map(char *argv, t_info info)
{
	int fd;
	int ret;
	char *map;
	char *line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		printf("%s", "ERROR: file open\n");
	map = (char *)malloc(sizeof(char) * 2);
	utils_bzero(map, sizeof(char));
	line = (char *)malloc(sizeof(char) * 1);
	utils_bzero(line, sizeof(char));
	while ((ret = get_next_line(fd, &line)) != -1) //line에 담아서
	{
		//test code
		// printf("test line: %s \n", line);
		utils_read(&map, line, &info); //map에 담음
		line = NULL;
		//test code
		// printf("test map: \n%s\n", map);
		free(line);
		if (ret == 0)
			break;
	}
	//test code
	// printf("최종맵: \n%s", map);
	return (map);
}
