/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:16:26 by yeju              #+#    #+#             */
/*   Updated: 2022/05/17 12:13:16 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	utils_check_txt_path(char *line)
{
	int	i;

	i = 0;
	while (utils_white_space(line[i]))
		++i;
	if ((line[i] != 'N' && line[i] != 'S' && \
		line[i] != 'W' && line[i] != 'E') || \
		(line[i + 1] != 'O' && line[i + 1] != 'E' && line[i + 1] != 'A'))
		return (0);
	i += 2;
	while (utils_white_space(line[i]))
		++i;
	if (line[i] != '.' && line[i + 1] != '/')
		return (0);
	while (utils_isprint(line[i]) && \
		!utils_white_space(line[i]) && line[i] != '\0')
		i++;
	while (utils_white_space(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int	utils_check_txt_execute(char *path)
{
	int	fd;
	int	len;

	len = utils_strlen(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (0);
	}
	if (path[len - 1] != 'm' || path[len - 2] != 'p' || \
		path[len - 3] != 'x' || path[len - 4] != '.')
		return (0);
	return (1);
}

int	texture_set(t_info *info, char *path, int idx)
{
	if (!utils_check_txt_execute(path))
		return (0);
	info->txt[idx]->img = mlx_xpm_file_to_image(info->mlx, path, \
		&info->txt[idx]->img_width, &info->txt[idx]->img_height);
	if (!info->txt[idx])
		return (0);
	info->txt[idx]->data = (int*)mlx_get_data_addr(info->txt[idx]->img, \
		&info->txt[idx]->bits_per_pixel, &info->txt[idx]->size_line, \
			&info->txt[idx]->endian);
	free(path);
	return (1);
}

char	*utils_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	new_len;

	if (s == NULL)
		return (NULL);
	if (utils_strlen(s) < start)
		return (utils_strdup(""));
	new_len = utils_strlen(s + start);
	if (new_len < len)
		len = new_len;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	utils_strlcpy(substr, s + start, len + 1);
	return (substr);
}

int	utils_get_size(char *str, int idx)
{
	int	ret;

	ret = 0;
	while (utils_isprint(str[idx + ret]) && !utils_white_space(str[idx + ret]))
		++ret;
	return (ret);
}
