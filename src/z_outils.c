/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_outils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/26 17:02:34 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
// exit all without the error message
static void	exit_img(t_data *data)
{
	if (data->img_ground)
		mlx_destroy_image(data->mlx, data->img_ground);
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
	if (data->img_ball)
		mlx_destroy_image(data->mlx, data->img_ball);
}

int	exit_all(t_data *data)
{
	int	i;

	free_tab(data->map);
	if (data->pika)
		free_s(data->pika);
	exit_img(data);
	i = -1;
	while (++i < 16)
	{
		if (data->img_player[i])
			mlx_destroy_image(data->mlx, data->img_player[i]);
		if (data->img_pika[i])
			mlx_destroy_image(data->mlx, data->img_pika[i]);
	}
	if (data->mlx)
	{
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

// exit all with the error message
int	exit_all_2(t_data *data, char *string)
{
	if (string)
		put("%s", string);
	exit_all(data);
	return (0);
}

void	put_map(char *txt, char **map)
{
	if (!map)
		return ;
	put("%s", txt);
	while (*map)
	{
		put("\t%S", *map);
		map++;
	}
}
