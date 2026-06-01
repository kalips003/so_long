# include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		if a caracter has a time value, ft_move will update its position
        and frame according to the GLOBAL_TIME
        use current frame to calculate direction
*******************************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        move player in a [0,1,0,2,0] fashion
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    f_move_player_v2(t_data2 *data)
{
	if (!data->player.time)
		return ;
	// if (data->time % (TIME_PLAYER / (1 + data->running)))
		// return ;
	data->player.time--;
	data->player.x += data->player.dx;
	data->player.y += data->player.dy;
	if (data->player.time == 54)
		data->player.f += 1;
	else if (data->player.time == 40)
		data->player.f += -1;
	else if (data->player.time == 24)
		data->player.f += 2;
	else if (data->player.time == 10)
		data->player.f += -2;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        move all enemy. if time == 0, random what happen next
        its also the ft_save_time of the enemies
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    ft_move_enemy(t_data2 *data)
{
	int	i;
	int	random;

	i = -1;
	while (++i < data->num_pika && i < 10)
	{
		if (data->pika[i].time < 0 || data->pika[i].x < 0)
			continue ;
		if (data->pika[i].time > 0)
			move_pika_v2(data, i);
		else
		{
			random = (rand() % (PIKA_MOVE_CHANCE + i));
			if (random < PIKA_TURN_CHANCE)
				data->pika[i].f = random % 8;
			if (random <= 3)
			{
				data->pika[i].dx = cos((double)random / 2 * PI);
				data->pika[i].dy = sin((double)random / 2 * PI);
				if (check_path_player_v3(data, data->pika[i], i) > 0)
					data->pika[i].time = 64;
			}
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        if time saved > 0, move pika n*i
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    move_pika_v2(t_data2 *data, int i)
{
    if (data->time % (TIME_PIKA + i))
        return ;
    data->pika[i].time--;
    data->pika[i].x += data->pika[i].dx;
    data->pika[i].y += data->pika[i].dy;
    if (!(data->pika[i].time % (16 + i)))
        data->pika[i].f += 1 - 2 * (data->pika[i].f % 2);
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        animation handler for ball throw
        move it 1 pixel, change its sprite
        if ball touch a pika, its time is negative
            in this case, the catching ball animation is played
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	move_ball(t_data2 *data)
{
	// if (data->time % TIME_BALL)
	// 	return ;
	if (data->throw.ball.time < 0)
	{
		draw_circle(data, (t_circle){data->throw.ball.x + BALL_SIZE / 2, data->throw.ball.y + BALL_SIZE / 2, -data->throw.ball.time, random_white});
		if (data->throw.ball.time == -5)
			data->pika[data->throw.pika_caught].x = -1;// <!> - - - - - -time also? - - - - - </!>
		if (data->throw.ball.time == -1)
			data->map[(int)round(data->throw.ball.x / SPRITE_SIZE)][(int)round(data->throw.ball.y / SPRITE_SIZE)] = 'c';
		data->throw.ball.time++;
		return ;
	}
	data->throw.ball.x += data->throw.ball.dx;
	data->throw.ball.y += data->throw.ball.dy;
	if (!(data->throw.ball.time % 5))
		data->throw.ball.f = (data->throw.ball.f + 1) % 12;
	if (data->throw.ball.time == 1)
		data->map[(int)round(data->throw.ball.x / SPRITE_SIZE)][(int)round(data->throw.ball.y / SPRITE_SIZE)] = 'C';
	data->throw.ball.time--;
}


// void    move_pika(t_data2 *data, int i)
// {

//     int direction = data->pika[i].f / 2;
//     int co = (int)cos(direction * PI / 2);
//     int si = (int)sin(direction * PI / 2);

//     if (abs(data->time - data->pika[i].time) % SLOWING + i)
//         return ;
//     data->pika[i].x += co;
//     data->pika[i].y += si;
//     if (!((data->pika[i].x + data->pika[i].y) % SPRITE_SIZE % 8))
//         data->pika[i].f += 1 - 2 * (data->pika[i].f % 2);
//     if (((data->pika[i].x + data->pika[i].y) % SPRITE_SIZE == 63 && co + si > 0) ||
//         ((data->pika[i].x + data->pika[i].y) % SPRITE_SIZE == 1 && co + si < 0))
//     {
//         data->pika[i].x += co;
//         data->pika[i].y += si;
//         data->pika[i].f += 1 - 2 * (data->pika[i].f % 2);
//         data->pika[i].time = -1;
//     }
// }
