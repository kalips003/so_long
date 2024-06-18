/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_attack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:14 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 16:54:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void check_attack(t_data2 *data);
static void	render_attack(t_data2 *data);
static void	find_pika_for_attak(t_data2 *data);
static int is_player_touched(int *atk_start_xy, int *atk_end_xy, int *player_xy);
static int  helper_find_closest(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
// 	ATTAK BALL
void	is_player_touched_v2(t_data2 *data)
{

}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	main loop fuction for the attak
	decide each loop if a pika shall attak
	if there is an attack ongoing, check if player touched
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	check_attack(t_data2 *data)
{
	int random;

	if (!data->attack.time)
	{
		random = rand() % ATTACK_CHANCE;
		if (!random)
			find_pika_for_attak(data);
		if (!data->attack.time)
			return ;
	}
	if (data->attack.time > 0 && is_player_touched(&data->attack.circle.center_x, &data->attack.circlend.center_x, &data->player.x))
		data->player.time = -1;
	render_attack(data);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    render_attack, advance time of the atk
    burns the ground at the end (time == 1)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void	render_attack(t_data2 *data)
{
	t_attack	*atk;

	atk = &data->attack;
	if (atk->time == -1)
	{
		data->map[(int)(atk->circlend.center_y / SPRITE_SIZE)] \
				[(int)(atk->circlend.center_x / SPRITE_SIZE)] = '*';
		data->pika[atk->pika_attaking].time = -2;
		atk->time = ATTAK_TIME;
	}
	else if (atk->time == 1)
	{
		data->pika[atk->pika_attaking].time = 0;
		data->tmp_bit = 1;
	}
	if (atk->time < 0)
	{
		atk->circlend.radius = -data->attack.time / 8;
		atk->circle.radius = -data->attack.time / 6;
		// atk->circle.radius = -(CHANNELING_TIME - data->attack.time) / 4;
		draw_circle(data, atk->circle);
		draw_circle(data, atk->circlend);
	}
	else
	{
		draw_line_v4(data, &atk->circle.center_x, &atk->circlend.center_x, data->color_r);
	}
	atk->time += 1 - 2 * (atk->time > 0);
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    find closest pika available,
    if it exist, fill attack struct
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void find_pika_for_attak(t_data2 *data)
{
	int i;
	double angle;

	i = helper_find_closest(data);
	if (i < 0)
		return ;
	data->attack.pika_attaking = i;
	data->attack.circle.center_x = data->pika[i].x + DEMI_SPRITE - 1;
	data->attack.circle.center_y = data->pika[i].y + DEMI_SPRITE - 1;
	data->attack.circle.color = data->color_r;
	data->attack.circlend.center_x = data->player.x + DEMI_SPRITE - 1;
	data->attack.circlend.center_y = data->player.y + DEMI_SPRITE - 1;
	data->attack.circlend.color = data->color_r;
	data->pika[i].time = -1;
	angle = atan2(data->player.y - data->pika[i].y, data->player.x - data->pika[i].x);
	if (angle < 0)
		angle += 2 * PI;
	data->pika[i].f = ((int)round(angle / (PI / 2)) % 4) * 2;
	data->attack.time = CHANNELING_TIME;
}

// return the n*i of the closest pika
static int  helper_find_closest(t_data2 *data)
{
	int i;
	int dist;
	int saved_smallest;
	int saved_pika;

	saved_smallest = INT_MAX;
	i = -1;
	while (++i < data->num_pika)
	{
		if (data->pika[i].x < 0 || data->pika[i].time)
			continue ;
		dist = abs(data->player.x - data->pika[i].x) + abs(data->player.y - data->pika[i].y);
		if (dist < saved_smallest)
		{
			saved_smallest = dist;
			saved_pika = i;
		}
	}
	if (saved_smallest == INT_MAX)
		return (-1);
	else
		return (saved_pika);
}
// Function to calculate the distance squared between two points
static double	distance_squared(int x1, int y1, int x2, int y2)
{

	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

///////////////////////////////////////////////////////////////////////////////]
// calculating the perpendicular distance from the player's position to the line segment
// prerequisite attack.time > 0
// static int is_player_touched(int atk_start_xy[2], int atk_end_xy[2], int player_xy[2])
static int is_player_touched(int *atk_start_xy, int *atk_end_xy, int *player_xy)
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
		int dist_sq = (int)distance_squared(player_xy[0] + DEMI_SPRITE, player_xy[1] + DEMI_SPRITE, x, y);
		if ((int)distance_squared(player_xy[0] + DEMI_SPRITE, player_xy[1] + DEMI_SPRITE, x, y) < HIT_BOX * HIT_BOX)
			return (1);
	}
	return (0);
}