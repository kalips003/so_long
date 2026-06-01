/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pathing2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/02 18:19:14 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	check path for player
******************************************************************************/
static void	f_exit(t_data *data)
{
	data->walk_count++;
	put(COLOR_5R_0G_5B "You moved "COLOR_1R_4G_1B"%d"COLOR_5R_0G_5B \
			" steps\n"RESET, data->walk_count);
	put("You finished with %d moves, and got %d/%d pokeballs!\n",
		data->walk_count, data->num_collected, data->num_ball);
	exit_all(data);
}

int	check_path_player(t_data *data, int dx, int dy)
{
	int	x;
	int	y;
	int	i;

	x = data->player[0] + dx;
	y = data->player[1] + dy;
	if (data->map[y][x] == '1')
		return (0);
	if (data->map[y][x] == 'C')
	{
		data->map[y][x] = '0';
		data->num_collected++;
	}
	else if (data->map[y][x] == 'E' && data->num_collected == data->num_ball)
		f_exit(data);
	i = -1;
	while (++i < data->num_pika)
		if (data->pika[i][0] == x && data->pika[i][1] == y)
			(put("YOU DIED\n"), exit_all(data));
	return (1);
}

/*******************************************************************************
	check path for pika n'i, with input [0,1,2,3]
******************************************************************************/
int	check_path_pika(t_data *data, int i, int random)
{
	t_coor	path;
	int		j;

	path.x = data->pika[i][0] + (int)cos(random * PI / 2);
	path.y = data->pika[i][1] + (int)sin(random * PI / 2);
	if (data->map[path.y][path.x] == '1')
		return (0);
	j = -1;
	while (++j < data->num_pika)
		if (path.x == data->pika[j][0] && path.y == data->pika[j][1])
			return (0);
	if (path.x == data->player[0] && path.y == data->player[1])
		(put("YOU DIED\n"), exit_all(data));
	return (1);
}
