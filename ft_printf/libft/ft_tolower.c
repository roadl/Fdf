/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:27:00 by yojin             #+#    #+#             */
/*   Updated: 2023/10/08 20:28:16 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int C)
{
	if (C >= 'A' && C <= 'Z')
		C += 32;
	return (C);
}
