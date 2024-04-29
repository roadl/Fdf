/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:45:34 by yojin             #+#    #+#             */
/*   Updated: 2024/04/29 16:53:01 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_line_num(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("fdf");
		exit(EXIT_FAILURE);
	}
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (count);
		}
		free(line);
		count++;
	}
}

int	init_point(t_point *point, char *info, int x, int y)
{
	char	**strs;

	strs = ft_split(info, ',');
	if (!strs)
		exit(EXIT_FAILURE);
	point->coord.x = x;
	point->coord.y = y;
	point->coord.z = ft_atoi(strs[0]);
	if (strs[1])
		point->color = atox(strs[1]);
	else
		point->color = 0xFFFFFF;
	free_strs(strs);
	return (1);
}

t_point	*init_line(int fd, int y, t_map *map)
{
	t_point	*point_line;
	char	**strs;
	char	*line;
	int		x;

	line = get_next_line(fd);
	if (!line)
		exit(EXIT_FAILURE);
	strs = ft_split(line, ' ');
	if (!strs)
		exit(EXIT_FAILURE);
	x = -1;
	map->width = get_str_num(strs);
	point_line = (t_point *)malloc(sizeof(t_point) * map->width);
	if (!point_line)
		exit(EXIT_FAILURE);
	while (++x < map->width)
	{
		init_point(point_line + x, strs[x], x, y);
		if (fabs(point_line[x].coord.z) > map->max_z)
			map->max_z = fabs(point_line[x].coord.z);
	}
	free(line);
	free_strs(strs);
	return (point_line);
}

void	init_map(char *file, t_map *map)
{
	int		fd;
	int		count;
	int		i;

	count = get_line_num(file);
	fd = open(file, O_RDONLY);
	map->map = (t_point **)malloc(sizeof(t_point *) * count);
	map->height = count;
	map->offset.x = WIN_WIDTH / 2;
	map->offset.y = WIN_HEIGHT / 2;
	if (fd < 0 || !map->map)
	{
		perror("fdf");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < count)
	{
		map->map[i] = init_line(fd, i, map);
		if (!map->map[i])
		{
			perror("fdf");
			exit(EXIT_FAILURE);
		}
	}
}
