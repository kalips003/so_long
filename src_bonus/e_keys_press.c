#include "so_long_bonus.h"

int	key_press(int keysym, t_data2 *data);
int	key_release(int keysym, t_data2 *data);
static void	f_save_time_player(t_data2 *data, int dx, int dy, int frame);
static void	f_save_time_ball(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        if player has a time, doesnt register any input
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# define XK_Escape 0
# define XK_Control_L 0
# define XK_e 0
# define XK_Right 0
# define XK_d 0
# define XK_Down 0
# define XK_s 0
# define XK_Left 0
# define XK_a 0
# define XK_Up 0
# define XK_w 0
# define XK_space 0

int	key_press(int keysym, t_data2 *data)
{
	if (keysym == XK_Escape)
			exit_all_v2(data);
	if (keysym == XK_e)
		data->time_freeze = 1;
	if (keysym == XK_Control_L)
		data->running = 1;
	if (data->player.time)
		return (0);
	if (keysym == XK_d || keysym == XK_Right)
		f_save_time_player(data, 1, 0, 0);
	else if (keysym == XK_s || keysym == XK_Down)
		f_save_time_player(data, 0, 1, 4);
	else if (keysym == XK_a || keysym == XK_Left)
		f_save_time_player(data, -1, 0, 8);
	else if (keysym == XK_w || keysym == XK_Up)
		f_save_time_player(data, 0, -1, 12);
	else if (keysym == XK_space && !data->throw.ball.time)
		f_save_time_ball(data);
	return (0);
}

int	key_release(int keysym, t_data2 *data)
{
	if (keysym == XK_Control_L)
        data->running = 0;
	if (keysym == XK_e)
        data->time_freeze = 0;
	if (keysym == XK_space)//  small anim for throwing
        data->running = 0;
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
static void	f_save_time_player(t_data2 *data, int dx, int dy, int frame)
{
	data->player.dx = dx;
	data->player.dy = dy;
	if (data->player.f != frame)
	{
		data->player.f = frame;
		return ;
	}
	if (check_path_npc(data, data->player, -1))
	{
		data->walk_count++;
		data->player.time = 64;
	}
}

///////////////////////////////////////////////////////////////////////////////]
//      initial ball event handler, check immediate path, ball count, give time
static void	f_save_time_ball(t_data2 *data)
{
	if (!data->num_holding)
		return ;
	if (check_path_npc(data, data->player, -1) == 0)
		return ;
	data->throw.ball.time = SPRITE_SIZE * THROW_RANGE;
	data->throw.ball.f = 0;
	data->throw.ball.x = data->player.x;
	data->throw.ball.y = data->player.y;
	data->throw.ball.dx = data->player.dx;
	data->throw.ball.dy = data->player.dy;
	data->num_holding--;
}