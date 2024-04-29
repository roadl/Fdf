/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:03:25 by yojin             #+#    #+#             */
/*   Updated: 2024/04/29 18:43:27 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ONE			18
#define TWO			19
#define THREE		20
#define FOUR		21
#define FIVE		23
#define SIX			22
#define UP          126
#define DOWN        125
#define LEFT        123
#define RIGHT       124
#define ESC         53

#define ROTATE_SPEED	0.0625
#define MOVE_SPEED		5

int	fdf_loop(t_vars *vars)
{
	clear(vars);
	render(vars);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	if (keycode == LEFT)
		vars->map.offset.x -= MOVE_SPEED;
	if (keycode == RIGHT)
		vars->map.offset.x += MOVE_SPEED;
	if (keycode == UP)
		vars->map.offset.y -= MOVE_SPEED;
	if (keycode == DOWN)
		vars->map.offset.y += MOVE_SPEED;
	if (keycode == ONE)
		vars->map.rotate.x += ROTATE_SPEED;
	if (keycode == TWO)
		vars->map.rotate.x -= ROTATE_SPEED;
	return (0);
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	if (mousecode == 4 && vars->map.scale <= 1000)
		vars->map.scale *= 1.1;
	if (mousecode == 5 && vars->map.scale >= 0.001)
		vars->map.scale *= 0.9;
	x = y;
	return (0);
}

int	handle_window_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(EXIT_SUCCESS);
	return (0);
}
