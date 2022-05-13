#include "../inc/Cub3D.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

// void    load_texture(t_info *info)
// {
// 	t_img   img;

// 	load_image(info, info->texture[0], "../textures/blue_block.xpm", &img);
// 	load_image(info, info->texture[1], "../textures/green_block.xpm", &img);
// 	load_image(info, info->texture[2], "../textures/red_block.xpm", &img);
// 	load_image(info, info->texture[3], "../textures/yellow_block.xpm", &img);
// 	load_image(info, info->texture[4], "../textures/blue_block.xpm", &img);
// 	// load_image(info, info->texture[5], "../textures/floor.xpm", &img);
// 	// load_image(info, info->texture[6], "../textures/floor2.xpm", &img);
// 	printf("?");
// }