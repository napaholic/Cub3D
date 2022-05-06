#include "../inc/Cub3D.h"

/*
 * 	// WALL CASTING
	for(int x = 0; x < width; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)width - 1; //x-coordinate in camera space
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			}
			else
			{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			}
			//Check if ray has hit a wall
			if(info->map[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height) drawEnd = height - 1;
		//texturing calculations
		int texNum = info->map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = info->posY + perpWallDist * rayDirY;
		else           wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = info->texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			info->buf[y][x] = color;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		info->zBuffer[x] = perpWallDist; //perpendicular distance is used
	}
 */

void    init_DDA_cast(t_wallData *wData, t_info *info)
{
	if (wData->rayDirX < 0)
	{
		wData->stepX = -1;
		wData->sideDistX = (info->pos->posX - wData->map_posX);
	}
	else
	{
		wData->stepX = 1;
		wData->sideDistX = (wData->map_posX + 1.0 - info->pos->posX) * wData->d_DistX;
	}
	if (wData->rayDirY < 0)
	{
		wData->stepY = -1;
		wData->sideDistY = (info->pos->posY - wData->map_posY);
	}
	else
	{
		wData->stepY = 1;
		wData->sideDistY = (wData->map_posY + 1.0 - info->pos->posY) * wData->d_DistY;
	}
}

void    stepProgress_until_hit(t_wallData *wData, t_info *info)//벽에 맞을때까지 sideDist 증가. sideDist 가 나중에 perpWallDist 에 사용됨.
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (wData->sideDistX < wData->sideDistY)
		{
			wData->sideDistX += wData->d_DistX;
			wData->map_posX += wData->stepX;
			wData->side = 0;
		}

	}

}

void    set_DDA(t_wallData *wData, t_info *info, int cur_x)
{
	wData->camera_x = 2 * cur_x / (double)width - 1; //카메라공간 x좌표계
	wData->rayDirX = info->pos->dirX + info->pos->planeX * wData->camera_x;//
	wData->rayDirY = info->pos->dirY + info->pos->planeY * wData->camera_x;
	wData->map_posX = (int)info->pos->posX;
	wData->map_posY = (int)info->pos->posY;
	wData->d_DistX = fabs(1 / wData->rayDirX);
	wData->d_DistY = fabs(1 / wData->rayDirY);
	wData->map_posX = (int)(info->pos->posX);
	wData->map_posY = (int)(info->pos->posY);
	init_DDA_cast(wData, info);
	stepProgress_until_hit(wData, info);
}

void    wall_cast(t_info *info)
{
	t_wallData w_data;
	int x;
	int y;

	x = -1;
	while (++x < width)
	{
		//1. set_DDA
		set_DDA(&w_data, info, x);
		//2. wall_DistCast
		while()
	}
}