/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d1_render_tiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:52 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 17:00:51 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_put_tile(t_data2 *data, int x, int y, t_img img);
void		put_background_to_buffer(t_data2 *data);
void		put_small_background_to_buffer(t_data2 *data);
static void	h_444(t_data2 *data, int x, int y);
static void	h_555(t_data2 *data, t_npc	npc);

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	efficient put sprite to buffer
	doesnt ask questions
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void	ft_put_tile(t_data2 *data, int x, int y, t_img img)
{
	t_sprite	s;

	s.i = -1;
	while (++s.i < img.sz_x)
	{
		s.j = -1;
		while (++s.j < img.sz_y)
		{
			s.pix_c = *(int *)(img.addr + s.j * img.ll + s.i * \
				img.bpp / 8);
			s.buf_i = (y + s.j) * data->buffer.ll + (x + s.i) * \
				(data->buffer.bpp / 8);
			*((unsigned int *)(data->buffer.addr + s.buf_i)) \
				= s.pix_c;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// 		main render for the full the map
void	put_background_to_buffer(t_data2 *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_y)
	{
		x = -1;
		while (++x < data->map_x)
			h_444(data, x, y);
	}
}

// 		redraw only around players
void	put_small_background_to_buffer(t_data2 *data)
{
	int	i;

	h_555(data, data->player);
	i = -1;
	while (++i < data->n_pika)
		if (data->pika[i].x >= 0)
			h_555(data, data->pika[i]);
	if (data->throw.ball.time)
		h_555(data, data->throw.ball);
}

// 														HELPER - put one sprite
static	void	h_444(t_data2 *data, int x, int y)
{
	if (x < 0 || y < 0)
	{
		put("trying to draw around cara goes out of bounds\n");
		return ;
	}
	if (data->map[y][x] == '1')
		ft_put_tile(data, x * SZ, y * SZ, data->i_wall);
	else if (data->map[y][x] == '0' || data->map[y][x] == 'P' || \
		data->map[y][x] == 'z' || data->map[y][x] == 'Z')
		ft_put_tile(data, x * SZ, y * SZ, data->i_ground[0]);
	else if (data->map[y][x] == '*')
		ft_put_tile(data, x * SZ, y * SZ, data->i_ground[1]);
	else if (data->map[y][x] == 'C' || data->map[y][x] == 'c')
		ft_put_tile(data, x * SZ, y * SZ, \
			data->i_ball[(data->map[y][x] == 'c')]);
	else if (data->map[y][x] == 'E')
		ft_put_tile(data, x * SZ, y * SZ, \
			data->i_exit[0 + data->exit[2]]);
}

// 										   HELPER - render 4 direction (cross)
static	void	h_555(t_data2 *data, t_npc	npc)
{
	int	x;
	int	y;

	x = (int)round((double)npc.x / SZ);
	y = (int)round((double)npc.y / SZ);
	h_444(data, x, y);
	h_444(data, x + 1, y);
	h_444(data, x - 1, y);
	h_444(data, x, y + 1);
	h_444(data, x, y - 1);
}
