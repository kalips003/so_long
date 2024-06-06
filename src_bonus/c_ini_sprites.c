# include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		initialize all sprites, the starter, and plyer default position
*******************************************************************************/
// fill in all data from img_path
// bit = 0 exit all
// bit = 1 return 0
static int helper_texture(t_data2 *data, char *path, t_img *img, int sw)
{
    img->img = mlx_xpm_file_to_image(data->mlx, path, &img->sz_x, &img->sz_y);
    if (!img->img)
    {
        perror(COLOR_2R_2G_3B"cant open file"RESET);
        if (!sw)
            exit_all_v2(data);
        else
            return (0);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    return (1);
}

// initialize variable sprites
static void ini_anim_v3(t_data2 *data)
{
    char *path_p;
    int i;
    int j;

    path_p = str("img/player_b/player_%d.xpm", data->boy_or_girl);
    j = helper_texture(data, path_p, &data->i_player, 1);
    free_s(path_p);
    if (!j)
        exit_all_v2(data);
    data->starter = rand() % 4;
    i = -1;
    while (++i < 8)
    { 
        path_p = str("img/enemy/%d/enemy_%d.xpm", data->starter, i);
        j = helper_texture(data, path_p, &data->i_pika[i], 1);
        free(path_p);
        if (!j)
            exit_all_v2(data);
    }
    path_p = str("img/grass/grass_%d.xpm", data->starter);
    j = helper_texture(data, path_p, &data->i_ground[1], 1);
    free_s(path_p);
    if (!j)
        exit_all_v2(data);
}

///////////////////////////////////////////////////////////////////////////////]
void ini_sprites(t_data2 *data)
{
    ini_anim_v3(data);
    helper_texture(data, "img/txt_floor.xpm", &data->i_ground[0], 0);
    helper_texture(data, "img/txt_floor_0.xpm", &data->i_ground[1], 0);
    helper_texture(data, "img/txt_wall.xpm", &data->i_wall, 0);
    helper_texture(data, "img/txt_collect.xpm", &data->i_ball[0], 0);
    helper_texture(data, "img/txt_collect_pika.xpm", &data->i_ball[1], 0);
    helper_texture(data, "img/big_ball.xpm", &data->i_big_ball[0], 0);
    helper_texture(data, "img/big_ball_pika.xpm", &data->i_big_ball[1], 0);
    helper_texture(data, "img/ball_throw.xpm", &data->i_ball_throw, 0);
    helper_texture(data, "img/txt_exit.xpm", &data->i_exit[0], 0);
    helper_texture(data, "img/txt_exit1.xpm", &data->i_exit[1], 0);
    data->buffer.sz_x = SPRITE_SIZE * data->map_x;
    data->buffer.sz_y = SPRITE_SIZE * data->map_y + BLACK_BOT;
    data->win = mlx_new_window(data->mlx, data->buffer.sz_x, data->buffer.sz_y, "Welcome to PikaLand");
    data->buffer.img = mlx_new_image(data->mlx, data->buffer.sz_x, data->buffer.sz_y);
    if (!data->win || !data->buffer.img)
        (put("cant open file\n"), exit_all_v2(data));
    data->buffer.addr = mlx_get_data_addr(data->mlx, &data->buffer.bits_per_pixel, &data->buffer.line_length, &data->buffer.endian);
    data->player[2] = 4;
    data->exit[2] = -1;// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
    data->exit[3] = -1;// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
}
