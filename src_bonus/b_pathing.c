/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pathing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/03 18:50:20 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/***************************************************************
	check if current '*' is exit (return 1)
	check 4 directions (return 0)
****************************************************************/
static int	check_cardinal(t_data2 *data, char **map)
{
	if (data->ptr[0] == data->exit[0] && data->ptr[1] == data->exit[1])
		return (1);
	map[data->ptr[1]][data->ptr[0]] = '1';
	if (map[data->ptr[1] + 1][data->ptr[0]] != '1')
		map[data->ptr[1] + 1][data->ptr[0]] = '*';
	if (map[data->ptr[1]][data->ptr[0] + 1] != '1')
		map[data->ptr[1]][data->ptr[0] + 1] = '*';
	if (map[data->ptr[1] - 1][data->ptr[0]] != '1')
		map[data->ptr[1] - 1][data->ptr[0]] = '*';
	if (map[data->ptr[1]][data->ptr[0] - 1] != '1')
		map[data->ptr[1]][data->ptr[0] - 1] = '*';
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
				data->ptr[0] = x;
				data->ptr[1] = y;
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
int	valid_path(t_data2 *data)
{
	char	**map_path;
	int		y;

	map_path = (char **)malloc(sizeof(char *) * (data->map_y + 1));
	if (!map_path)
		return (put("error malloc 2\n"), 1);
	y = -1;
	while (++y < data->map_y)
	{
		map_path[y] = str("%1s", data->map[y]);
		if (!map_path[y])
			return (put("error malloc 3\n"), free_tab(map_path), exit_all(data),
				1);
	}
	map_path[y] = NULL;
	map_path[data->player[1]][data->player[0]] = '*';
	while (find_next_to_explore(data, map_path))
	{
		if (check_cardinal(data, map_path))
			return (free_tab(map_path), 0);
	}
	return (free_tab(map_path), 1);
}


/***************************************************************
	check path for player
****************************************************************/
int check_path_player(t_data2 *data, int dx, int dy)
{
    int x;
    int y;
    int i;

    x = data->player[0] / SPRITE_SIZE + dx;
    y = data->player[1] / SPRITE_SIZE + dy;
    if (data->map[y][x] == '1')
        return (0);
    if (data->map[y][x] == 'C')
    {
        data->map[y][x] = '0';
        data->num_collected++;
    }
    else if (data->map[y][x] == 'E')
    {
        put("You finished with %d moves, and got %d/%d pokeballs!\n", data->walk_count, data->num_collected, data->num_ball);
        exit_all(data);
    }
    i = -1;
    while (++i < data->num_pika)
        if (data->pika[i][0] == x && data->pika[i][1] == y)
            (put("YOU DIED\n"), exit_all(data));
    return (1);
}

/***************************************************************
	check path for pika n'i, with input [0,1,2,3]
****************************************************************/
int check_path_pika(t_data2 *data, int i, int random)
{
    t_coor  path;
    int     j;

    path.x = data->pika[i][0] + (int)cos(random * PI / 2);
    path.y = data->pika[i][1] + (int)sin(random * PI / 2);
    if (data->map[path.y / SPRITE_SIZE][path.x / SPRITE_SIZE] == '1')
        return (0);
    j = -1;
    while (++j < data->num_pika)
        if (path.x == data->pika[j][0] && path.y == data->pika[j][1])
            return (0);
    if (path.x == data->player[0] && path.y == data->player[1])
        (put("YOU DIED\n"), exit_all(data));
    return (1);
}
