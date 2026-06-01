# include "so_long.h"

# define XK_Escape 0
# define XK_w 0
# define XK_d 0
# define XK_a 0
# define XK_s 0
# define XK_space 0
# define XK_Up 0
# define XK_Right 0
# define XK_Down 0
# define XK_Left 0
# define XK_ctrl 0


///////////////////////////////////////////////////////////////////////////////]
static void    f_save_time_player(t_data2 *data, int n0123, int frame)
{
    if (data->player[2] != frame)
        data->player[2] = frame;
    else if (check_path_player_v2(data, n0123, &data->player, -1))
    {
        data->player[3] = 64;
        data->walk_count++;
    }
}

///////////////////////////////////////////////////////////////////////////////]
//      initial ball event handler, check immediate path, ball count, give time
static void    f_save_time_ball(t_data2 *data)
{
    if (data->ball_throw.time < 0 || !data->num_holding)
        return ;
    if (check_path_player_v2(data, data->player[2] / 4, &data->player, -1) == 0)
        return ;
    data->ball_throw.time = SPRITE_SIZE * THROW_RANGE;
    data->ball_throw.frame = 0;
    data->ball_throw.x = data->player[0] + OFFSET_BALL_THR;
    data->ball_throw.y = data->player[1] + OFFSET_BALL_THR;
    data->ball_throw.n0123 = data->player[2] / 4;

    data->num_holding--;
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        if player has a time, doesnt register any input
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int	key_press_v2(int keysym, t_data2 *data)
{
	if (keysym == XK_Escape)
			exit_all_v2(data);
	if (keysym == XK_ctrl)
		data->running = 1;
	if (keysym == XK_e)
		data->time_freeze = 1;
	if (data->player[3])
		return (0);
	if (keysym == XK_d || keysym == XK_Right)
		f_save_time_player(data, 0, 0);
	else if (keysym == XK_s || keysym == XK_Down)
		f_save_time_player(data, 1, 4);
	else if (keysym == XK_a || keysym == XK_Left)
		f_save_time_player(data, 2, 8);
	else if (keysym == XK_w || keysym == XK_Up)
		f_save_time_player(data, 3, 12);
	else if (keysym == XK_space && !data->ball_throw.time)
		f_save_time_ball(data);
	return (0);
}

int	key_release(int keysym, t_data2 *data)
{
	if (keysym == XK_ctrl)
        data->running = 0;
	if (keysym == XK_e)
        data->time_freeze = 0;
	if (keysym == XK_Escape)//  small anim for throwing
        data->running = 0;
	return (0);
}
