#include "../inc/Cub3D.h"

void	set_wall_data(t_wall_data *wall_data, t_info *info)
{
	wall_data->lineheight = (int)(info->win_hei / wall_data->perp_wall_dist);
	wall_data->draw_start = -wall_data->lineheight / 2 + ((info->win_hei / 2) * wall_data->camera_x);
	if (wall_data->draw_start < 0)
		wall_data->draw_start = 0;
	wall_data->draw_end = wall_data->lineheight / 2 + ((info->win_hei / 2) * wall_data->camera_x);
	if (wall_data->draw_end >= info->win_hei)
		wall_data->draw_end = info->win_hei - 1;
	//wall_data->step_x = x_sign
	// if (wall_data->side == 0)
	// 	wall_data->wallx = info->pos->pos_y + wall_data->perp_wall_dist * wall_data->raydir_y;
	// else
	// 	wall_data->wallx = info->pos->pos_x + wall_data->perp_wall_dist * wall_data->raydir_x;
	// wall_data->wallx -= floor((wall_data->wallx));
}

void	set_texture_data(t_wall_data *wall_data, t_info *info)
{
	wall_data->texX = (int)(wall_data->wallx * (double)32);
	if (wall_data->side == 0 && wall_data->raydir_x > 0)
		wall_data->texX = 32 - wall_data->texX - 1;
	if (wall_data->side == 1 && wall_data->raydir_x < 0)
		wall_data->texX = 32 - wall_data->texX - 1;
	wall_data->step_val = 1.0 * 32 / wall_data->lineheight;
	wall_data->tex_pos = (wall_data->draw_start - info->win_hei / 2 + wall_data->lineheight / 2)
			* wall_data->step_val;
}

int		set_color(t_wall_data *wall_data, t_info *info)
{
	int texY;
	int color=0; //=0
	int texnum;

	texY = (int)wall_data->tex_pos & (32 - 1);
	wall_data->tex_pos += wall_data->step_val;
	if (wall_data->side && (wall_data->step_x == POSITIVE))
		texnum = TEX_WALL_N;
	else if (wall_data->side && (wall_data->step_x == NEGATIVE))
		texnum = TEX_WALL_S;
	else if (!wall_data->side && (wall_data->step_x == POSITIVE))
		texnum = TEX_WALL_E;
	else
		texnum = TEX_WALL_W;
	(void)info;
	color = info->texture[texnum][32 * texY + wall_data->texX];
	if (wall_data->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}