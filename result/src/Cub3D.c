#include "../inc/Cub3D.h"


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

	if (argc != 2)
	{
		printf("%s", "usage:./cub3D 'map'");
		return (0);
	}
	// 0. init
	init_map(&info);
	// 1. map
	// info.map->world_map = read_world_map(argv[1]);
	info.map->line_map = read_line_map(argv[1], info);
	get_map_size(&info);
	//testcode
	// printf("%d\n", info.map->mapHeight);
	// printf("%d\n", info.map->mapWidth);
	
	// 2. textureLoad
	
	// 3. vector
	
	// 4. hook
	
	// 5. engine renew
	return (0);
}