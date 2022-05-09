#include "../inc/Cub3D.h"

void    cal_vec(t_info *info)
{
	floor_cast(info);
	wall_cast(info);
}

int render(t_info *info)
{
	cal_vec(info);
//	draw(info);
	key_update(info);
}

void    engine_run(t_info *info)
{
	mlx_loop_hook(info->mlx->mlxptr, &render, &info);
}