/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_outils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:11 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 17:01:38 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int			exit_all_v2(t_data2 *data);
void		print_data(t_data2 *data);
static void	destroy_img_v4(t_data2 *d);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	exit at any point, with security for all
******************************************************************************/
int	exit_all_v2(t_data2 *data)
{
	free_tab(data->map);
	if (data->pika)
		free_s(data->pika);
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
// 	PRINT DATA STRUCT & PIKA & MAP
void	print_data(t_data2 *data)
{
	put(CLS"\tDATA\n[%#*S", offsetof(t_data2, time), data);
	put(BLINK RED"[%.8d]"R_BLINK, data->time);
	put("%#*S", 2 * sizeof(int), &data->map_x);
	put(BLINK BLUE"[%.8d]"R_BLINK, data->steps);
	put("%#*S]", sizeof(t_data2) - offsetof(t_data2, n_ball), &data->n_ball);
	put("\n\tPIKA\n[%p]%#+*.24S\n", data->pika, sizeof(t_npc) * data->n_pika, \
		data->pika);
	put("\tMAP\n%.1t\n", data->map);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	helper destroy all img in a loop
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static void	destroy_img_v4(t_data2 *d)
{
	int		i;
	t_img	*curseur;

	curseur = &d->buffer;
	i = -1;
	while (++i <= 22)
	{
		if (curseur->img)
			mlx_destroy_image(d->mlx, curseur->img);
		curseur++;
	}
}
