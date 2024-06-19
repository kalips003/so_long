/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e3_pathing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:40 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 16:54:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int		check_path_npc(t_data2 *data, t_npc npc, int current_pika);
void	check_what_your_walking_on(t_data2 *data);
void	check_throw_path(t_data2 *data);
int		is_touched(int *atk_start_xy, int *atk_end_xy, int *player_xy);

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	check path for player && pika && ball n'i, with input [0,1,2,3]
    tree = 0;
	pika = -1;
    all good = 1;
****************************************************************/
int	check_path_npc(t_data2 *data, t_npc npc, int current_pika)
{
	int	x;
	int	y;
	int	i;

	x = npc.x / SZ + npc.dx;
	y = npc.y / SZ + npc.dy;
	if (data->map[y][x] == '1' || (data->map[y][x] == '*' && \
			data->starter == 1))
		return (0);
	i = -1;
	while (++i < data->n_pika)
	{
		if (i == current_pika)
			continue ;
		if ((int)round((double)data->pika[i].x / SZ) == x && \
				(int)round((double)data->pika[i].y / SZ) == y)
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
	int	x;
	int	y;
	int	i;

	x = (int)round((double)data->player.x / SZ);
	y = (int)round((double)data->player.y / SZ);
	if (data->map[y][x] == 'C' && ++data->n_hold)
	{
		data->map[y][x] = '0';
		data->n_collec = min(++data->n_collec, data->n_ball);
		if (data->n_collec == data->n_ball)
			data->exit[2] = 1;
	}
	if (data->map[y][x] == 'c' && ++data->n_gotta)
		data->map[y][x] = '0';
	else if (data->exit[0] == data->player.x && data->exit[1] == \
		data->player.y && data->exit[2] && ++data->is_winning)
		data->player.time = -1;
	i = -1;
	while (++i < data->n_pika)
		if (abs(data->pika[i].x - data->player.x) < HIT_BOX && \
			abs(data->pika[i].y - data->player.y) < HIT_BOX)
			data->player.time = -1;
	if (data->map[y][x] == '*' && data->starter == 2)
		data->player.time = -1;
}

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	in the loop, check round(x / SPRITE) == pika, or wall
****************************************************************/
void	check_throw_path(t_data2 *d)
{
	int	x;
	int	y;
	int	i;

	x = (int)round((double)d->throw.ball.x / SZ);
	y = (int)round((double)d->throw.ball.y / SZ);
	if (d->map[y][x] == '1')
	{
		d->map[y - d->throw.ball.dy][x - d->throw.ball.dx] = 'C';
		d->tmp_bit = 1;
		d->throw.ball.time = 0;
	}
	i = -1;
	while (++i < d->n_pika)
	{
		if (d->pika[i].time != -1 && abs(d->pika[i].x - d->throw.ball.x) \
			< HIT_BOX && abs(d->pika[i].y - d->throw.ball.y) < HIT_BOX)
		{
			d->pika[i].time = -1;
			d->throw.pika_caught = i;
			d->throw.ball.time = -32;
			break ;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// sampling points on the line segment, 
//  	check distance from the player's position
// prerequisite attack.time > 0
int	is_touched(int *start, int *end, int *player_xy)
{
	int	step;
	int	i;
	int	x;
	int	y;

	step = max(abs(end[0] - start[0]), abs(end[1] - start[1])) / SZ + 1;
	i = -1;
	while (++i <= step)
	{
		x = (int)(start[0] + (double)i / step * (end[0] - start[0]));
		y = (int)(start[1] + (double)i / step * (end[1] - start[1]));
		if ((int)distance_squared(player_xy[0] + HALF, player_xy[1] + \
			HALF, x, y) < HIT_BOX * HIT_BOX)
			return (1);
	}
	return (0);
}
