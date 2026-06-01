/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:36 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 16:54:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int			ft_loop_v2(t_data2 *data);
static int	f_is_dying(t_data2 *data);
static void	f_wait_time(clock_t startTime);
static void	print_end(t_data2 *data);
// static void f_test_time(clock_t startTime, int i);

#define FRAME_DURATION_MICROSECONDS 16666
///////////////////////////////////////////////////////////////////////////////]
// 																	MAIN LOOP
int	ft_loop_v2(t_data2 *data)
{
	clock_t	startime;

	startime = clock();
	data->time = (data->time + 1) % TIME_F;
	if (data->player.time < 0)
		return (f_is_dying(data));
	check_what_your_walking_on(data);
	f_move_player_v2(data);
	ft_move_enemy(data);
	if (data->throw.ball.time > 0)
		check_throw_path(data);
	ft_background(data, data->tmp_bit);
	ft_foreground(data);
	if (data->throw.ball.time)
		move_ball(data);
	check_attack(data);
	mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
	f_wait_time(startime);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	hijack any other action in loop if player.time < 0 
draw growing circle around player, leave room for YOU DIED?
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static int	f_is_dying(t_data2 *data)
{
	t_circle	circle;

	if (data->player.time <= TIME_TO_DIE)
		print_end(data);
	circle.x = data->player.x + HALF;
	circle.y = data->player.y + HALF;
	circle.rad = -data->player.time;
	circle.color = data->color_r;
	if (data->is_winning)
		circle.color = ft_black;
	data->player.time -= 2;
	draw_circle_v2(data, circle, 0);
	draw_frame(data, data->i_player, (int [4]){data->player.x, data->player.y, \
		data->player.f, 4}, ft_black);
	if (data->is_winning)
		draw_frame(data, data->i_player, (int [4]){data->player.x, \
			data->player.y, data->player.f, 4}, NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
	return (0);
}

static void	print_end(t_data2 *data)
{
	if (!data->is_winning)
		put(CLS MSG_DEAD"\tYou died in %d moves, and got %d/%d pokeballs...\n", \
			data->steps, data->n_collec, data->n_ball);
	else
		put(CLS MSG_WIN"\tYou finished with %d moves, picked up %d pokeballs \
and caught %d/%d mons!\n", \
					data->steps, data->n_ball, data->n_gotta, data->n_pika);
	exit_all_v2(data);
}

///////////////////////////////////////////////////////////////////////////////]
static void	f_wait_time(clock_t startTime)
{
	clock_t	frame_t;
	double	time_diff;

	frame_t = clock();
	time_diff = ((double)(frame_t - startTime) / CLOCKS_PER_SEC) * 1000;
	if (time_diff < FRAME_DURATION_MILLISECONDS)
		usleep((FRAME_DURATION_MILLISECONDS - time_diff) * 1000);
	else
		put("(%.0ffps) ", 1000.0 / time_diff);
}

///////////////////////////////////////////////////////////////////////////////]
// static void	f_test_time(clock_t startTime, int i)
// {
// 	clock_t frameTime;
// 	double timeDifference;

// 	frameTime = clock();
// 	timeDifference = ((double)(frameTime - startTime) / CLOCKS_PER_SEC) * 1000;
// 	put("time process (%d)= %f\n", i, timeDifference);
// }
