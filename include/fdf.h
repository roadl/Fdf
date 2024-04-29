/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:46:00 by yojin             #+#    #+#             */
/*   Updated: 2024/04/29 16:55:30 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../ft_printf/ft_printf.h"
# include "../gnl/get_next_line.h"

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

# define ISO_RATIO	1.7320508
# define Z_SCALE	1.75

# define TRUE	1
# define FALSE	0

typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_point
{
	t_vec3	coord;
	t_vec2	pos;
	int		color;
}	t_point;

typedef struct s_map
{
	t_point	**map;
	t_vec2	offset;
	t_vec3	rotate;
	int		width;
	int		height;
	int		max_z;
	double	scale;
}	t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*data;
	t_map	map;
}	t_vars;

void	init_map(char *file, t_map *map);
int		atox(char *str);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		sign(double n);
int		get_str_num(char **strs);

int		get_color(t_point *p1, t_point *p2, t_vec2f *point, int slope_x);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

void	calc_map(t_map *map_info);
int		put_map(t_vars *vars);
void	calc_pos(t_point *point, t_map *map_info);
void	conn_points(t_point *p1, t_point *p2, t_data *data);

int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int mousecode, int x, int y, t_vars *vars);
int		handle_window_close(t_vars *vars);

int		fdf_loop(t_vars *vars);
void	clear(t_vars *vars);
void	render(t_vars *vars);

#endif