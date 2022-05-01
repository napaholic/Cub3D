#include "Cud3D.h"

int **save_int(char **map)
{
	int **ret_map = (int **)malloc(sizeof(int *) * info->map->mapWidth + 1);

	for (int l = 0; l < info->map->mapWidth; l++)
	{
		ret_map[l] = (int *)malloc(sizeof(int) * info->map->mapHeight + 1);
	}

	for (int i = 0; i < info->map->mapWidth; i++)
		for (int j = 0; j < info->map->mapHeight; j++)
			ret_map[i][j] = map[i][j] - '0';
	return (ret_map);
}

int	**read_map(char *argv)
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
	return (save_int(map));
}
	//x// 1. 파일 읽기
	//x// 1-1. 빈 파일인지 확인
	//x// 1-2. "\n"단위로 spilt
	// //1-2-0. raw col 세기 (info->map->mapW, mapH) & malloc후 저장
	// //1-2-1. 벽이 뚫려있는 경우 같은 에러요소 처리
	// //1-2-2. 정사각형이 아닌 경우 빈공간 채워주기
	// //1-3. info->map에 int**로 저장하기


int main(int argc, char * argv[])
{
	t_info info;

	// 0. init

	// 1. map
	info.map = parse_map(argv[1]);
	
	// 2. textureLoad
	
	// 3. vector
	
	// 4. hook
	
	// 5. engine renew
}