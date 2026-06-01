/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h3_geo_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:22 by marvin            #+#    #+#             */
/*   Updated: 2024/06/18 15:58:19 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		draw_line_v2(t_data2 *data, int a[2], int b[2], unsigned int color);
void		draw_line_v3(t_data2 *data, int a[2], int b[2], unsigned int \
(*co)(void));
void		draw_line_v4(t_data2 *data, int *a, int *b, unsigned int \
(*color)(void));
static void	helper_v555(int *err, int a[2], int dxy[2], int sxy[2]);

///////////////////////////////////////////////////////////////////////////////]
//      	Bresenham's Line Algorithm
//      Single color
void	draw_line_v2(t_data2 *data, int a[2], int b[2], unsigned int color)
{
	int	dxy[2];
	int	sxy[2];
	int	err;

	dxy[0] = abs(b[0] - a[0]);
	dxy[1] = abs(b[1] - a[1]);
	sxy[0] = 1 - 2 * !(a[0] < b[0]);
	sxy[1] = 1 - 2 * !(a[1] < b[1]);
	err = dxy[0] - dxy[1];
	while (1)
	{
		put_pixel_buffer(data, a[0], a[1], color);
		if (a[0] == b[0] && a[1] == b[1])
			break ;
		helper_v555(&err, a, dxy, sxy);
	}
}

//      Color passed as function
void	draw_line_v3(t_data2 *data, int aa[2], int b[2], unsigned int \
(*co)(void))
{
	int	dxy[2];
	int	sxy[2];
	int	a[2];
	int	err;

	a[0] = aa[0];
	a[1] = aa[1];
	dxy[0] = abs(b[0] - a[0]);
	dxy[1] = abs(b[1] - a[1]);
	sxy[0] = 1 - 2 * !(a[0] < b[0]);
	sxy[1] = 1 - 2 * !(a[1] < b[1]);
	err = dxy[0] - dxy[1];
	while (1)
	{
		put_pixel_buffer(data, a[0], a[1], co());
		if (a[0] == b[0] && a[1] == b[1])
			break ;
		helper_v555(&err, a, dxy, sxy);
	}
}

#define EPAISSEUR 3
// ligne + epaisse
void	draw_line_v4(t_data2 *data, int *a, int *b, unsigned int (*color)(void))
{
	int	i_j[2];
	int	a_shifted[2];
	int	b_shifted[2];

	i_j[0] = -EPAISSEUR;
	while (++i_j[0] < EPAISSEUR)
	{
		i_j[1] = -EPAISSEUR;
		while (++i_j[1] < EPAISSEUR)
		{
			a_shifted[0] = a[0] + i_j[0];
			a_shifted[1] = a[1] + i_j[1];
			b_shifted[0] = b[0] + i_j[0];
			b_shifted[1] = b[1] + i_j[1];
			draw_line_v3(data, a_shifted, b_shifted, color);
		}
	}
}

static void	helper_v555(int *err, int a[2], int dxy[2], int sxy[2])
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -dxy[1])
	{
		*err -= dxy[1];
		a[0] += sxy[0];
	}
	if (e2 < dxy[0])
	{
		*err += dxy[0];
		a[1] += sxy[1];
	}
}
