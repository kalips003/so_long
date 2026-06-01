/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_path_finding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/26 17:00:10 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int			valid_path_v2(t_data2 *data);
static int	check_cardinal(t_data2 *data, char **map);
static int	find_next_to_explore(t_data2 *data, char **map_path);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		create copy of map for path finding, free it in all cases
			if no path, return 1
			ditto map free in all cases
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////]
int	valid_path_v2(t_data2 *data)
{
	char	**map_path;
	int		y;

	map_path = (char **)malloc(sizeof(char *) * (data->map_y + 1));
	if (!map_path)
		return (put(ERRM"error malloc (2)\n"), exit_all_v2(data));
	y = -1;
	while (++y < data->map_y)
	{
		map_path[y] = str("%1s", data->map[y]);
		if (!map_path[y])
			return (put(ERRM"error malloc (3)\n"), free_tab(map_path), 1);
	}
	map_path[y] = NULL;
	map_path[data->player.y / SZ][data->player.x / SZ] = '*';
	while (find_next_to_explore(data, map_path))
	{
		if (check_cardinal(data, map_path))
			return (free_tab(map_path), 0);
	}
	return (put(ERR"bad pathing\n%.3t\n", data->map), free_tab(map_path), 1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	check if current '*' is exit (return 1)
	mark 4 directions with '*' (return 0)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static int	check_cardinal(t_data2 *data, char **map)
{
	if (data->exit[3] == data->exit[0] / SZ && \
		data->exit[4] == data->exit[1] / SZ)
		return (1);
	map[data->exit[4]][data->exit[3]] = '1';
	if (map[data->exit[4] + 1][data->exit[3]] != '1')
		map[data->exit[4] + 1][data->exit[3]] = '*';
	if (map[data->exit[4]][data->exit[3] + 1] != '1')
		map[data->exit[4]][data->exit[3] + 1] = '*';
	if (map[data->exit[4] - 1][data->exit[3]] != '1')
		map[data->exit[4] - 1][data->exit[3]] = '*';
	if (map[data->exit[4]][data->exit[3] - 1] != '1')
		map[data->exit[4]][data->exit[3] - 1] = '*';
	return (0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	parse map to find next to explore ('*')
	if no more '*', return 0
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static int	find_next_to_explore(t_data2 *data, char **map_path)
{
	int	y;
	int	x;

	y = 0;
	while (++y < data->map_y - 1)
	{
		x = 0;
		while (++x < data->map_x - 1)
		{
			if (map_path[y][x] == '*')
			{
				data->exit[3] = x;
				data->exit[4] = y;
				return (1);
			}
		}
	}
	return (0);
}
