/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:12:58 by yeju              #+#    #+#             */
/*   Updated: 2022/05/10 16:31:41 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cub3D.h"

int	utils_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

void	utils_bzero(void *s, size_t n)
{
	char	*dest;
	size_t	i;

	dest = s;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

int	utils_read_another(char *line, int i)
{
	if (line[i])
	{
		if (line[i] != '\0' && line[i] != '\n')
		{
			free(line);
			printf("%s", "ERROR: unknown identifier\n");
		}
	}
	return (1);
}

// int	utils_read(char **map, char *line, t_info *info)
// {
// 	int i;
// 	int readed;

// 	(void)info;
// 	i = 0;
// 	readed = 0;
// 	while (utils_white_space(line[i]) == 1)
// 		i++;
// 	/*
// 	readed = read_map_setting(line, i, info); //NO, SP, WE, EA, F, C
// 	if (readed == 3) //error
// 		return (0);
// 	if (readed == 2 || readed == 1) //path, color
// 		return (0); //return은아님
// 	*/
// 	if (readed == 0)
// 	{
// 		if (read_map(line, map, i, readed))
// 			return (1);
// 		else //\n, \0: free line
// 		{
// 			utils_read_another(line, i);
// 		}
// 	}
// 	return (1);
// }
