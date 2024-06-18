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

int ft_loop_v2(t_data2 *data);
static int	f_is_dying(t_data2 *data);
static void	f_wait_time(clock_t startTime);
static void f_test_time(clock_t startTime, int i);

#define DESIRED_FPS 64
#define FRAME_DURATION_MICROSECONDS (1000000 / DESIRED_FPS)
///////////////////////////////////////////////////////////////////////////////]
// 																		MAIN LOOP
int	ft_loop_v2(t_data2 *data)
{
	clock_t startTime = clock();

// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
	data->time = (data->time + 1) % TIME_F;
	// if (!(data->time % 5))// <!> - - - - - - - - - - -- - - - - </?>
	//     f_print_memory(data);
	// put("%d ", data->time);
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

	// f_test_time(startTime, 1);
	// f_test_time(startTime, 2);
	// f_test_time(startTime, 3);
	mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
	f_wait_time(startTime);
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
	{
		if (!data->is_winning)
			put(CLS MSG_DEAD"\tYou died in %d moves, and got %d/%d pokeballs...\n", data->walk_count, data->num_collected, data->num_ball);
		else
			put(MSG_WIN"\tYou finished with %d moves, picked up %d pokeballs and caught %d/%d mons!\n", \
						data->walk_count, data->num_ball, data->num_pika_caught, data->num_pika);
		exit_all_v2(data);
	}
	circle.center_x = data->player.x + DEMI_SPRITE;
	circle.center_y = data->player.y + DEMI_SPRITE;
	circle.radius = -data->player.time;
	circle.color = data->color_r;
	if (data->is_winning)
		circle.color = ft_black;
	data->player.time -= 2;
	draw_circle_v2(data, circle, 0);
	draw_frame(data, data->i_player, (int [4]){data->player.x, data->player.y, data->player.f, 4}, ft_black);
	if (data->is_winning)
		draw_frame(data, data->i_player, (int [4]){data->player.x, data->player.y, data->player.f, 4}, NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
static void	f_wait_time(clock_t startTime)
{
	clock_t frameTime;
	double timeDifference;

	frameTime = clock(); // Frame time in clock ticks
	timeDifference = ((double)(frameTime - startTime) / CLOCKS_PER_SEC) * 1000;
	if (timeDifference < FRAME_DURATION_MILLISECONDS)
		usleep((FRAME_DURATION_MILLISECONDS - timeDifference) * 1000);
	else
		put("(%.2f) ", timeDifference);
}

///////////////////////////////////////////////////////////////////////////////]
static void	f_test_time(clock_t startTime, int i)
{
	clock_t frameTime;
	double timeDifference;

	frameTime = clock();
	timeDifference = ((double)(frameTime - startTime) / CLOCKS_PER_SEC) * 1000;
	put("time process (%d)= %f\n", i, timeDifference);
}
