/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:55 by yeju              #+#    #+#             */
/*   Updated: 2022/05/13 09:55:06 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		exit(1);
	else if (key == KEY_W && info->key->w == 0)
		info->key->w = 1;
	else if (key == KEY_S && info->key->s == 0)
		info->key->s = 1;
	else if (key == KEY_A && info->key->a == 0)
		info->key->a = 1;
	else if (key == KEY_D && info->key->d == 0)
		info->key->d = 1;
	else if (key == KEY_LEFT && info->key->left == 0)
		info->key->left = 1;
	else if (key == KEY_RIGHT && info->key->right == 0)
		info->key->right = 1;
	else if (key == KEY_E)
		info->key->e  ^= 1;//xor연산 해놨습니당..
	return (1);
}

int	key_release(int key, t_info *info)
{
	if (key == KEY_W && info->key->w == 1)
		info->key->w = 0;
	else if (key == KEY_S && info->key->s == 1)
		info->key->s = 0;
	else if (key == KEY_A && info->key->a == 1)
		info->key->a = 0;
	else if (key == KEY_D && info->key->d == 1)
		info->key->d = 0;
	else if (key == KEY_LEFT && info->key->left == 1)
		info->key->left = 0;
	else if (key == KEY_RIGHT && info->key->right == 1)
		info->key->right = 0;
	return (1);
}

int	close_win(int keycode, int x, int y, void *param)
{
	(void)keycode;
	(void)x;
	(void)y;
	(void)param;
	exit(1);
}

void	check_leaks()
{
	system("leaks Cub3D");
	return ;
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc != 2)
	{
		printf("%s", "usage: ./Cub3D './map/path'");
		return (0);
	}
	// 0. init
	info = init_info_mlx();
	if (!info)
		exit(1);
	// 1. map
	// 2. vector & mlx init, mlx_new_window
	// 3. textureLoad
	if (!init_info(info, argv[1]))
	{
		printf("Error\n init error");
		exit(1);
	}

	// load_texture(info);
	// 4. hook & engine renew
	hook_set(info);

	// 5. free & game end
	render(info);
	// 6. leaks check
	atexit(check_leaks);
	return (0);
}