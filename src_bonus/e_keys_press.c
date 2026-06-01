/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_keys_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:45 by marvin            #+#    #+#             */
/*   Updated: 2024/06/20 02:26:40 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int			key_press(int keysym, t_data2 *data);
int			key_release(int keysym, t_data2 *data);
static void	f_save_time_player(t_data2 *data, int dx, int dy, int frame);
static void	f_save_time_ball(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        if player has a time, doesnt register any input
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int	key_press(int keysym, t_data2 *data)
{
	if (keysym == XK_Escape)
		exit_all_v2(data);
	if (data->player.time)
		return (0);
	if (keysym == XK_d || keysym == XK_Right)
		f_save_time_player(data, 1, 0, 0);
	else if (keysym == XK_s || keysym == XK_Down)
		f_save_time_player(data, 0, 1, 4);
	else if (keysym == XK_a || keysym == XK_Left)
		f_save_time_player(data, -1, 0, 8);
	else if (keysym == XK_w || keysym == XK_Up)
		f_save_time_player(data, 0, -1, 12);
	else if (keysym == XK_space && !data->throw.ball.time)
		f_save_time_ball(data);
	return (0);
}

int	key_release(int keysym, t_data2 *data)
{
	if (keysym == XK_Control_L && !data->player.time)
		data->running ^= 1;
	if (keysym == XK_e)
		print_data(data);
	if (keysym == XK_space)
		data->running = 0;
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
static void	f_save_time_player(t_data2 *data, int dx, int dy, int frame)
{
	data->player.dx = dx;
	data->player.dy = dy;
	if (data->player.f != frame)
	{
		data->player.f = frame;
		return ;
	}
	data->player.time = 64;
	if (check_path_npc(data, data->player, -1))
		data->steps++;
	else
	{
		data->player.dx = 0;
		data->player.dy = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////]
//      initial ball event handler, check immediate path, ball count, give time
static void	f_save_time_ball(t_data2 *data)
{
	if (!data->n_hold)
		return ;
	if (check_path_npc(data, data->player, -1) == 0)
		return ;
	data->throw.ball.time = SZ * THROW_RANGE;
	data->throw.ball.f = 0;
	data->throw.ball.x = data->player.x;
	data->throw.ball.y = data->player.y;
	data->throw.ball.dx = data->player.dx;
	data->throw.ball.dy = data->player.dy;
	data->n_hold--;
}
