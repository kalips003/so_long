# include "so_long.h"

/////////////////////////////////////////////////////////////////////////////////////
int render2(t_data *data)
{
    data->time_frame = (data->time_frame + 1) % TIME_F;
    if (data->player_time >= 0)
        f_move_player(data);
    f_move_pika(data);
    put_background_to_img(data);
    put_foreground_to_img(data);
    if (data->is_dying)
        draw_square_2(data, data->player[0] * 64, data->player[1] * 64, 64);
    mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
    return (0);
}

void put_background_to_img(t_data *data)
{
    int x;
    int y;

    y = -1;
    while (++y < data->map_y)
    {
        x = -1;
        while (++x < data->map_x)
        {
            if (data->map[y][x] == '1')
                mlx_put_image_to_window(data->mlx, data->win, data->img_wall, data->wid * x, data->hei * y);
            else if (data->map[y][x] == '0' || data->map[y][x] == 'P' || data->map[y][x] == 'z')
                mlx_put_image_to_window(data->mlx, data->win, data->img_ground, data->wid * x, data->hei * y);
            else if (data->map[y][x] == 'C')
                mlx_put_image_to_window(data->mlx, data->win, data->img_ball, data->wid * x, data->hei * y);
            else if (data->map[y][x] == 'E')
                mlx_put_image_to_window(data->mlx, data->win, data->img_exit, data->wid * x, data->hei * y);
        }
    }
}

void put_foreground_to_img(t_data *data)
{
    int i;

    mlx_put_image_to_window(data->mlx, data->win, data->img_player[data->player[2]], data->player[0] * data->wid, data->player[1] * data->hei);
    i = -1;
    while (++i < data->num_pika)
    {
        mlx_put_image_to_window(data->mlx, data->win, data->img_pika[data->pika[i][2]], data->pika[i][0] * data->wid, data->pika[i][1] * data->hei);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
static void ini_anim2(t_data *data)
{
    char *path_player;
    char *path_pika;
    char *dico;

    dico = "0123456789abcdef";
    int i = -1;
    while (++i < 16)
    {
        path_player = str("img/player/player_%c.xpm", dico[i]);
        data->img_player[i] = mlx_xpm_file_to_image(data->mlx, path_player, &data->wid, &data->hei);
        free(path_player);
        if (!data->img_player[i])
        {
            put("cant open player file\n");
            exit_all(data);
        }
        // random starter
        path_pika = str("img/pika/pika_%c.xpm", dico[i]);
        data->img_pika[i] = mlx_xpm_file_to_image(data->mlx, path_pika, &data->wid, &data->hei);
        free(path_pika);
        if (!data->img_pika[i])
        {
            put("cant open pika file\n");
            exit_all(data);
        }
    }
}

void ini_texture2(t_data *data)
{
	int i;

    ini_anim(data);
    data->img_ground = mlx_xpm_file_to_image(data->mlx, "img/txt_floor.xpm", &data->wid, &data->hei);
	data->img_wall = mlx_xpm_file_to_image(data->mlx, "img/txt_wall.xpm", &data->wid, &data->hei);
	data->img_ball = mlx_xpm_file_to_image(data->mlx, "img/txt_collect.xpm", &data->wid, &data->hei);
	data->img_exit = mlx_xpm_file_to_image(data->mlx, "img/txt_exit.xpm", &data->wid, &data->hei);
    data->win = mlx_new_window(data->mlx, data->wid * data->map_x, data->hei * data->map_y + 75, "So Looong");
    if (!data->win || !data->img_ground|| !data->img_wall|| !data->img_exit|| !data->img_ball)
    {
        put("cant open file\n");
        exit_all(data);
    }
    data->player[2] = 4;
    data->player_time = -1;
    i = -1;
    while (++i < data->num_pika)
    {
        data->pika[i][2] = 4;
        data->pika_time[i] = -1;
    }
}

// void f_put_img_to_buffer(t_data *data, t_coor xy, )
// {

// }

// void	draw_sprite(t_data *game, t_img *img, int x, int y)
// {
// 	int				i;
// 	int				j;
// 	unsigned int	color;

// 	i = 0;
// 	while (i < img->width)
// 	{
// 		j = -1;
// 		while (++j < img->height)
// 		{
// 			if (j + y < 0 || j + y >= (game->max_y * 32) || i + x < 0 || i + x >= (game->max_x * 32))
// 				continue ;
// 			color = ((int *)img->data)[(int)j * img->width + (int)i];
// 			if (color == 0xFF000000)
// 				continue ;
// 			((int *)game->screen->data)[(y + j) * game->screen->width + (x + i)] = color;
// 		}
// 		i++;
// 	}
// }

// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
