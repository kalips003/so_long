/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e2_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 17:01:07 by agallon          ###   ########.fr       */
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
******************************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        move player in a [0,1,0,2,0] fashion
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	f_move_player_v2(t_data2 *data)
{
	int	speed;

	if (!data->player.time)
		return ;
	speed = PLAYER_SPEED;
	if (data->running)
		speed = PLAYER_SPEED * 2;
	data->player.time -= speed;
	data->player.x += speed * data->player.dx;
	data->player.y += speed * data->player.dy;
	if (data->player.time == 60)
		data->player.f += 1;
	else if (data->player.time == 48)
		data->player.f += -1;
	else if (data->player.time == 32)
		data->player.f += 2;
	else if (data->player.time == 16)
		data->player.f += -2;
}

// void	f_move_player_v2(t_data2 *data)
// {
// 	int	speed;

// 	if (!data->player.time)
// 		return ;
// 	speed = PLAYER_SPEED;
// 	if (data->running)
// 		speed = PLAYER_SPEED * 2;
// 	data->player.time -= speed;
// 	data->player.x += speed * data->player.dx;
// 	data->player.y += speed * data->player.dy;
// 	if (data->player.time == 52)
// 		data->player.f += 1;
// 	else if (data->player.time == 36)
// 		data->player.f += -1;
// 	else if (data->player.time == 20)
// 		data->player.f += 2;
// 	else if (data->player.time == 8)
// 		data->player.f += -2;
// }
///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        move all enemy. if time == 0, random what happen next
        its also the ft_save_time of the enemies
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	ft_move_enemy(t_data2 *d)
{
	int	i;
	int	random;

	i = -1;
	while (++i < d->n_pika && i < 10)
	{
		if (d->pika[i].time == -1 || d->pika[i].time == -2 || d->pika[i].x < 0)
			continue ;
		if (d->pika[i].time > 0)
			move_pika_v2(d, i);
		else
		{
			random = (rand() % (PIKA_MOVE_CHANCE + i));
			if (random < PIKA_TURN_CHANCE)
				d->pika[i].f = (random % 4) * 2;
			if (random <= 3 && d->pika[i].time != -3)
			{
				d->pika[i].dx = (int)cos(random * PI / 2);
				d->pika[i].dy = (int)sin(random * PI / 2);
				if (check_path_npc(d, d->pika[i], i) > 0)
					d->pika[i].time = 64;
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
void	move_ball(t_data2 *d)
{
	if (d->throw.ball.time < 0)
	{
		draw_circle(d, (t_circle){d->throw.ball.x + HALF, d->throw.ball.y \
			+ HALF, -d->throw.ball.time, ft_r_white});
		if (d->throw.ball.time == -5)
			d->pika[d->throw.pika_caught].x = -1;
		if (d->throw.ball.time == -1)
			d->map[(int)round((double)d->throw.ball.y / SZ)][\
				(int)round((double)d->throw.ball.x / SZ)] = 'c';
		d->throw.ball.time++;
		if (!d->throw.ball.time)
			d->tmp_bit = 1;
		return ;
	}
	d->throw.ball.x += THROW_SPEED * d->throw.ball.dx;
	d->throw.ball.y += THROW_SPEED * d->throw.ball.dy;
	if (!(d->throw.ball.time % 5))
		d->throw.ball.f = (d->throw.ball.f + 1) % 12;
	if (d->throw.ball.time == THROW_SPEED)
		d->map[(int)round((double)d->throw.ball.y / SZ)][\
			(int)round((double)d->throw.ball.x / SZ)] = 'C';
	d->throw.ball.time -= THROW_SPEED;
	if (!d->throw.ball.time)
		d->tmp_bit = 1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        if time saved > 0, move pika n*i
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void	move_pika_v2(t_data2 *data, int i)
{
	data->pika[i].time--;
	data->pika[i].x += data->pika[i].dx;
	data->pika[i].y += data->pika[i].dy;
	if (!(data->pika[i].time % (16 + i)))
		data->pika[i].f ^= 1;
}
