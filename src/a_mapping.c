/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_mapping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:06 by agallon           #+#    #+#             */
/*   Updated: 2024/06/26 17:02:19 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/***************************************************************
	fill map with gnl, check if rectangle
	return 1 on error, with map free
	fill map->map_x, map->map_y
****************************************************************/
int	fill_map(t_data *data, int fd_map)
{
	data->map = expand_tab(NULL, gnl(fd_map));
	if (!data->map || !data->map[0])
	{
		put(ERRM"some error occured (1)\n");
		data->map = free_tab(data->map);
		return (close(fd_map), 1);
	}
	data->map_x = len_m(data->map[0], "\n");
	while (data->map[data->map_y])
	{
		if (len_m(data->map[data->map_y], "\n") != data->map_x)
		{
			put_map(ERR"not a rectangle\n", data->map);
			data->map = free_tab(data->map);
			return (close(fd_map), 1);
		}
		data->map_y++;
		data->map = expand_tab(data->map, gnl(fd_map));
	}
	close(fd_map);
	return (0);
}

/***************************************************************
	fill num_ball, num_exit, num_start
	return 1 on error, with map not free
****************************************************************/
static void	copy_posi(int *ptr, int x, int y)
{
	ptr[0] = x;
	ptr[1] = y;
	ptr[2]++;
}

static void	ft_posi_pika(t_data *data, int x, int y)
{
	data->pika = (int (*)[3])
		expand(data->pika, data->num_pika * sizeof(int [3]), sizeof(int [3]));
	if (!data->pika)
		(put("error expension\n"), exit_all(data));
	data->pika[data->num_pika][0] = x;
	data->pika[data->num_pika][1] = y;
	data->pika[data->num_pika][2] = 4;
	data->num_pika++;
}

static int	small_check(t_data *data)
{
	int	y;
	int	x;

	if (data->player[2] != 1)
		return (put_map(ERR"none or too many player\n", data->map), 1);
	if (data->exit[2] != 1)
		return (put_map(ERR"none or too many exit\n", data->map), 1);
	if (data->num_ball < 1)
		return (put_map(ERR"no collectible\n", data->map), 1);
	y = 0;
	while (++y < data->map_y - 1)
		if (data->map[y][0] != '1' || data->map[y][data->map_x - 1] != '1')
			return (put_map(ERR"bad wall side\n", data->map), 1);
	x = -1;
	while (++x < data->map_x)
		if (data->map[0][x] != '1' || data->map[data->map_y - 1][x] != '1')
			return (put_map(ERR"bad wall top/bot\n", data->map), 1);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
int	count_check(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_y)
	{
		x = -1;
		while (++x < data->map_x)
		{
			if (wii(data->map[y][x], "01CEPz\n") == -1)
				return (put(ERR "unknown tile %c: [%d, %d]\n", \
					data->map[y][x], x, y), put_map("", data->map), 1);
			if (data->map[y][x] == 'C')
				data->num_ball++;
			else if (data->map[y][x] == 'E')
				copy_posi(data->exit, x, y);
			else if (data->map[y][x] == 'P')
				copy_posi(data->player, x, y);
			else if (data->map[y][x] == 'z')
				ft_posi_pika(data, x, y);
		}
	}
	return (small_check(data));
}
