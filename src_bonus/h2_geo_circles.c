/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h2_geo_circles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:25 by marvin            #+#    #+#             */
/*   Updated: 2024/06/18 16:35:11 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		draw_circle(t_data2 *data, t_circle circle);
void		draw_circle_v2(t_data2 *data, t_circle circle, int what_helper);
static void	helper_v64(t_data2 *data, t_circle *c, int x, int y);
static void	helper_v360(t_data2 *data, t_circle *circle, int x, int y);

///////////////////////////////////////////////////////////////////////////////]
//      use v64 for empty circle
//      use v360 for full circle
void	draw_circle(t_data2 *data, t_circle circle)
{
	int	x;
	int	y;
	int	determinant;

	x = 0;
	y = circle.rad;
	determinant = 1 - circle.rad;
	helper_v64(data, &circle, x, y);
	while (++x < y)
	{
		if (determinant < 0)
			determinant += 2 * x + 1;
		else
			determinant += 2 * (x - --y) + 1;
		helper_v64(data, &circle, x, y);
	}
}

// what_helper = 1:	outline circle
// what_helper = 0:	full circle
void	draw_circle_v2(t_data2 *data, t_circle circle, int what_helper)
{
	int		x;
	int		y;
	int		determinant;
	void	(*helper)(t_data2*, t_circle*, int, int);

	if (what_helper)
		helper = helper_v64;
	else
		helper = helper_v360;
	x = 0;
	y = circle.rad;
	determinant = 1 - circle.rad;
	helper(data, &circle, x, y);
	while (++x < y)
	{
		if (determinant < 0)
			determinant += 2 * x + 1;
		else
			determinant += 2 * (x - --y) + 1;
		helper(data, &circle, x, y);
	}
}

//      use v64 for empty circle
static void	helper_v64(t_data2 *data, t_circle *c, int x, int y)
{
	put_pixel_buffer(data, c->x + x, c->y + y, c->color());
	put_pixel_buffer(data, c->x - x, c->y + y, c->color());
	put_pixel_buffer(data, c->x + x, c->y - y, c->color());
	put_pixel_buffer(data, c->x - x, c->y - y, c->color());
	put_pixel_buffer(data, c->x + y, c->y + x, c->color());
	put_pixel_buffer(data, c->x - y, c->y + x, c->color());
	put_pixel_buffer(data, c->x + y, c->y - x, c->color());
	put_pixel_buffer(data, c->x - y, c->y - x, c->color());
}

//      use v360 for full circle
static void	helper_v360(t_data2 *data, t_circle *circle, int x, int y)
{
	int	i;

	i = -x -1;
	while (++i <= x)
	{
		put_pixel_buffer(data, circle->x + i, circle->y + y, circle->color());
		put_pixel_buffer(data, circle->x + i, circle->y - y, circle->color());
	}
	i = -y -1;
	while (++i <= y)
	{
		put_pixel_buffer(data, circle->x + i, circle->y + x, circle->color());
		put_pixel_buffer(data, circle->x + i, circle->y - x, circle->color());
	}
}
