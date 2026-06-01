/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e2_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 17:07:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		f_move_player_v2(t_data2 *data);
void		ft_move_enemy(t_data2 *data);
void		move_ball(t_data2 *data);
static void	move_pika_v2(t_data2 *data, int i);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		if a caracter has a time value, ft_move will update its position
        and frame according to the GLOBAL_TIME
        use current frame to calculate direction
*******************************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        move player in a [0,1,0,2,0] fashion
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	f_move_player_v2(t_data2 *data)
{
	if (!data->player.time)
		return ;
	if (!((data->time + 1) % (TIME_PLAYER - data->running)))
		return ;
	data->player.time -= 1;
	data->player.x += data->player.dx;
	data->player.y += data->player.dy;
	if (data->player.time == 54)
		data->player.f += 1;
	else if (data->player.time == 40)
		data->player.f += -1;
	else if (data->player.time == 24)
		data->player.f += 2;
	else if (data->player.time == 10)
		data->player.f += -2;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        move all enemy. if time == 0, random what happen next
        its also the ft_save_time of the enemies
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	ft_move_enemy(t_data2 *data)
{
	int	i;
	int	random;

	i = -1;
	while (++i < data->num_pika && i < 10)
	{
		if (data->pika[i].time < 0 || data->pika[i].x < 0)
			continue ;
		if (data->pika[i].time > 0)
			move_pika_v2(data, i);
		else
		{
			random = (rand() % (PIKA_MOVE_CHANCE + i));
			if (random < PIKA_TURN_CHANCE)
				data->pika[i].f = random % 8;
			if (random <= 3)
			{
				data->pika[i].dx = (int)cos(random * PI / 2);
				data->pika[i].dy = (int)sin(random * PI / 2);
				if (check_path_npc(data, data->pika[i], i) > 0)
					data->pika[i].time = 64;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        animation handler for ball throw
        move it 1 pixel, change its sprite
        if ball touch a pika, its time is negative
            in this case, the catching ball animation is played
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	move_ball(t_data2 *data)
{
	// if (data->time % TIME_BALL)
	// 	return ;
	if (data->throw.ball.time < 0)
	{
		draw_circle(data, (t_circle){data->throw.ball.x + DEMI_SPRITE, data->throw.ball.y + DEMI_SPRITE, -data->throw.ball.time, random_white});
		if (data->throw.ball.time == -5)
			data->pika[data->throw.pika_caught].x = -1;
		if (data->throw.ball.time == -1)
			data->map[(int)round(data->throw.ball.y / SPRITE_SIZE)][(int)round(data->throw.ball.x / SPRITE_SIZE)] = 'c';
		data->throw.ball.time++;
		return ;
	}
	data->throw.ball.x += data->throw.ball.dx;
	data->throw.ball.y += data->throw.ball.dy;
	if (!(data->throw.ball.time % 5))
		data->throw.ball.f = (data->throw.ball.f + 1) % 12;
	if (data->throw.ball.time == 1)
		data->map[(int)round(data->throw.ball.y / SPRITE_SIZE)][(int)round(data->throw.ball.x / SPRITE_SIZE)] = 'C';
	data->throw.ball.time--;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        if time saved > 0, move pika n*i
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void	move_pika_v2(t_data2 *data, int i)
{
	// if (data->time % (TIME_PIKA + i))
	//     return ;
	data->pika[i].time--;
	data->pika[i].x += data->pika[i].dx;
	data->pika[i].y += data->pika[i].dy;
	if (!(data->pika[i].time % (16 + i)))
		data->pika[i].f ^= 1;
}
