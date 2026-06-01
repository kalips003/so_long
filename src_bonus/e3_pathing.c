/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pathing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/03 18:50:20 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int		check_path_npc(t_data2 *data, t_npc npc, int current_pika);
void	check_what_your_walking_on(t_data2 *data);
void	check_throw_path(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	check path for player && pika && ball n'i, with input [0,1,2,3]
    tree = 0;
	pika = -1;
    all good = 1;
****************************************************************/
int	check_path_npc(t_data2 *data, t_npc npc, int current_pika)
{
	int x;
	int y;
	int i;

	x = npc.x / SPRITE_SIZE + npc.dx;
	y = npc.y / SPRITE_SIZE + npc.dy;
	if (data->map[y][x] == '1')
		return (0);
	i = -1;
	while (++i < data->num_pika)
	{
		if (i == current_pika)
			continue ;
		if ((int)round(data->pika[i].x / SPRITE_SIZE) == x && (int)round(data->pika[i].y / SPRITE_SIZE) == y)
			return (-1);
	}
	return (1);
}

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	in the loop, check round(x / SPRITE) ==
****************************************************************/
void	check_what_your_walking_on(t_data2 *data)
{
	int x;
	int y;
	int i;

	x = (int)round(data->player.x / SPRITE_SIZE);
	y = (int)round(data->player.y / SPRITE_SIZE);
	if (data->map[y][x] == 'C')
	{
		data->map[y][x] = '0';
		data->num_collected = min(++data->num_collected, data->num_ball);
		data->num_holding++;
		if (data->num_collected == data->num_ball)
			data->exit[2] = 1;
	}
	if (data->map[y][x] == 'c' && ++data->num_pika_caught)
		data->map[y][x] = '0';
	else if (data->exit[0] == data->player.x && data->exit[1] == data->player.y && data->exit[2])
	{
		put(MSG_WIN"You finished with %d moves, picked up %d pokeballs and caught %d/%d mons!\n",
		data->walk_count, data->num_ball, data->num_pika_caught, data->num_pika);
		exit_all_v2(data);
	}
	i = -1;
	while (++i < data->num_pika)
		if (abs(data->pika[i].x - data->player.x) < HIT_BOX && abs(data->pika[i].y - data->player.y) < HIT_BOX)
			data->player.time = -1;
	if (data->map[y][x] == '*' && data->starter == 2)
		data->player.time = -1;
}

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	in the loop, check round(x / SPRITE) == pika, or wall
****************************************************************/
void	check_throw_path(t_data2 *data)
{
	int x;
	int y;
	int i;

	x = (int)round(data->throw.ball.x / SPRITE_SIZE);
	y = (int)round(data->throw.ball.y / SPRITE_SIZE);
	if (data->map[y][x] == '1')
	{
		data->map[y - data->throw.ball.dy][x - data->throw.ball.x] = 'C';
		data->throw.ball.time = 0;
	}
	i = -1;
	while (++i < data->num_pika)
	{
		if (data->pika[i].time >= 0 && abs(data->pika[i].x - data->throw.ball.x) < HIT_BOX && abs(data->pika[i].y - data->throw.ball.y) < HIT_BOX)
		{
			data->pika[i].time = -1;
			data->throw.pika_caught = i;
			data->throw.ball.time = -32;
			break ;
		}
	}
}
