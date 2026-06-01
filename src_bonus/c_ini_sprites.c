/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ini_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 04:24:13 by agallon           #+#    #+#             */
/*   Updated: 2024/06/26 17:00:34 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		ini_sprites(t_data2 *data);
static int	helper_texture(t_data2 *data, char *path, t_img *img, int sw);
static void	ini_anim_v3(t_data2 *data);
static void	ini_img(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		initialize all sprites,
			the starter, and player default position reset
		if any pb, exit all by itself
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////]
void	ini_sprites(t_data2 *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		(put(ERRM"--->MLX fait de la merde\n"), exit_all_v2(data));
	ini_anim_v3(data);
	ini_img(data);
	data->buffer.sz_x = SZ * data->map_x;
	data->buffer.sz_y = SZ * data->map_y + BLACK_BOT;
	data->win = mlx_new_window(data->mlx, data->buffer.sz_x, \
			data->buffer.sz_y, "Welcome to PikaLand");
	data->buffer.img = mlx_new_image(data->mlx, data->buffer.sz_x, \
			data->buffer.sz_y);
	if (!data->win || !data->buffer.img)
		(put(RED"Problem initalisazing mlx (2)\n"), exit_all_v2(data));
	data->buffer.addr = mlx_get_data_addr(data->buffer.img, &data->buffer.bpp, \
			&data->buffer.ll, &data->buffer.end);
	data->player.f = 4;
	data->exit[2] = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	initialize variable sprites:
		PLAYER_GENDER
		STARTER
		BURNED_GRASS_TILE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static void	ini_anim_v3(t_data2 *data)
{
	char	*path_p;
	int		j;

	path_p = str("img/player_b/player_%d.xpm", data->boy_or_girl);
	j = helper_texture(data, path_p, &data->i_player, 1);
	free_s(path_p);
	if (!j)
		(put(ERR1"cant open player sprite\n"), exit_all_v2(data));
	path_p = str("img/enemy/enemy_%d.xpm", data->starter);
	j = helper_texture(data, path_p, &data->i_pika, 1);
	free_s(path_p);
	if (!j)
		(put(ERR1"cant open enemy n*%d\n", data->starter), exit_all_v2(data));
	path_p = str("img/txt_grass_%d.xpm", data->starter);
	j = helper_texture(data, path_p, &data->i_ground[1], 1);
	free_s(path_p);
	if (!j)
		(put(ERR1"cant open grass sprite\n"), exit_all_v2(data));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	fill in all data from img_path
		bit = 0 exit all
		bit = 1 return 0
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static int	helper_texture(t_data2 *data, char *p, t_img *img, int sw)
{
	if (p)
		img->img = mlx_xpm_file_to_image(data->mlx, p, &img->sz_x, &img->sz_y);
	if (!img->img)
	{
		put("sprite n*%d\n", (int)(((unsigned long)img - (unsigned long)data) \
			/ sizeof(t_img)));
		perror(COLOR_2R_2G_3B"cant open file");
		if (!sw)
			exit_all_v2(data);
		else
			return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->end);
	return (1);
}

static void	ini_img(t_data2 *data)
{
	int		i;
	int		j;
	char	*path;

	i = -1;
	while (++i < 10)
	{
		path = str("img/num/%d.xpm", i);
		j = helper_texture(data, path, &data->i_numbers[i], 1);
		path = free_s(path);
		if (!j)
			(put(ERR1"cant open number sprite\n"), exit_all_v2(data));
	}
	helper_texture(data, "img/txt_grass.xpm", &data->i_ground[0], 0);
	helper_texture(data, "img/txt_wall.xpm", &data->i_wall, 0);
	helper_texture(data, "img/txt_collect.xpm", &data->i_ball[0], 0);
	helper_texture(data, "img/txt_collect2.xpm", &data->i_ball[1], 0);
	helper_texture(data, "img/big_ball.xpm", &data->i_big_ball[0], 0);
	helper_texture(data, "img/big_ball_pika.xpm", &data->i_big_ball[1], 0);
	helper_texture(data, "img/ball_throw.xpm", &data->i_throw, 0);
	helper_texture(data, "img/txt_exit.xpm", &data->i_exit[1], 0);
	helper_texture(data, "img/txt_exit2.xpm", &data->i_exit[0], 0);
}
