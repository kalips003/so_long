/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d3_render_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:47 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 16:54:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ft_foreground(t_data2 *data);
void		draw_frame(t_data2 *data, t_img img, int xyfe[4], unsigned int (*color)(void));
static void	f_put_event_ball_to_buffer_v3(t_data2 *data);
static void	f_put_player_to_buffer_v4(t_data2 *data);
static void	f_put_pika_to_buffer_v4(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
void	ft_foreground(t_data2 *data)
{
	f_put_player_to_buffer_v4(data);
	f_put_pika_to_buffer_v4(data);
	f_put_event_ball_to_buffer_v3(data);
	// if (data->attack.time)
	// 	render attak
}

///////////////////////////////////////////////////////////////////////////////]
// draw img at xyfe[0], xyfe[1]
// if color != NULL, non transparent pixel will be color
// xyfe[2] = frame number to render
// xyfe[3] = frame encoding x
void	draw_frame(t_data2 *data, t_img img, int xyfe[4], unsigned int (*color)(void))
{
	t_frame	f;

	f.sz = img.sz_x / xyfe[3];
	if (xyfe[0] < 0 || xyfe[1] < 0 || xyfe[0] + f.sz > data->buffer.sz_x || xyfe[1] + f.sz > data->buffer.sz_y)
		return ((void)put(ERR"------> out of bounds (1)\n"));
	f.frame_start_x = (xyfe[2] % xyfe[3]) * f.sz;
	f.frame_start_y = (xyfe[2] / xyfe[3]) * f.sz;
	f.i = -1;
	while (++f.i < f.sz)
	{
		f.j = -1;
		while (++f.j < f.sz)
		{
			f.src_x = f.frame_start_x + f.i;
			f.src_y = f.frame_start_y + f.j;
			f.pixel_index = (f.src_y * img.ll + f.src_x * (img.bpp / 8));
			f.pixel_color = *(int *)(img.addr + f.pixel_index);
			if (f.pixel_color == 0xFF000000)
				continue ;
			if (color)
				f.pixel_color = color();
			f.buffer_index = (xyfe[1] + f.j) * data->buffer.ll + (xyfe[0] + f.i) * (data->buffer.bpp / 8);
			*(unsigned int *)(data->buffer.addr + f.buffer_index) = f.pixel_color;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
static void	f_put_event_ball_to_buffer_v3(t_data2 *data)
{
	int	i;

	i = data->time % 12;
	if (data->throw.ball.time > 0)
		draw_frame(data, data->i_throw, (int [4]){data->throw.ball.x + OFFSET_BALL_THR, data->throw.ball.y + OFFSET_BALL_THR, i, 1}, NULL);
	else if (data->throw.ball.time < 0)
		draw_frame(data, data->i_throw, (int [4]){data->throw.ball.x + OFFSET_BALL_THR, data->throw.ball.y + OFFSET_BALL_THR, i, 1}, ft_r_white);
}

static void	f_put_player_to_buffer_v4(t_data2 *data)
{
	if (data->player.time >= 0)
		draw_frame(data, data->i_player, (int [4]){data->player.x, data->player.y, data->player.f, 4}, NULL);
	else
		draw_frame(data, data->i_player, (int [4]){data->player.x, data->player.y, data->player.f, 4}, data->color_r);
}

static void	f_put_pika_to_buffer_v4(t_data2 *data)
{
	int	i;

	i = -1;
	while (++i < data->num_pika)
	{
		if (data->pika[i].x < 0)
			continue ;
		if (data->pika[i].time == -1)
			draw_frame(data, data->i_pika, (int [4]){data->pika[i].x, data->pika[i].y, data->pika[i].f, 2}, data->color_r);
		else
			draw_frame(data, data->i_pika, (int [4]){data->pika[i].x, data->pika[i].y, data->pika[i].f, 2}, NULL);
	}
}
