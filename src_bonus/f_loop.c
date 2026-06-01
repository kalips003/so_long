#include "so_long.h"

#define DESIRED_FPS 64
#define FRAME_DURATION_MICROSECONDS (1000000 / DESIRED_FPS)
///////////////////////////////////////////////////////////////////////////////]
// clean it , with usleep
int ft_loop_v2(t_data2 *data)
{
	int	startTime = getCurrentTime();
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
	
	char *message;

	if (data->time_freeze)
		return (0);
	data->time = (data->time + 1) % TIME_F;
	// if (!(data->time % 5))
	//     f_print_memory(data);// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
	put("%d ", data->time);// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
	if (data->player.time < 0)//			player is dying
		return (f_is_dying(data));
	check_what_your_walking_on(data);
	if (data->throw.ball.time < 0)
		check_throw_path(data);
	if (data->attack.time > 0)
		if (is_player_touched(&data->attack.circle.center_x, &data->attack.circlend.center_x, &data->player.x))
			data->player.time = -1;
	else if (!data->attack.time && data->num_pika && (rand() % (ATTACK_CHANCE + 1)))
		find_pika_for_attak(data);
	f_move_player_v2(data);
	ft_move_enemy(data);
	background(data);
    put_foreground_to_buffer(data);
    if (data->throw.ball.time)
        move_ball(data);
    if (data->attack.time)
        render_attack(data);


    mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
    message = str("Current TIME: %d steps", data->walk_count);
    mlx_string_put(data->mlx, data->win, 50, data->buffer.sz_y + 50, 0x00FF0000, message);
    free_s(message);
	// draw score
    return (0);
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>

	int frameTime = getCurrentTime() - startTime;
	if (frameTime < FRAME_DURATION_MICROSECONDS) {
		printf("Time difference: %ld microseconds\n", FRAME_DURATION_MICROSECONDS - frameTime);
		usleep(FRAME_DURATION_MICROSECONDS - frameTime);
	}
}

///////////////////////////////////////////////////////////////////////////////]
int ft_loop(t_data2 *data)
{
    char *message;

    if (data->time_freeze)
        return (0);
    // if (!(data->time % 5))
    //     f_print_memory(data);// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
    data->time = (data->time + 1) % TIME_F;
    put("%d ", data->time);
    check_what_your_walking_on(data);
    if (data->player.time < 0)
    {
        put_background_to_buffer(data);
        f_is_dying(data);
        mlx_put_image_to_window(data->mlx, data->win, data->buffer.img, 0, 0);
        return (0);
    }
    check_throw_path(data);
    f_move_player_v2(data);
    ft_move_enemy(data);
	background(data);
    put_foreground_to_buffer(data);
    if (data->throw.ball.time)
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
void put_foreground_to_buffer(t_data2 *data)
{
    int i;

    f_put_player_to_buffer_v2(data, 0, random_yellow);
    i = -1;
    while (++i < data->num_pika)
    {
        if (data->pika[i].time == -1)
            f_put_sprite_to_buffer_v2(data, &data->pika[i].x, data->i_pika[data->pika[i].f], random_yellow_v2);
        else
            f_put_sprite_to_buffer_v2(data, &data->pika[i].x, data->i_pika[data->pika[i].f], random_white);
    }
    if (data->throw.ball.time)
        f_put_event_ball_to_buffer_v2(data);
}
