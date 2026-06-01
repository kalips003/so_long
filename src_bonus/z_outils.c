/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_outils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:11 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 19:20:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	exit_all_v2(t_data2 *data);
void	ft_break(int n, char *string, t_data2 *data);
static void destroy_img_v4(t_data2 *d);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	exit at any point, with security for all
*******************************************************************************/
int	exit_all_v2(t_data2 *data)
{
	free_tab(data->map);
	if (data->pika)
	{
		// put("PIKA=\n[%*S]\n", sizeof(t_npc), data->pika);
		// put("------->\n");
		free_s(data->pika);
	}
	destroy_img_v4(data);
	if (data->mlx)
	{
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free_s(data->mlx);
	}
	exit(0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	BREAK : small cat break point

	char *string1;
	string1 = str(" ---> %d", data);
	char *string2;
	string2 = str(" ---> %d", data);
	ft_break("1", string2, data);
	free_s(string1);
	free_s(string2);
*******************************************************************************/
// ft_break("TEST ( 1 )", "DATA struct");
void	ft_break(int n, char *string, t_data2 *data)
{
// 	PRINT DATA STRUCT & PIKA & MAP
	put(CLS"\tDATA\n[%#+*S", offsetof(t_data2, time), data);
	put(BLINK RED"[%.8d]"R_BLINK, data->time);
	put("%#+*S", 2 * sizeof(int), &data->map_x);
	put(BLINK BLUE"[%.8d]"R_BLINK, data->walk_count);
	put("%#+*S]", sizeof(t_data2) - offsetof(t_data2, num_ball), &data->num_ball);
	put("\n\tPIKA\n[%#+*.24S]\n", sizeof(t_npc) * data->num_pika, data->pika);
	put("\tMAP\n%.1t\n", data->map);

	ft_print_cat(n, string, 0);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	helper destroy all img in a loop
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void destroy_img_v4(t_data2 *d)
{
	int	i;
	t_img	*curseur;

	curseur = &d->buffer;
	i = -1;
	while (++i <= 21)
	{
		if (curseur->img)
			mlx_destroy_image(d->mlx, curseur->img);
		curseur++;
	}
}
///////////////////////////////////////////////////////////////////////////////]
// 														OLD VERSION WITHOUT LOOP
// static void destroy_img_v3(t_data2 *d)
// {
// 	int	i;
// 
// 	if (d->i_ground[0].img)
// 		mlx_destroy_image(d->mlx, d->i_ground[0].img);
// 	if (d->i_ground[1].img)
// 		mlx_destroy_image(d->mlx, d->i_ground[1].img);
// 	if (d->i_wall.img)
// 		mlx_destroy_image(d->mlx, d->i_wall.img);
// 	if (d->i_exit[0].img)
// 		mlx_destroy_image(d->mlx, d->i_exit[0].img);
// 	if (d->i_exit[1].img)
// 		mlx_destroy_image(d->mlx, d->i_exit[1].img);
// 	if (d->i_ball[0].img)
// 		mlx_destroy_image(d->mlx, d->i_ball[0].img);
// 	if (d->i_ball[1].img)
// 		mlx_destroy_image(d->mlx, d->i_ball[1].img);
// 	if (d->buffer.img)
// 		mlx_destroy_image(d->mlx, d->buffer.img);
// 	if (d->i_player.img)
// 		mlx_destroy_image(d->mlx, d->i_player.img);
// 	if (d->i_big_ball[0].img)
// 		mlx_destroy_image(d->mlx, d->i_big_ball[0].img);
// 	if (d->i_big_ball[1].img)
// 		mlx_destroy_image(d->mlx, d->i_big_ball[1].img);
// 	if (d->i_throw.img)
// 		mlx_destroy_image(d->mlx, d->i_throw.img);
// 	if (d->i_numbers.img)
// 		mlx_destroy_image(d->mlx, d->i_numbers.img);
// 	i = -1;
// 	while (++i < 8)
// 		if (d->i_pika[i].img)
// 			mlx_destroy_image(d->mlx, d->i_pika[i].img);
// }
///////////////////////////////////////////////////////////////////////////////]
