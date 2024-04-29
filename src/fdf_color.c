/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:00:47 by yojin             #+#    #+#             */
/*   Updated: 2024/03/14 17:21:11 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(t_point *p1, t_point *p2, t_vec2f *point, int slope_x)
{
	int		color;
	int		temp;
	float	ratio;

	color = 0;
	if (p1->color == p2->color)
		return (p1->color);
	if (slope_x)
		ratio = (point->x - p1->pos.x) / (p2->pos.x - p1->pos.x);
	else
		ratio = (point->y - p1->pos.y) / (p2->pos.y - p1->pos.y);
	temp = get_t(p1->color) + (get_t(p2->color) - get_t(p1->color)) * ratio;
	color += temp & 0xFF000000;
	temp = get_r(p1->color) + (get_r(p2->color) - get_r(p1->color)) * ratio;
	color += temp & 0x00FF0000;
	temp = get_g(p1->color) + (get_g(p2->color) - get_g(p1->color)) * ratio;
	color += temp & 0x0000FF00;
	color += get_b(p1->color) + (get_b(p2->color) - get_b(p1->color)) * ratio;
	return (color);
}

int	get_t(int trgb)
{
	return (trgb & 0xFF000000);
}

int	get_r(int trgb)
{
	return (trgb & 0xFF0000);
}

int	get_g(int trgb)
{
	return (trgb & 0xFF00);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
