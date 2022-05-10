#include "../inc/Cub3D.h"

void    set_wall_data(t_wall_data *wall_data, t_info *info)
{
	wall_data->lineheight = (int)(height / wall_data->perp_wall_dist * 1);
	wall_data->draw_start = -wall_data->lineheight / 2 + height / 2;
	if (wall_data->draw_start < 0)
		wall_data->draw_end = 0;
	wall_data->draw_end = wall_data->lineheight / 2 + height / 2;
	if (wall_data->draw_end >= height)
		wall_data->draw_end = height - 1;
	//wall_data->stepX = x_sign
	if (wall_data->side == 0)
		wall_data->wallx = info->pos->pos_y + wall_data->perp_wall_dist * wall_data->raydir_y;
	else
		wall_data->wallx = info->pos->pos_x + wall_data->perp_wall_dist * wall_data->raydir_x;
	wall_data->wallx -= floor((wall_data->wallx));
}

void    set_texture_data(t_wall_data *wall_data, t_info *info)
{
	wall_data->texX = (int)(wall_data->wallx * (double)texWidth);
	if (wall_data->side == 0 && wall_data->raydir_x > 0)
		wall_data->texX = texWidth - wall_data->texX - 1;
	if (wall_data->side == 1 && wall_data->raydir_x < 0)
		wall_data->texX = texWidth - wall_data->texX - 1;
	wall_data->step_val = 1.0 * texHeight / wall_data->lineheight;
	wall_data->tex_pos = (wall_data->draw_start - height / 2 + wall_data->lineheight / 2)
			* wall_data->step_val;
}

int     set_color(t_wall_data *wall_data, t_info *info)
{
	int texY;
	int color;
	int texnum;

	texY = (int)wall_data->tex_pos & (texHeight - 1);
	wall_data->tex_pos += wall_data->step_val;
	if (wall_data->side && (wall_data->stepX == POSITIVE))
		texnum = TEX_WALL_N;
	else if (wall_data->side && (wall_data->stepX == NEGATIVE))
		texnum = TEX_WALL_S;
	else if (!wall_data->side && (wall_data->stepX == POSITIVE))
		texnum = TEX_WALL_E;
	else
		texnum = TEX_WALL_W;
	color = info->texture[texnum][texHeight * texY + wall_data->texX];
	if (wall_data->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}