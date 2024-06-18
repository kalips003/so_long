/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/16 13:02:10 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
int	render(t_data *data)
{
	data->time_frame = (data->time_frame + 1) % TIME_F;
	if (data->player_time >= 0)
		f_move_player(data);
	f_move_pika(data);
	put_background(data);
	put_foreground(data);
	return (0);
}

void	put_background(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_y)
	{
		x = -1;
		while (++x < data->map_x)
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->img_wall,
					data->wid * x, data->hei * y);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'P'
				|| data->map[y][x] == 'z')
				mlx_put_image_to_window(data->mlx, data->win, data->img_ground,
					data->wid * x, data->hei * y);
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->img_ball,
					data->wid * x, data->hei * y);
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->img_exit,
					data->wid * x, data->hei * y);
		}
	}
}

void	put_foreground(t_data *data)
{
	int	i;

	mlx_put_image_to_window(data->mlx, data->win,
		data->img_player[data->player[2]], data->player[0] * data->wid,
		data->player[1] * data->hei);
	i = -1;
	while (++i < data->num_pika)
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_pika[data->pika[i][2]], data->pika[i][0] * data->wid,
			data->pika[i][1] * data->hei);
	}
}

///////////////////////////////////////////////////////////////////////////////]
static void	ini_anim(t_data *data)
{
	char	*path_player;
	char	*path_pika;
	int		i;

	i = -1;
	while (++i < 16)
	{
		path_player = str("img/player/player_%x.xpm", i);
		data->img_player[i] = mlx_xpm_file_to_image(data->mlx, path_player,
				&data->wid, &data->hei);
		free(path_player);
		if (!data->img_player[i])
			(put(ERR "cant open player file\n"), exit_all(data));
		path_pika = str("img/pika/pika_%x.xpm", i);
		data->img_pika[i] = mlx_xpm_file_to_image(data->mlx, path_pika,
				&data->wid, &data->hei);
		free(path_pika);
		if (!data->img_pika[i])
		{
			put(ERR "cant open pika file\n");
			exit_all(data);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
void	ini_texture(t_data *data)
{
	int	i;

	ini_anim(data);
	data->img_ground = mlx_xpm_file_to_image(data->mlx, "img/txt_grass.xpm",
			&data->wid, &data->hei);
	data->img_wall = mlx_xpm_file_to_image(data->mlx, "img/txt_wall.xpm",
			&data->wid, &data->hei);
	data->img_ball = mlx_xpm_file_to_image(data->mlx, "img/txt_collect.xpm",
			&data->wid, &data->hei);
	data->img_exit = mlx_xpm_file_to_image(data->mlx, "img/txt_exit.xpm",
			&data->wid, &data->hei);
	data->win = mlx_new_window(data->mlx, data->wid * data->map_x, data->hei
			* data->map_y, "So Long average");
	if (!data->win || !data->img_ground || !data->img_wall || !data->img_exit
		|| !data->img_ball)
		(put(ERR "cant open file\n"), exit_all(data));
	data->player[2] = 4;
	data->player_time = -1;
	i = -1;
	while (++i < data->num_pika)
	{
		data->pika[i][2] = 4;
		data->pika_time[i] = -1;
	}
}
