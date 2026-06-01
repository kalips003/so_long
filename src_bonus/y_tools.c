/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:48:08 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/26 17:29:58 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	is_map_ok_v2(t_data2 *data, char *path);
void	what_starter(t_data2 *data);
void	boy_or_girl(t_data2 *data);
double	distance_squared(int x1, int y1, int x2, int y2);
void	ft_1(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
void	what_starter(t_data2 *data)
{
	srand(time(NULL));
	data->starter = (int)(rand() % 4);
	if (data->starter == 0)
	{
		data->color = ft_yellow;
		data->color_r = ft_r_yellow;
	}
	else if (data->starter == 1)
	{
		data->color = ft_green;
		data->color_r = ft_r_green;
	}
	else if (data->starter == 2)
	{
		data->color = ft_red;
		data->color_r = ft_r_red;
	}
	else
	{
		data->color = ft_blue;
		data->color_r = ft_r_blue;
	}
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void	boy_or_girl(t_data2 *data)
{
	char	*answer;

	put(COLOR_3R_2G_5B"\n\tAre you a 'boy' or a 'girl'?: "RESET);
	answer = gnl(0);
	if (find_str(answer, "boy") >= 0)
		data->boy_or_girl = 0;
	else if (find_str(answer, "girl") >= 0)
		data->boy_or_girl = 1;
	else
		data->boy_or_girl = 2;
	free_s(answer);
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		MEMSET DATA
	create map, free it in all cases
	do all the tests, exit in case of any error
******************************************************************************/
void	is_map_ok_v2(t_data2 *data, char *path)
{
	int	fd_map;

	ft_memset(data, 0, sizeof(t_data2));
	if (find_str(path, ".ber") != len(path) - 4)
		(put(ERRM"map name should end with \'.ber\'\n"), exit(1));
	fd_map = open(path, O_RDONLY);
	if (fd_map == -1)
		(perror(ERRM"open"), exit(1));
	if (fill_map_v2(data, fd_map) || count_check_v2(data))
		exit_all_v2(data);
	if (valid_path_v2(data))
		exit_all_v2(data);
}

// Function to calculate the distance squared between two points
double	distance_squared(int x1, int y1, int x2, int y2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Helper check attack ball walls
void	ft_1(t_data2 *data)
{
	int	x;
	int	y;

	x = (int)round((double)data->attack.circle.x / SZ);
	y = (int)round((double)data->attack.circle.y / SZ);
	if (data->map[y][x] == '1')
	{
		data->map[y][x] = '*';
		data->tmp_bit = 1;
		data->attack.time = 0;
		data->pika[data->attack.enemy].time = 0;
	}
}
