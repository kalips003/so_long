/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_moving_parts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/02 18:14:40 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
static void	f_save_time_player(t_data *data, int dx, int dy, int frame)
{
	if (data->player[2] != frame)
		data->player[2] = frame;
	else if (check_path_player(data, dx, dy))
	{
		data->player_time = data->time_frame;
		data->walk_count++;
		put(COLOR_5R_0G_5B "You moved "COLOR_1R_4G_1B"%d"COLOR_5R_0G_5B \
			" steps\n"RESET, data->walk_count);
	}
}

///////////////////////////////////////////////////////////////////////////////]
int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit_all(data);
	if (data->player[2] % 4 || data->player_time != -1)
	{
		return (0);
	}
	if (keysym == XK_w || keysym == XK_Up)
		f_save_time_player(data, 0, -1, 12);
	else if (keysym == XK_d || keysym == XK_Right)
		f_save_time_player(data, 1, 0, 0);
	else if (keysym == XK_s || keysym == XK_Down)
		f_save_time_player(data, 0, 1, 4);
	else if (keysym == XK_a || keysym == XK_Left)
		f_save_time_player(data, -1, 0, 8);
	else if (keysym == XK_space)
		data->is_dying = 1;
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
void	f_move_player(t_data *data)
{
	if (data->time_frame == (data->player_time + ANIM_1) % TIME_F)
	{
		if (data->player[2] == 12)
			data->player[1] += -1;
		else if (data->player[2] == 8)
			data->player[0] += -1;
		data->player[2]++;
	}
	else if (data->time_frame == (data->player_time + 2 * ANIM_T) % TIME_F)
		data->player[2]++;
	else if (data->time_frame == (data->player_time + 3 * ANIM_T) % TIME_F)
		data->player[2]++;
	else if (data->time_frame == (data->player_time + 4 * ANIM_T) % TIME_F)
	{
		if (data->player[2] == 3)
			data->player[0] += 1;
		else if (data->player[2] == 7)
			data->player[1] += 1;
		data->player[2] -= 3;
		data->player_time = -1;
	}
}

///////////////////////////////////////////////////////////////////////////////]
void	f_move_pika(t_data *data)
{
	int	i;
	int	random;

	i = -1;
	while (++i < data->num_pika)
	{
		if (data->pika_time[i] >= 0)
			anim_pika(data, i);
		else
		{
			random = (rand() % (MAX_CHANCE + 1));
			if (random <= 7)
				data->pika[i][2] = (random % 4) * 4;
			if (random <= 3 && check_path_pika(data, i, random))
				data->pika_time[i] = data->time_frame;
		}
	}
}

void	anim_pika(t_data *data, int i)
{
	if (data->time_frame == (data->pika_time[i] + ANIM_1) % TIME_F)
	{
		if (data->pika[i][2] == 12)
			data->pika[i][1] += -1;
		else if (data->pika[i][2] == 8)
			data->pika[i][0] += -1;
		data->pika[i][2]++;
	}
	else if (data->time_frame == (data->pika_time[i] + 2 * ANIM_T) % TIME_F)
		data->pika[i][2]++;
	else if (data->time_frame == (data->pika_time[i] + 3 * ANIM_T) % TIME_F)
		data->pika[i][2]++;
	else if (data->time_frame == (data->pika_time[i] + 4 * ANIM_T) % TIME_F)
	{
		if (data->pika[i][2] == 3)
			data->pika[i][0] += 1;
		else if (data->pika[i][2] == 7)
			data->pika[i][1] += 1;
		data->pika[i][2] -= 3;
		data->pika_time[i] = -1;
	}
}
