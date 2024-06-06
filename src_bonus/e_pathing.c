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

#include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	check path for player && pika n'i, with input [0,1,2,3]
    player == 0;
    pika <= 0;
****************************************************************/
int check_path_player_v2(t_data2 *data, int n0123, int *npc[4], int current_pika)
{
    int x;
    int y;
    int i;

    x = *npc[0] / SPRITE_SIZE + (int)cos(n0123 * PI / 2);
    y = *npc[1] / SPRITE_SIZE + (int)sin(n0123 * PI / 2);
    if (data->map[y][x] == '1')
        return (0);
    i = -1;
    while (++i < data->num_pika)
    {
        if (i == current_pika)
            continue ;
        if (round(data->pika[i][0] / SPRITE_SIZE) == x && round(data->pika[i][1] / SPRITE_SIZE) == y)
            return (-1);
    }
    return (1);
}

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	in the loop, check round(x / SPRITE) == 
****************************************************************/
void    check_what_your_walking_on(t_data2 *data)
{
    int x;
    int y;
    int i;

    x = (int)round(data->player[0] / SPRITE_SIZE);
    y = (int)round(data->player[1] / SPRITE_SIZE);
    if (data->map[y][x] == 'C')
    {
        data->map[y][x] = '0';
        data->num_collected++;
        data->num_holding++;
		if (data->num_collected == data->num_ball)
			data->is_all_collected = 1;
    }
    if (data->map[y][x] == 'c' && ++data->num_pika_caught)
        data->map[y][x] = '0';
    else if (data->exit[0] == data->player[0] && data->exit[1] == data->player[1] && data->is_all_collected)
    {
        put(MSG_WIN"You finished with %d moves, and got %d/%d pokeballs!\n", data->walk_count, data->num_collected, data->num_ball);
        exit_all_v2(data);
    }
    i = -1;
    while (++i < data->num_pika)
        if (abs(data->pika[i][0] - data->player[0]) < HIT_BOX && abs(data->pika[i][1] - data->player[1]) < HIT_BOX)
            data->player[3] = -1;
}

///////////////////////////////////////////////////////////////////////////////]
/***************************************************************
	in the loop, check round(x / SPRITE) == pika, or wall
****************************************************************/
void check_ball_throw_path(t_data2 *data)
{
    int x;
    int y;
    int i;
    
    if (data->ball_throw.time <= 0)
        return ;
    x = round((data->ball_throw.x - OFFSET_BALL_THR) / SPRITE_SIZE);
    y = round((data->ball_throw.y - OFFSET_BALL_THR) / SPRITE_SIZE);
    if (data->map[y][x] == '1')
    {
        data->map[y - (int)sin(data->ball_throw.n0123 * PI / 2)][x - (int)cos(data->ball_throw.n0123 * PI / 2)] = 'C';
        data->ball_throw.time = 0;
    }
    i = -1;
    while (++i < data->num_pika)
    {
        if (round(data->pika[i][0] / SPRITE_SIZE) == x && round(data->pika[i][1] / SPRITE_SIZE) == y)
        {
            data->pika[i][3] = -1;
            data->ball_throw.pika_caught = i;
            data->ball_throw.time = -32;
            break ;
        }
    }
}
