#include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
int ft_loop(t_data2 *data)
{
    char *message;
    
    put(CLS"%#*S", sizeof(t_data2), data);// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
    put("\n%#*S", sizeof(int[4]) * data->num_pika, &data->pika[0]);
    data->time_frame = (data->time_frame + 1) % TIME_F;
    check_what_your_walking_on(data);
    if (data->player[3] < 0)
    {
        put_background_to_buffer(data);
        f_is_dying(data);
        mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
        return (0);
    } 
    check_ball_throw_path(data);
    f_move_player_v2(data);
    ft_move_enemy(data);
    put_background_to_buffer(data);
    put_foreground_to_buffer(data);
    if (data->ball_throw.time)
        move_ball(data);
    if (data->attack.time)
        render_attack(data);
    mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
    message = str("Current TIME: %d steps", data->walk_count);
    mlx_string_put(data->mlx, data->win, 50, data->buffer.sz_y + 50, 0x00FF0000, message);
    free_s(message);
    return (0);
}

///////////////////////////////////////////////////////////////////////////////]
static void ft_stamina(t_data2 *data)
{
    if (data->running)
        data->stamina = max(data->stamina - 1, 0);
    else
        data->stamina = min(data->stamina + 1, MAX_ENDURANCE);
    draw_stamina(data);
}

void put_background_to_buffer(t_data2 *data)
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
                f_put_sprite_to_buffer(data, &(int){x * SPRITE_SIZE, y * SPRITE_SIZE}, data->i_wall);// <!> - - - - - - - - - - - - - - - - - </?>
            else if (data->map[y][x] == '0' || data->map[y][x] == 'P' || data->map[y][x] == 'z')
                f_put_sprite_to_buffer(data, &(int){x * SPRITE_SIZE, y * SPRITE_SIZE}, data->i_ground[0]);
            else if (data->map[y][x] == '*')
                f_put_sprite_to_buffer(data, &(int){x * SPRITE_SIZE, y * SPRITE_SIZE}, data->i_ground[1]);
            else if (data->map[y][x] == 'C' || data->map[y][x] == 'c')
                f_put_sprite_to_buffer(data, &(int){x * SPRITE_SIZE, y * SPRITE_SIZE}, data->i_ball[(data->map[y][x] == 'c')]);
            else if (data->map[y][x] == 'E')
                f_put_sprite_to_buffer(data, &(int){x * SPRITE_SIZE, y * SPRITE_SIZE}, data->i_exit[0 + data->is_all_collected]);
        }
    }
    ft_stamina(data);
}

///////////////////////////////////////////////////////////////////////////////]
void put_foreground_to_buffer(t_data2 *data)
{
    int i;

    f_put_player_to_buffer_v2(data, 0, random_white);
    i = -1;
    while (++i < data->num_pika)
    {
        if (data->pika[i][3] == -1)
            f_put_sprite_to_buffer_v2(data, &data->pika[i], data->i_pika[data->pika[i][2]], random_yellow_v2);
        else
            f_put_sprite_to_buffer_v2(data, &data->pika[i], data->i_pika[data->pika[i][2]], random_white);
    }
    if (data->ball_throw.time)
        f_put_event_ball_to_buffer_v2(data);
    put_black_background(data);
    put_balls_foreground(data);
}