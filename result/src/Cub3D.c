#include "../inc/Cub3D.h"

int init_mlx(t_info *info)
{
	if (!(info->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (0);
	utils_bzero(info->mlx, sizeof(t_mlx));
	return (1);
}

int init_key(t_info *info)
{
	if (!(info->key = (t_key *)malloc(sizeof(t_key))))
		return (0);
	utils_bzero(info->key, sizeof(t_key));
	info->key->left = 0;
	info->key->right = 0;
	info->key->down = 0;
	info->key->up = 0;
	return (1);
}

int key_press(int key, t_info *info)
{
	if (key == KEY_ESC)
		exit(1); //free
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

int key_release(int key, t_info *info)
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

int close_win(int keycode, int x, int y, void *param)
{
	(void)keycode;
	(void)x;
	(void)y;
	(void)param;
	exit(1); //free
}

int main(int argc, char * argv[])
{
	t_info *info;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	utils_bzero(info, sizeof(t_info));
	if (argc != 2)
	{
		printf("%s", "usage: ./Cub3D './map/path'");
		return (0);
	}
	// 0. init
	
	init_map(info);
	init_mlx(info);
	init_key(info);
	// 1. map
	// info.map->world_map = read_world_map(argv[1]);
	info->map->line_map = read_line_map(argv[1], *info);
	get_map_size(info);
	//testcode
	// printf("%d\n", info->map->mapHeight);
	// printf("%d\n", info->map->mapWidth);
	
	// 2. textureLoad
	
	// 3. vector
	
	// 4. hook
	info->mlx->mlxptr = mlx_init();
	info->mlx->winptr = mlx_new_window(info->mlx->mlxptr, 500, 500, "Cub3D");
	// mlx_loop_hook(info->mlx->mlxptr);
	mlx_hook(info->mlx->winptr, X_KEY_PRESS, 0, &key_press, info);
	mlx_hook(info->mlx->winptr, X_KEY_RELEASE, 0, &key_release, info);
	mlx_hook(info->mlx->winptr, X_CLICK_EXIT, 0, &close_win, 0);
	mlx_loop(info->mlx->mlxptr);
	// 5. engine renew
	return (0);
}