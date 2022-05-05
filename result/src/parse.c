#include "../inc/Cub3D.h"

void set_pos(t_info *info)
{
	int i; //hei
	int j; //wid

	i = -1; //-1로 바꾸기
	while (++i < info->map->mapHeight)
	{
		j = -1;
		while (++j < info->map->mapWidth)
		{
			if (info->map->world_map[i][j] == 'N')
			{
				info->posX = (double)j;
				info->posY = (double)i;
			}
		}
	}
	if (info->posX == -1.0 && info->posY == -1.0)
		printf("pos세팅안됨\n");
	//test code
	// printf("posX: %f\n", info->posX);
	// printf("posY: %f\n", info->posY);
}

void set_info_pos(t_info *info)
{
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	return ;
}

void init_info(t_info *info)
{
	set_info_pos(info);
	init_map(info);
	init_mlx(info);
	init_key(info);
	return ;
}

void set_data(t_info *info)
{
	(void)info;
}

void load_texture(t_info *info)
{
	(void)info;
	//texture 구성
}