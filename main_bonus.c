# include "so_long.h"

/***************************************************************
    create map, free it in all cases
    do all the tests, exit in case of any error
****************************************************************/
void is_map_ok(t_data *data, char *path)
{
    int fd_map;

    ft_memset(data, 0, sizeof(t_data));
// map path end in ".ber"
    if (find_str(path, ".ber") != len(path) - 4)
        (put("bad argument\n"), exit(1));
// create map struct
    fd_map = open(path, O_RDONLY);
    if (fd_map == -1)
        (perror("open"), exit(1));
// fill map
    if (fill_map(data, fd_map) || count_check(data))
        exit_all(data);
// valid path?
    if (valid_path(data))
        (put("bad pathing\n"), exit_all(data));
}

/////////////////////////////////////////////////////////////////////////////////////
int main(int ac, char **av)
{
	t_data  data;

    if (ac != 2)
        return (put("bad arguments\n"), 1);
    is_map_ok(&data, av[1]);
////////////////////////////////////////
	data.mlx = mlx_init();
    if (!data.mlx)
        exit_all(&data);
    ini_texture(&data);
////////////////////////////////////////
    mlx_loop_hook(data.mlx, &render, &data);
    mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
    mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data);
    mlx_hook(data.win, 17, 0, &exit_all, &data);
	mlx_loop(data.mlx);
////////////////////////////////////////
    exit_all(&data);
}

/*

UP      (0) W = 0x -1y
RIGHT   (1) D = 1x 0y
DOWN    (2) S = 0x 1y
LEFT    (3) A = -1x 0y

UP      [0, -1] >+1 [1, 0] >*2y [1, 0] > 1
LEFT    [-1, 0] >+1 [0, 1] >*2y [0, 2] > 2
RIGHT   [1, 0] >+1 [2, 1] >*2y [2, 2] > 4
DOWN    [0, 1] >+1 [1, 2] >*2y [1, 4] > 5



A       B
0 1 0 2 0


pika 4 chance to move
4 x n chance to turn
    n can be modulo the pika number, to have fast ones and slow ones

? chance to attack







*/
