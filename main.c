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
		return (put(ERR "bad argument\n"), exit(1));
	fd_map = open(path, O_RDONLY);
	if (fd_map == -1)
		return (perror("open"), exit(1));
	if (fill_map(data, fd_map) || count_check(data))
		exit_all(data);
	if (valid_path(data))
		exit_all_2(data, ERR "bad pathing\n");
}

////////////////////////////////////////////////////////////////
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (put(ERR "bad arguments\n"), 1);
	is_map_ok(&data, av[1]);
	data.mlx = mlx_init();
	if (!data.mlx)
		exit_all(&data);
	ini_texture(&data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.win, 17, 0, &exit_all, &data);
	mlx_loop(data.mlx);
	exit_all(&data);
}
