/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:58 by marvin            #+#    #+#             */
/*   Updated: 2024/06/24 21:20:02 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

////////////////////////////////////////////////////////////////
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (put(ERR "bad arguments\n"), 1);
	is_map_ok(&data, av[1]);
	data.mlx = mlx_init();
	if (!data.mlx)
		(put("--->MLX fait de la merde\n"), exit_all(&data));
	ini_texture(&data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.win, 17, 0, &exit_all, &data);
	mlx_loop(data.mlx);
	exit_all(&data);
}
