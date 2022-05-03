#include "../inc/Cub3D.h"


void init_map(t_info *info)
{
	info->map->mapWidth = 0;
	info->map->mapHeight = 0;
	return ;
}

void get_map_size(t_info *info) //index로 세기 때문에 0이면 1칸 있는거
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
	info->map->mapHeight = hei;
	i = 0;
	while (info->map->line_map[i] != '\0')
	{
		if (info->map->line_map[i] != '\n')
		{
			++i;
			++wid;
		}
		if (wid2 < wid)
			wid2 = wid;
		wid = 0;
		info->map->mapWidth = wid2;
		++i;
	}
	return ;
}

char	**read_world_map(char *argv)
{
	int		fd;
	char	*tmp;
	int		i;
	char	**map;

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
	//test code
	for (int index = 0; index < 24; index++)
		printf("%s\n", map[index]);
	return (map);
}

 char	*read_line_map(char *argv)
 {
 	int fd;
 	char *buf;
 	int len;

 	fd = open(argv, O_RDONLY);
 	if (fd < 0)
 		printf("%s", "ERROR: file open\n");
 	len = read(fd, &buf, BUFFER_SIZE);
     buf = (char *)malloc(sizeof(char) * (len + 2));
 	buf[len] = '\0';
 	printf("%s", buf);
 	return buf;
 }