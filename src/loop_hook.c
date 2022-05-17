/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:31:53 by yeju              #+#    #+#             */
/*   Updated: 2022/05/17 12:16:38 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

void	set_texture_data(t_info *info, t_wall_data *wall_data, t_img *txt, int count)
{
	// int	d; //@
	// d = info->pos->pos_y * txt->size_line - (info->win_hei * wall_data->camera_x) * \
	// 	txt->size_line / 2 + wall_data->lineheight * txt->size_line / 2;
	// //@
	// int txy = ((d * txt->img_height) / wall_data->lineheight) / txt->size_line;

	wall_data->tex_x = (int)(wall_data->wallx * (double)info->img->img_width);
	info->img->data[(int)info->pos->pos_y * info->img->size_line + count * info->img->bits_per_pixel / 8] = \
		txt->data[txt->size_line + wall_data->tex_x * (txt->bits_per_pixel / 8)];
	info->img->data[(int)info->pos->pos_y * info->img->size_line + count * info->img->bits_per_pixel / 8 + 1] = \
		txt->data[txt->size_line + wall_data->tex_x * (txt->bits_per_pixel / 8) + 1];
	info->img->data[(int)info->pos->pos_y * info->img->size_line + count * info->img->bits_per_pixel / 8 + 2] = \
		txt->data[txt->size_line + wall_data->tex_x * (txt->bits_per_pixel / 8) + 2];
	
	if (wall_data->side == 0 && wall_data->raydir_x > 0)
		wall_data->tex_x = 32 - wall_data->tex_x - 1;
	if (wall_data->side == 1 && wall_data->raydir_x < 0)
		wall_data->tex_x = 32 - wall_data->tex_x - 1;
	wall_data->step_val = 1.0 * 32 / wall_data->lineheight;
	wall_data->tex_pos = (wall_data->draw_start - info->win_hei / 2 + wall_data->lineheight / 2)
			* wall_data->step_val;
	return ;
}

void	texture_load(t_wall_data *wall_data, t_info *info, int count)
{
	if (wall_data->side == 0)
		wall_data->wallx = info->pos->pos_y + wall_data->perp_wall_dist \
			* wall_data->raydir_y;
	else
		wall_data->wallx = info->pos->pos_x + wall_data->perp_wall_dist \
			* wall_data->raydir_x;
	wall_data->wallx -= floor((wall_data->wallx));
	set_texture_data(info, wall_data, *info->txt, count);
}

void	paint_ceiling(t_wall_data *wall_data, t_info *info)
{
	unsigned char	*src;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	src = (unsigned char *)&info->ceiling_color;
	r = src[0];
	g = src[1];
	b = src[2];
	info->img->data[0 * info->img->size_line + wall_data->draw_start * info->img->bits_per_pixel / 8] = r;
	info->img->data[0 * info->img->size_line + wall_data->draw_start * info->img->bits_per_pixel / 8 + 1] = g;
	info->img->data[0 * info->img->size_line + wall_data->draw_start * info->img->bits_per_pixel / 8 + 2] = b;
}

void	paint_floor(t_wall_data *wall_data, t_info *info)
{
	unsigned char	*src;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	src = (unsigned char *)&info->floor_color;
	r = src[0];
	g = src[1];
	b = src[2];
	info->img->data[info->win_hei * info->img->size_line + wall_data->draw_end * info->img->bits_per_pixel / 8] = r;
	info->img->data[info->win_hei * info->img->size_line + wall_data->draw_end * info->img->bits_per_pixel / 8 + 1] = g;
	info->img->data[info->win_hei * info->img->size_line + wall_data->draw_end * info->img->bits_per_pixel / 8 + 2] = b;
}

void	wall_cast(t_info *info, t_wall_data *wall_data, int count)
{
	set_dda(wall_data, info, count);
	init_dda_cast(wall_data, info);
	step_progress_until_hit(wall_data, info);
	calc_perp_dist(wall_data, info);
	set_wall_data(wall_data, info);
	// info->buffer[count] = wall_data->perp_wall_dist;
	// printf("!: %f\n", wall_data->perp_wall_dist);
	texture_load(wall_data, info, count);
	
	paint_ceiling(wall_data, info);
	paint_floor(wall_data, info);
	return ;
}

// int		set_color(t_wall_data *wall_data, t_info *info)
// {
// 	int texY;
// 	int color=0; //=0
// 	int texnum;

// 	texY = (int)wall_data->tex_pos & (32 - 1);
// 	wall_data->tex_pos += wall_data->step_val;
// 	if (wall_data->side && (wall_data->step_x == 1))
// 		texnum = TEX_WALL_N;
// 	else if (wall_data->side && (wall_data->step_x == -1))
// 		texnum = TEX_WALL_S;
// 	else if (!wall_data->side && (wall_data->step_x == 1))
// 		texnum = TEX_WALL_E;
// 	else
// 		texnum = TEX_WALL_W;
// 	(void)info;
// 	color = info->txt[texnum][32 * texY + wall_data->tex_x];
// 	if (wall_data->side == 1)
// 		color = (color >> 1) & 8355711;
// 	return (color);
// }

int	raycasting(t_info *info)
{
	t_wall_data	*wall_data;
	int			count;
	int			y;

	wall_data = (t_wall_data *)malloc(sizeof(t_wall_data));
	if (!wall_data)
		return (0);
	utils_bzero(wall_data, sizeof(t_wall_data));
	count = -1;
	while (count++ < info->win_wid)
	{
		wall_cast(info, wall_data, count);
		// y = wall_data->draw_start - 1;
		// while (++y < wall_data->draw_end)
		// 	info->buf[y][count] = set_color(wall_data, info);
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
	free(wall_data);
	return (1);
}

void	hook_set(t_info *info)
{
	mlx_hook(info->win, X_KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win, X_KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win, X_CLICK_EXIT, 0, close_win, info);
	mlx_loop_hook(info->mlx, render, info);
	mlx_loop(info->mlx);
}
