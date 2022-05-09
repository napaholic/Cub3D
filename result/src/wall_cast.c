#include "../inc/Cub3D.h"

void    set_wall_data(t_wallData *wData, t_info *info)
{
	wData->lineheight = (int)(height / wData->perp_wall_dist * 1);
	wData->draw_start = -wData->lineheight / 2 + height / 2;
	if (wData->draw_start < 0)
		wData->draw_end = 0;
	wData->draw_end = wData->lineheight / 2 + height / 2;
	if (wData->draw_end >= height)
		wData->draw_end = height - 1;
	//wData->stepX = x_sign
	if (wData->side == 0)
		wData->wallx = info->pos->posY + wData->perp_wall_dist * wData->rayDirY;
	else
		wData->wallx = info->pos->posX + wData->perp_wall_dist * wData->rayDirX;
	wData->wallx -= floor((wData->wallx));
}

void    set_texture_data(t_wallData *wData, t_info *info)
{
	wData->texX = (int)(wData->wallx * (double)texWidth);
	if (wData->side == 0 && wData->rayDirX > 0)
		wData->texX = texWidth - wData->texX - 1;
	if (wData->side == 1 && wData->rayDirX < 0)
		wData->texX = texWidth - wData->texX - 1;
	wData->step_val = 1.0 * texHeight / wData->lineheight;
	wData->tex_pos = (wData->draw_start - height / 2 + wData->lineheight / 2)
			* wData->step_val;
}

int     set_color(t_wallData *wData, t_info *info)
{
	int texY;
	int color;
	int texnum;

	texY = (int)wData->tex_pos & (texHeight - 1);
	wData->tex_pos += wData->step_val;
	if (wData->side && (wData->stepX == POSITIVE))
		texnum = TEX_WALL_N;
	else if (wData->side && (wData->stepX == NEGATIVE))
		texnum = TEX_WALL_S;
	else if (!wData->side && (wData->stepX == POSITIVE))
		texnum = TEX_WALL_E;
	else
		texnum = TEX_WALL_W;
	color = info->texture[texnum][texHeight * texY + wData->texX];
	if (wData->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}