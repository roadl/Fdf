/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:41:26 by yojin             #+#    #+#             */
/*   Updated: 2024/04/29 17:00:35 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_pos(t_point *point, t_map *map_info)
{
	t_vec3	rotate;

	rotate.x = point->coord.x;
	rotate.y = point->coord.y * cos(map_info->rotate.x)
		- point->coord.z * sin(map_info->rotate.x);
	rotate.z = point->coord.y * sin(map_info->rotate.x)
		+ point->coord.z * cos(map_info->rotate.x);
	point->pos.x = (rotate.x - rotate.y) * ISO_RATIO * map_info->scale;
	point->pos.y = ((rotate.x + rotate.y) - rotate.z)
		* map_info->scale;
	point->pos.x += map_info->offset.x;
	point->pos.y += map_info->offset.y;
}

void	init_slope(int *slope_x, t_vec2f *delta, t_vec2f *slope, t_vec2f *move)
{
	slope->x = delta->y / delta->x;
	slope->y = delta->x / delta->y;
	if (slope->x <= 1 && slope->x >= -1)
	{
		*slope_x = 1;
		move->x = sign(delta->x);
		move->y = slope->x * move->x;
	}
	else
	{
		*slope_x = 0;
		move->y = sign(delta->y);
		move->x = slope->y * move->y;
	}
}

void	conn_points(t_point *p1, t_point *p2, t_data *data)
{
	t_vec2f	delta;
	t_vec2f	slope;
	t_vec2f	move;
	t_vec2f	point;
	int		slope_x;

	delta.x = p2->pos.x - p1->pos.x;
	delta.y = p2->pos.y - p1->pos.y;
	init_slope(&slope_x, &delta, &slope, &move);
	point.x = p1->pos.x;
	point.y = p1->pos.y;
	while (1)
	{
		point.x += move.x;
		point.y += move.y;
		if ((slope_x && point.x == p2->pos.x)
			|| (!slope_x && point.y == p2->pos.y))
			break ;
		my_mlx_pixel_put(data, point.x, point.y,
			get_color(p1, p2, &point, slope_x));
	}
}

void	clear(t_vars *vars)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			my_mlx_pixel_put(vars->data, x, y, 0);
	}
}

void	render(t_vars *vars)
{
	calc_map(&vars->map);
	put_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}
