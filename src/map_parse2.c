/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:49:07 by yeju              #+#    #+#             */
/*   Updated: 2022/05/14 17:28:24 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

char	*get_texture_path(char *line, int idx)
{
	char	*path;

	idx += 3;
	path = utils_substr(line, idx, utils_get_size(line, idx));
	return (path);
}

int	read_txt_path(char *line, int first, int second, int idx, t_info *info)
{
	char	*path;

	if (!utils_check_txt_path(line))
	{
		printf("Error\n wrong path: %s\n", line);
		exit(1);
	}
	path = get_texture_path(line, idx);
	if (!path)
		return (0);
	utils_check_txt_execute(path);
	while (utils_white_space(line[idx]))
		++idx;
	if (first == 'N' && second == 'O')
		return (texture_set(info, path, TEX_WALL_N));
	if (first == 'S' && second == 'O')
		return (texture_set(info, path, TEX_WALL_S));
	if (first == 'E' && second == 'A')
		return (texture_set(info, path, TEX_WALL_E));
	if (first == 'W' && second == 'E')
		return (texture_set(info, path, TEX_WALL_W));
	else
		return (0);
}

int	utils_check_color(char *line, int c, int idx)
{
	int	i;

	i = 0;
	while (utils_white_space(line[idx]))
		idx++;
	if (line[idx] == c)
		i = idx + 1;
	while (utils_white_space(line[i]))
		i++;
	while (utils_isdigit(line[i]) || line[i] == ',')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int	get_rgb_value(char *line)
{
	int		rgb;
	char	**split_rgb;
	int		r;
	int		g;
	int		b;

	rgb = 0;
	line++;
	while (utils_white_space(*line))
		line++;
	split_rgb = utils_split(line, ',');
	r = utils_atoi(split_rgb[0]);
	g = utils_atoi(split_rgb[1]);
	b = utils_atoi(split_rgb[2]);
	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	utils_free_split(split_rgb);
	return (rgb);
}

int	read_color(char *line, int c, int idx, t_info *info)
{
	int	rgb;

	rgb = 0;
	if (!utils_check_color(line, c, idx))
	{
		printf("Error\n wrong color\n");
		exit(1);
	}
	rgb = get_rgb_value(line);
	if (c == 'F')
		info->floor_color = rgb;
	else if (c == 'C')
		info->ceiling_color = rgb;
	free(line);
	return (1);
}
