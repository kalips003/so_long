/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h1_geo_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:28 by marvin            #+#    #+#             */
/*   Updated: 2024/06/18 21:36:27 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_put_rectangle(t_data2 *data, int xy[2], int dxy[2], \
unsigned int (*color)(void));
void	ft_put_square(t_data2 *data, int xy[2], int size, unsigned int color);

///////////////////////////////////////////////////////////////////////////////]
// 																		 SQUARES
// draw between top-left(xy) & bot-right(dxy)
void	ft_put_rectangle(t_data2 *data, int xy[2], int dxy[2], \
unsigned int (*color)(void))
{
	int	i;
	int	j;
	int	buf_i;

	if (xy[0] < 0 || xy[1] < 0 || dxy[0] > data->buffer.sz_x || \
		dxy[1] > data->buffer.sz_y)
	{
		put("rect too big\n");
		return ;
	}
	i = xy[0];
	while (++i < dxy[0])
	{
		j = xy[1];
		while (++j < dxy[1])
		{
			buf_i = j * data->buffer.ll + i * (data->buffer.bpp / 8);
			*((unsigned int *)(data->buffer.addr + buf_i)) = color();
		}
	}
}

// to use with scaler:
// if scale = 3, draw squares of size 3
void	ft_put_square(t_data2 *data, int xy[2], int size, unsigned int color)
{
	int	i;
	int	j;
	int	buf_i;

	if (xy[0] < 0 || xy[1] < 0 || xy[0] + size >= data->buffer.sz_x || \
		xy[1] + size >= data->buffer.sz_y)
		return ;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			buf_i = (xy[1] + j) * data->buffer.ll + (xy[0] + i) * \
				(data->buffer.bpp / 8);
			*((unsigned int *)(data->buffer.addr + buf_i)) = color;
		}
	}
}
