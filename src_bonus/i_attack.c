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

void			check_attack(t_data2 *data);
static void		render_attack(t_data2 *data);
static void		render_attack_v2(t_data2 *data);
static void		find_pika_for_attak_v2(t_data2 *data);
static int		helper_find_closest(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	main loop fuction for the attak
	decide each loop if a pika shall attak
	if there is an attack ongoing, check if player touched
	2 types of attak
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	check_attack(t_data2 *data)
{
	int	random;

	if (!data->attack.time)
	{
		random = rand() % ATTACK_CHANCE;
		if (!random)
			find_pika_for_attak_v2(data);
		if (!data->attack.time)
			return ;
	}
	if (data->starter == 0 || data->starter == 3)
	{
		if (data->attack.time > 0 && is_touched(&data->attack.circle.x, \
			&data->attack.circlend.x, &data->player.x))
			data->player.time = -1;
		render_attack(data);
	}
	else
	{
		if (abs(data->attack.circle.x - HALF - data->player.x) < HIT_BOX && \
			abs(data->attack.circle.y - HALF - data->player.y) < HIT_BOX)
			data->player.time = -1;
		ft_1(data);
		render_attack_v2(data);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    render_attack, advance time of the atk
    burns the ground at the end (time == 1)
	render the ray
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void	render_attack(t_data2 *data)
{
	t_attack	*atk;
	int			i;

	atk = &data->attack;
	if (atk->time == -1)
	{
		data->map[(int)(atk->circlend.y / SZ)] \
				[(int)(atk->circlend.x / SZ)] = '*';
		data->pika[atk->enemy].time = -2;
		atk->time = ATTAK_TIME;
	}
	else if (atk->time == 1 && ++data->tmp_bit)
		data->pika[atk->enemy].time = 0;
	if (atk->time < 0)
	{
		atk->circlend.rad = 20;
		atk->circle.rad = -data->attack.time / 2 - 5;
		draw_circle_v2(data, atk->circle, 0);
		i = -1;
		while (++i < 3 && atk->circlend.rad++)
			draw_circle(data, atk->circlend);
	}
	else if (data->time % 2)
		draw_line_v4(data, &atk->circle.x, &atk->circlend.x, data->color_r);
	atk->time += 1 - 2 * (atk->time > 0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    render_attack, advance time of the atk
    burns the ground at the end (time == 1)
	render the sphere
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void	render_attack_v2(t_data2 *data)
{
	t_attack	*atk;

	atk = &data->attack;
	if (atk->time == -1)
	{
		data->pika[atk->enemy].time = -2;
		atk->time = ATTAK_TIME_2;
	}
	else if (atk->time == 1 && ++data->tmp_bit)
	{
		data->map[(int)(atk->circlend.y / SZ)] \
				[(int)(atk->circlend.x / SZ)] = '*';
		data->pika[atk->enemy].time = 0;
	}
	if (atk->time > 0)
	{
		atk->circle.x += atk->dx;
		atk->circle.y += atk->dy;
		draw_frame(data, data->i_throw, (int [4]){atk->circle.x, \
			atk->circle.y, 0, 1}, data->color_r);
	}
	if (atk->time)
		atk->time += 1 - 2 * (atk->time > 0);
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    find closest pika available,
    if it exist, fill attack struct
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void	find_pika_for_attak_v2(t_data2 *d)
{
	int		i;
	double	angle;

	i = helper_find_closest(d);
	if (i < 0)
		return ;
	d->attack.enemy = i;
	d->attack.circle.x = d->pika[i].x + HALF - 1;
	d->attack.circle.y = d->pika[i].y + HALF - 1;
	d->attack.circle.color = d->color_r;
	d->attack.circlend.x = d->player.x + HALF - 1;
	d->attack.circlend.y = d->player.y + HALF - 1;
	d->attack.circlend.color = d->color;
	d->pika[i].time = -1;
	angle = atan2(d->player.y - d->pika[i].y, d->player.x - d->pika[i].x);
	if (angle < 0)
		angle += 2 * PI;
	d->pika[i].f = ((int)round(angle / (PI / 2)) % 4) * 2;
	d->attack.dx = (int)(((double)d->player.x - d->pika[i].x) / SZ);
	d->attack.dy = (int)(((double)d->player.y - d->pika[i].y) / SZ);
	d->attack.time = CHANNELING_TIME + 10 * d->starter;
}

// return the n*i of the closest pika
static int	helper_find_closest(t_data2 *d)
{
	int	i;
	int	di;
	int	saved_smallest;
	int	saved_pika;

	saved_smallest = INT_MAX;
	i = -1;
	while (++i < d->n_pika)
	{
		if (d->pika[i].x < 0 || d->pika[i].time)
			continue ;
		di = abs(d->player.x - d->pika[i].x) + abs(d->player.y - d->pika[i].y);
		if (di < saved_smallest)
		{
			saved_smallest = di;
			saved_pika = i;
		}
	}
	if (saved_smallest == INT_MAX)
		return (-1);
	else
		return (saved_pika);
}
