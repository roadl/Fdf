/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:45:55 by yojin             #+#    #+#             */
/*   Updated: 2024/04/29 17:01:25 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_map_coord(t_map *map_info)
{
	t_point	**map;
	int		x;
	int		y;

	y = -1;
	map = map_info->map;
	map_info->rotate.x = 0;
	map_info->rotate.y = 0;
	map_info->rotate.z = 0;
	if (map_info->width > map_info->height)
		map_info->scale = WIN_WIDTH / (map_info->width * 2.0 * ISO_RATIO);
	else
		map_info->scale = WIN_HEIGHT / (map_info->height * 2.0);
	while (++y < map_info->height)
	{
		x = -1;
		while (++x < map_info->width)
		{
			map[y][x].coord.x -= (map_info->width - 1) / 2.0;
			map[y][x].coord.y -= (map_info->height - 1) / 2.0;
			map[y][x].coord.z *= map_info->max_z;
		}
	}
}

void	calc_map(t_map *map_info)
{
	t_point	**map;
	int		x;
	int		y;

	y = -1;
	map = map_info->map;
	while (++y < map_info->height)
	{
		x = -1;
		while (++x < map_info->width)
			calc_pos(&map[y][x], map_info);
	}
}

int	put_map(t_vars *vars)
{
	t_point	**map;
	int		x;
	int		y;

	y = 0;
	map = vars->map.map;
	while (y < vars->map.height)
	{
		x = 0;
		while (x < vars->map.width)
		{
			my_mlx_pixel_put(vars->data, map[y][x].pos.x,
				map[y][x].pos.y, map[y][x].color);
			if (x != vars->map.width - 1)
				conn_points(&map[y][x], &map[y][x + 1], vars->data);
			if (y != vars->map.height - 1)
				conn_points(&map[y][x], &map[y + 1][x], vars->data);
			x++;
		}
		y++;
	}
	return (0);
}

int	fdf(char *file)
{
	t_vars	vars;
	t_data	*img;

	vars.map.max_z = 0;
	init_map(file, &vars.map);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "yojin's fdf!");
	vars.data = (t_data *)malloc(sizeof(t_data));
	img = vars.data;
	img->img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	calc_map_coord(&vars.map);
	render(&vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, handle_window_close, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, fdf_loop, &vars);
	mlx_loop(vars.mlx);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_printf("ERROR: input one .fdf file\n");
		ft_printf("%s\n", argv[0]);
		return (-1);
	}
	return (fdf(argv[1]));
}
