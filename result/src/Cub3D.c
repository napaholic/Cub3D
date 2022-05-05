/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:55 by yeju              #+#    #+#             */
/*   Updated: 2022/05/05 13:28:15 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		info->key->esc = 1;
	if (key == KEY_A || key == KEY_LEFT)
		info->key->left = 1;
	if (key == KEY_D || key == KEY_RIGHT)
		info->key->right = 1;
	if (key == KEY_S || key == KEY_DOWN)
		info->key->down = 1;
	if (key == KEY_W || key == KEY_UP)
		info->key->up = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == KEY_A || key == KEY_LEFT)
		info->key->left = 0;
	if (key == KEY_D || key == KEY_RIGHT)
		info->key->right = 0;
	if (key == KEY_S || key == KEY_DOWN)
		info->key->down = 0;
	if (key == KEY_W || key == KEY_UP)
		info->key->up = 0;
	return (0);
}

int	close_win(int keycode, int x, int y, void *param)
{
	(void)keycode;
	(void)x;
	(void)y;
	(void)param;
	exit(1); //free
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (0);
	utils_bzero(info, sizeof(t_info));
	if (argc != 2)
	{
		printf("%s", "usage: ./Cub3D './map/path'");
		return (0);
	}
	// 0. init
	init_info(info);
	// 1. map
	info->map->line_map = read_line_map(argv[1], *info);
	get_map_size(info);
	info->map->world_map = read_world_map(argv[1]);
	//map읽은뒤 init_info해도 될듯!.! 일단은 pos값은 따로 뺄게용
	set_pos(info);
	// testcode
	/*
	printf("mapHei: %d\n", info->map->mapHeight);
	printf("mapWid: %d\n", info->map->mapWidth);
	printf("print line map: \n%s\n", info->map->line_map);
	printf("test worldmap[2][2]: %c\n", info->map->world_map[2][2]);
	printf("print world map: \n");
	for (int i = 0; i < info->map->mapHeight; i++)
		printf("%s\n", info->map->world_map[i]);
	*/
	// 2. vector & mlx init, mlx_new_window
	info->mlx->mlxptr = mlx_init();
	info->mlx->winptr = mlx_new_window(info->mlx->mlxptr, 500, 500, "Cub3D");
	// 3. textureLoad
	load_texture(info);

	
	// 4. hook & engine_set
	engine_set(info);
	// mlx_loop_hook(info->mlx->mlxptr);

	// 5. engine renew
	engine_run(info);
	mlx_loop(info->mlx->mlxptr);
	return (0);
}
