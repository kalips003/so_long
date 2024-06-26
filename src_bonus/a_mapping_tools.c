/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_mapping_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:06 by agallon           #+#    #+#             */
/*   Updated: 2024/06/26 16:59:58 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int			fill_map_v2(t_data2 *data, int fd_map);
int			count_check_v2(t_data2 *data);
static void	copy_posi(int *ptr, int x, int y);
static void	ft_copy_posi_pika(t_data2 *data, int x, int y, char c);
static int	small_check(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	fill map with gnl, check if rectangle
	fill map->map_x, map->map_y
	return 1 on error, with map not free
******************************************************************************/
int	fill_map_v2(t_data2 *data, int fd_map)
{
	data->map = expand_tab(NULL, gnl(fd_map));
	if (!data->map || !data->map[0])
		return (put(ERRM"some error occured (1)\n"), close(fd_map), 1);
	data->map_x = len_m(data->map[0], "\n");
	while (data->map[data->map_y])
	{
		if (len_m(data->map[data->map_y], "\n") != data->map_x)
			return (put(ERR"not a rectangle\n%.3t\n", data->map), \
					close(fd_map), 1);
		data->map_y++;
		data->map = expand_tab(data->map, gnl(fd_map));
	}
	close(fd_map);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	iterate map counting all 'EPCz' tiles
	return the value of small_check:
		verify if the values are correct
		check outer walls
	return 1 on error, with map not free
******************************************************************************/
int	count_check_v2(t_data2 *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_y)
	{
		x = -1;
		while (++x < data->map_x)
		{
			if (wii(data->map[y][x], "01CEPzZ*\n") == -1)
				return (put(ERR"unknown tile: (%c) [%d, %d]\n%.3t\n", \
							data->map[y][x], x, y, data->map), 1);
			if (data->map[y][x] == 'C')
				data->n_ball++;
			else if (data->map[y][x] == 'E')
				copy_posi(data->exit, x, y);
			else if (data->map[y][x] == 'P')
				copy_posi(&data->player.x, x, y);
			else if (data->map[y][x] == 'z' || data->map[y][x] == 'Z')
				ft_copy_posi_pika(data, x, y, data->map[y][x]);
		}
	}
	return (small_check(data));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	helper to copy posi players and exits
		ptr[2] is temporary used to count how many, reset at 0 later
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static void	copy_posi(int *ptr, int x, int y)
{
	ptr[0] = x * SZ;
	ptr[1] = y * SZ;
	ptr[2]++;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	expend the list: t_npc[pika + 1]
	also fill it, initialize it
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static void	ft_copy_posi_pika(t_data2 *data, int x, int y, char c)
{
	data->pika = (t_npc *)expand(data->pika, data->n_pika * sizeof(t_npc), \
								sizeof(t_npc));
	if (!data->pika)
		(put(ERRM"error expension\n"), exit_all_v2(data));
	data->pika[data->n_pika].x = x * SZ;
	data->pika[data->n_pika].y = y * SZ;
	data->pika[data->n_pika].f = 3;
	if (c == 'Z')
		data->pika[data->n_pika].time = -3;
	data->n_pika++;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		verify if the values are correct
		check outer walls
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static int	small_check(t_data2 *data)
{
	int	y;
	int	x;

	if (data->player.f != 1)
		return (put(ERR"none or too many player\n%.3t\n", data->map), 1);
	if (data->exit[2] != 1)
		return (put(ERR"none or too many exit\n%.3t\n", data->map), 1);
	if (data->n_ball < 1)
		return (put(ERR"no collectible\n%.3t\n", data->map), 1);
	y = 0;
	while (++y < data->map_y - 1)
		if (data->map[y][0] != '1' || data->map[y][data->map_x - 1] != '1')
			return (put(ERR"bad wall side\n%.3t\n", data->map), 1);
	x = -1;
	while (++x < data->map_x)
		if (data->map[0][x] != '1' || data->map[data->map_y - 1][x] != '1')
			return (put(ERR"bad wall top/bot\n%.3t\n", data->map), 1);
	return (0);
}
