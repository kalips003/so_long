#include "so_long.h"

int	exit_all(t_data *data)
{
	int	i;

	free_tab(data->map);
	if (data->pika)
		free(data->pika);
	if (data->img_ground)
		mlx_destroy_image(data->mlx, data->img_ground);
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
	if (data->img_ball)
		mlx_destroy_image(data->mlx, data->img_ball);
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
