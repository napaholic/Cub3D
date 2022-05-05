#include "../inc/Cub3D.h"

void set_pos(t_info *info)
{
	unsigned int i; //hei
	unsigned int j; //wid

	i = 0; //-1로 바꾸기
	j = 0;

	while (i < info->map->mapHeight)
	{
		while (j < info->map->mapWidth)
		{
			printf("%c", info->map->world_map[(int)i][(int)j]);
			if (info->map->world_map[(int)i][(int)j] == 'N')
			{
				info->posX = (double)j;
				info->posY = (double)i;
			}
			j = j + 1.0;
		}
		i = i + 1.0;
	}
	if (info->posX == -1.0 && info->posY == -1.0)
		printf("pos세팅안됨\n");
	//test code
	printf("posX: %f\n", info->posX);
	printf("posY: %f\n", info->posY);
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