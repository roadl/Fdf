/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:45:57 by yojin             #+#    #+#             */
/*   Updated: 2024/03/07 13:35:56 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	atox(char *str)
{
	int	result;

	if (ft_strncmp((str), "0x", 2) != 0)
		return (0);
	str += 2;
	result = 0;
	while (*str)
	{
		result *= 16;
		if (ft_isdigit(*str))
			result += *str - '0';
		else
			result += ft_tolower(*str) - 'a' + 10;
		str++;
	}
	return (result);
}

int	get_str_num(char **strs)
{
	int	count;

	count = 0;
	if (!strs)
		return (0);
	while (strs[count])
		count++;
	return (count);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char			*dst;
	unsigned int	*temp;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	temp = (unsigned int *)dst;
	*temp = color;
}

int	sign(double n)
{
	if (n < 0)
		return (-1);
	if (n > 0)
		return (1);
	return (0);
}
