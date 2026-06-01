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
static int is_player_touched_line(int *atk_start_xy, int *atk_end_xy, int *player_xy);

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

	x = npc.x / SPRITE_SIZE + npc.dx;
	y = npc.y / SPRITE_SIZE + npc.dy;
	if (data->map[y][x] == '1' || (data->map[y][x] == '*' && data->starter == 1))
		return (0);
	i = -1;
	while (++i < data->num_pika)
	{
		if (i == current_pika)
			continue ;
		if ((int)round((double)data->pika[i].x / SPRITE_SIZE) == x && (int)round((double)data->pika[i].y / SPRITE_SIZE) == y)
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

	x = (int)round((double)data->player.x / SPRITE_SIZE);
	y = (int)round((double)data->player.y / SPRITE_SIZE);
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
		data->player.time = -1;
		data->is_winning = 1;
		// put(MSG_WIN"You finished with %d moves, picked up %d pokeballs and caught %d/%d mons!\n", \
		// 	data->walk_count, data->num_ball, data->num_pika_caught, data->num_pika);
		// exit_all_v2(data);
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
	int	x;
	int	y;
	int	i;

	x = (int)round((double)data->throw.ball.x / SPRITE_SIZE);
	y = (int)round((double)data->throw.ball.y / SPRITE_SIZE);
	if (data->map[y][x] == '1')
	{
		data->map[y - data->throw.ball.dy][x - data->throw.ball.dx] = 'C';
		data->tmp_bit = 1;
		data->throw.ball.time = 0;
	}
	i = -1;
	while (++i < data->num_pika)
	{
		if (data->pika[i].time != -1 && abs(data->pika[i].x - data->throw.ball.x) < HIT_BOX && abs(data->pika[i].y - data->throw.ball.y) < HIT_BOX)
		{
			data->pika[i].time = -1;
			data->throw.pika_caught = i;
			data->throw.ball.time = -32;
			break ;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// calculating the perpendicular distance from the player's position to the line segment
// prerequisite attack.time > 0
// static int is_player_touched(int atk_start_xy[2], int atk_end_xy[2], int player_xy[2])
static int is_player_touched_line(int *atk_start_xy, int *atk_end_xy, int *player_xy)
{
	int	step;
	int	i;
	int	x;
	int	y;

	step = max(abs(atk_end_xy[0] - atk_start_xy[0]), abs(atk_end_xy[1] - atk_start_xy[1])) / SPRITE_SIZE + 1;
	i = -1;
	while (++i <= step)
	{
		x = (int)(atk_start_xy[0] + (double)i / step * (atk_end_xy[0] - atk_start_xy[0]));
		y = (int)(atk_start_xy[1] + (double)i / step * (atk_end_xy[1] - atk_start_xy[1]));
		if ((int)distance_squared(player_xy[0] + DEMI_SPRITE, player_xy[1] + DEMI_SPRITE, x, y) < HIT_BOX * HIT_BOX)
			return (1);
	}
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
// calculating the perpendicular distance from the player's position to the line segment
// prerequisite attack.time > 0
// static int is_player_touched(int atk_start_xy[2], int atk_end_xy[2], int player_xy[2])
static int is_player_touched_sphere(int *atk_start_xy, int *atk_end_xy, int *player_xy)
{
	int	step;
	int	i;
	int	x;
	int	y;

	step = max(abs(atk_end_xy[0] - atk_start_xy[0]), abs(atk_end_xy[1] - atk_start_xy[1])) / SPRITE_SIZE + 1;
	i = -1;
	while (++i <= step)
	{
		x = (int)(atk_start_xy[0] + (double)i / step * (atk_end_xy[0] - atk_start_xy[0]));
		y = (int)(atk_start_xy[1] + (double)i / step * (atk_end_xy[1] - atk_start_xy[1]));
		if ((int)distance_squared(player_xy[0] + DEMI_SPRITE, player_xy[1] + DEMI_SPRITE, x, y) < HIT_BOX * HIT_BOX)
			return (1);
	}
	return (0);
}