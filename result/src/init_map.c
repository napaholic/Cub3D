#include "Cub3D.h"

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
	int hei;

	i = 0;
	wid = 0;
	hei = 0;
	while (info->map->world_map[i] != '\n')
	{
		++wid;
		++i;
	}
	info->map->mapWidth = wid;
	while (info->map->world_map[i] != '\0')
	{
		if (info->map->world_map[i] == '\n')
			++hei;
		++i;
	}
	info->map->mapHeight = hei;
}
