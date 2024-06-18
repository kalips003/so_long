/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g2_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 19:56:57 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_pixel_buffer(t_data2 *data, int x, int y, unsigned color);

///////////////////////////////////////////////////////////////////////////////]
// 			put pixel to buffer, secure for out_of_bounds
void	put_pixel_buffer(t_data2 *data, int x, int y, unsigned color)
{
	char	*dst;
	int		offset;

	if (x < 0 || y < 0 || x >= data->buffer.sz_x || y >= data->buffer.sz_y)
		return ;
	offset = (y * data->buffer.ll + x * (data->buffer.bpp / 8));
	dst = data->buffer.addr + offset;
	*(unsigned int*)dst = color;
}
