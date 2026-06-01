/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_path_finding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/09 19:28:09 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
    create map, free it in all cases
    do all the tests, exit in case of any error
*******************************************************************************/
void is_map_ok_v2(t_data2 *data, char *path)
{
    int fd_map;

    ft_memset(data, 0, sizeof(t_data2));
// map path end in ".ber"
    if (find_str(path, ".ber") != len(path) - 4)
        (put(ERR"bad argument\n"), exit(1));
// create map struct
    fd_map = open(path, O_RDONLY);
    if (fd_map == -1)
        (perror(ERR"open"), exit(1));
// fill map
    if (fill_map_v2(data, fd_map) || count_check_v2(data))
		exit_all_v2(data);
// valid path?
    if (valid_path_v2(data))
        (put(ERR"bad pathing\n%.3t\n", data->map), exit_all_v2(data));
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		create copy of map for path finding, free it in all cases
		if no path, return 1, struct not free
*******************************************************************************/
/***************************************************************
	check if current '*' is exit (return 1)
	check 4 directions (return 0)
****************************************************************/
static int	check_cardinal(t_data2 *data, char **map)
{
	if (data->exit[3] == data->exit[0] / SPRITE_SIZE && data->exit[4] == data->exit[1] / SPRITE_SIZE)
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

/***************************************************************
	parse map to find next to explore ('*')
	if no more '*', return 0
****************************************************************/
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

///////////////////////////////////////////////////////////////////////////////]
int	valid_path_v2(t_data2 *data)
{
	char	**map_path;
	int		y;

	map_path = (char **)malloc(sizeof(char *) * (data->map_y + 1));
	if (!map_path)
		return (put(ERRM"error malloc (2)\n"), 1);
	y = -1;
	while (++y < data->map_y)
	{
		map_path[y] = str("%1s", data->map[y]);
		if (!map_path[y])
			return (put(ERRM"error malloc (3)\n"), free_tab(map_path), exit_all_v2(data), 1);
	}
	map_path[y] = NULL;
	map_path[data->player.y / SPRITE_SIZE][data->player.x / SPRITE_SIZE] = '*';
	while (find_next_to_explore(data, map_path))
	{
		if (check_cardinal(data, map_path))
			return (free_tab(map_path), 0);
	}
	return (free_tab(map_path), 1);
}

