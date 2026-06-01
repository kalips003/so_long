/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d2_render_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:50 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 16:54:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_background(t_data2 *data, int sw);
static void	draw_frame_scaled(t_data2 *data, t_img img, int xyfe[3], \
							unsigned int (*color)(void));
static void	ft_stamina(t_data2 *data);
static void	put_balls_background(t_data2 *data);
static void	ft_draw_score(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
// 														  UPDATE THE BACKGROUND
// if sw: draw all background
// if !sw: draw only necessary
void	ft_background(t_data2 *data, int sw)
{
	if (sw)
	{
		put_background_to_buffer(data);
		data->tmp_bit = 0;
	}
	else
		put_small_background_to_buffer(data);
	ft_put_rectangle(data, (int [2]){0, data->buffer.sz_y - BLACK_BOT}, \
		(int [2]){END_X_BB, data->buffer.sz_y}, ft_black);
	ft_put_rectangle(data, (int [2]){data->buffer.sz_x - BALL_START_X - \
		OFFSET_BALL * data->n_hold, data->buffer.sz_y - BLACK_BOT}, \
		(int [2]){data->buffer.sz_x, data->buffer.sz_y}, ft_black);
	ft_put_rectangle(data, (int [2]){END_X_BB - 2, data->buffer.sz_y + \
		BOT_STAMINA}, (int [2]){data->buffer.sz_x - BALL_START_X - OFFSET_BALL \
		* data->n_hold + 1, data->buffer.sz_y}, ft_black);
	ft_stamina(data);
	put_balls_background(data);
	ft_draw_score(data);
}

///////////////////////////////////////////////////////////////////////////////]
// draw img at xyfe[0], xyfe[1]
// if color != NULL, non transparent pixel will be color
// xyfe[2] = scalling
void	draw_frame_scaled(t_data2 *data, t_img img, int xyfe[3], \
unsigned int (*color)(void))
{
	t_frame	f;

	f.sz = img.sz_x;
	if (xyfe[0] < 0 || xyfe[1] < 0 || xyfe[0] + img.sz_x * xyfe[2] > \
		data->buffer.sz_x || xyfe[1] + img.sz_y * xyfe[2] > data->buffer.sz_y)
		return ((void)put(ERR"------> out of bounds (1)\n"));
	f.i = -1;
	while (++f.i < img.sz_x)
	{
		f.j = -1;
		while (++f.j < img.sz_y)
		{
			f.pix_i = (f.j * img.ll + f.i * (img.bpp / 8));
			f.pix_c = *(int *)(img.addr + f.pix_i);
			if (f.pix_c == 0xFF000000)
				continue ;
			if (color)
				f.pix_c = color();
			ft_put_square(data, (int [2]){xyfe[0] + f.i * xyfe[2], xyfe[1] \
				+ f.j * xyfe[2]}, xyfe[2], f.pix_c);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// update stamina, and render it
static void	ft_stamina(t_data2 *data)
{
	int	i;
	int	j;
	int	sta;

	if (data->running)
		data->stamina = max(data->stamina - 1, 0);
	else
		data->stamina = min(data->stamina + 1, MAX_ENDURANCE);
	if (!data->stamina)
	{
		data->running = 0;
		return ;
	}
	sta = (int)(((double)data->stamina / MAX_ENDURANCE) * data->buffer.sz_x);
	i = data->buffer.sz_y + BOT_STAMINA;
	while (++i < data->buffer.sz_y)
	{
		j = -1;
		while (++j < sta)
			put_pixel_buffer(data, j, i, data->color());
	}
}

///////////////////////////////////////////////////////////////////////////////]
//      put retrieved balls and caught pika on bottom
static void	put_balls_background(t_data2 *data)
{
	int	i;
	int	x;
	int	y;

	y = data->map_y * SZ + BALL_START_Y;
	i = -1;
	while (++i < data->n_hold)
	{
		x = data->buffer.sz_x - BALL_START_X - OFFSET_BALL * i;
		draw_frame(data, data->i_big_ball[0], (int [4]){x, y, 0, 1}, NULL);
	}
	i = -1;
	while (++i < data->n_gotta)
	{
		x = PIKA_START_X + OFFSET_BALL * i;
		draw_frame(data, data->i_big_ball[1], (int [4]){x, y, 0, 1}, NULL);
	}
}

void	ft_draw_score(t_data2 *data)
{
	int				score;
	int				i;
	int				start_y_posi;
	unsigned int	(*color)(void);

	score = data->steps;
	color = NULL;
	if (data->player.time < 0 || data->running)
		color = data->color_r;
	i = START_X_SCORE;
	start_y_posi = data->buffer.sz_y + START_Y_SCORE;
	while (score > 9)
	{
		draw_frame_scaled(data, data->i_numbers[score % 10], \
			(int [3]){i, start_y_posi, 4}, color);
		i += DECIMAL_SCORE;
		score /= 10;
	}
	draw_frame_scaled(data, data->i_numbers[score % 10], \
		(int [3]){i, start_y_posi, 4}, color);
}
