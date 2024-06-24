/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pathing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/24 21:21:03 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/***************************************************************
	create map, free it in all cases
	do all the tests, exit in case of any error
****************************************************************/
void	is_map_ok(t_data *data, char *path)
{
	int	fd_map;

	ft_memset(data, 0, sizeof(t_data));
	if (find_str(path, ".ber") != len(path) - 4)
		return (put(ERR "bad argument: %s\n", path), exit(1));
	fd_map = open(path, O_RDONLY);
	if (fd_map == -1)
		return (perror("open"), exit(1));
	if (fill_map(data, fd_map) || count_check(data))
		exit_all(data);
	if (valid_path(data))
		(put_map(ERR "bad pathing\n", data->map), exit_all(data));
}

/***************************************************************
	check if current '*' is exit (return 1)
	check 4 directions (return 0)
****************************************************************/
static void	check_cardinal2(t_data *data, t_valid_path *path)
{
	int	x;
	int	y;

	if (path->x == data->exit[0] && path->y == data->exit[1])
		path->how_many++;
	path->map[path->y][path->x] = '1';
	path->i = -1;
	while (++path->i < 4)
	{
		y = path->y + cos(path->i * PI / 4);
		x = path->x + sin(path->i * PI / 4);
		if (path->map[y][x] == 'C')
			path->how_many++;
		if (path->map[y][x] != '1')
			path->map[y][x] = '*';
	}
}

/***************************************************************
	parse map to find next to explore ('*')
	if no more '*', return 0
****************************************************************/
static int	find_next_to_explore2(t_data *data, t_valid_path *path)
{
	int	y;
	int	x;

	y = 0;
	while (++y < data->map_y - 1)
	{
		x = 0;
		while (++x < data->map_x - 1)
		{
			if (path->map[y][x] == '*')
			{
				path->x = x;
				path->y = y;
				return (1);
			}
		}
	}
	return (0);
}

/***************************************************************
	create copy of map for path finding, free it in all cases
	if no path, return 1, struct not free
****************************************************************/
int	valid_path(t_data *data)
{
	t_valid_path	path;

	path.map = (char **)malloc(sizeof(char *) * (data->map_y + 1));
	if (!path.map)
		return (put("error malloc 2\n"), 1);
	path.i = -1;
	while (++path.i < data->map_y)
	{
		path.map[path.i] = str("%1s", data->map[path.i]);
		if (!path.map[path.i])
			return (put("error malloc 3\n"), free_tab(path.map), exit_all(data),
				1);
	}
	path.map[path.i] = NULL;
	path.map[data->player[1]][data->player[0]] = '*';
	path.how_many = 0;
	while (find_next_to_explore2(data, &path) && path.how_many < data->num_ball
		+ 1)
		check_cardinal2(data, &path);
	if (path.how_many != data->num_ball + 1)
		return (free_tab(path.map), 1);
	return (free_tab(path.map), 0);
}
