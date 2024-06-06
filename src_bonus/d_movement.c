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
    if (!data->player[2])
        return ;
    if (data->time_frame % (TIME_PLAYER / (1 + data->running)))
        return ;
    data->player[3]--;
    data->player[0] += cos(data->player[2] * PI / 8);
    data->player[1] += sin(data->player[2] * PI / 8);
    if (data->player[3] == 54)
        data->player[2] += 1;
    else if (data->player[3] == 40)
        data->player[2] += -1;
    else if (data->player[3] == 24)
        data->player[2] += 2;
    else if (data->player[3] == 10)
        data->player[2] += -2;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        move all enemy. if time == 0, random what happen next
        its also the ft_save_time of the enemies
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    ft_move_enemy(t_data2 *data)
{
    int     i;
    int     random;

    i = -1;
    while (++i < data->num_pika && i < 10)
    {
        if (data->pika[i][3] < 0 || data->pika[i][0] < 0)
            continue ;
        if (data->pika[i][3] > 0)
            move_pika_v2(data, i);
        else
        {
            random = (rand() % (PIKA_MOVE_CHANCE + i));
            if (random < PIKA_TURN_CHANCE)
                data->pika[i][2] = random % 8;
            if (random <= 3 && check_path_player_v2(data, random, &data->pika[i], i) > 0)
                data->pika[i][3] = 64;
        }
    }
    check_random_attak(data);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        if time saved > 0, move pika n*i
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    move_pika_v2(t_data2 *data, int i)
{
    if (data->time_frame % (TIME_PIKA + i))
        return ;
    data->pika[i][3]--;
    data->pika[i][0] += cos(data->pika[i][2] * PI / 4);
    data->pika[i][1] += sin(data->pika[i][2] * PI / 4);
    if (!(data->pika[i][3] % (16 + i)))
        data->pika[i][2] += 1 - 2 * (data->pika[i][2] % 2);
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        animation handler for ball throw
        move it 1 pixel, change its sprite
        if ball touch a pika, its time is negative
            in this case, the catching ball animation is played
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    move_ball(t_data2 *data)
{
    if (data->time_frame % (TIME_BALL))
        return ;
    if (data->ball_throw.time < 0)
    {
        draw_circle(data, (t_circle){data->ball_throw.x + BALL_SIZE / 2, data->ball_throw.y + BALL_SIZE / 2, -data->ball_throw.time, random_white()});
        if (data->ball_throw.time == -5)
            data->pika[data->ball_throw.pika_caught][0] = -1;
        if (data->ball_throw.time == -1)
            data->map[(int)round(data->ball_throw.x / SPRITE_SIZE)][(int)round(data->ball_throw.y / SPRITE_SIZE)] = 'c';
        data->ball_throw.time++;
        return ;
    }
    data->ball_throw.x += cos(data->ball_throw.n0123 * PI / 2);
    data->ball_throw.y += sin(data->ball_throw.n0123 * PI / 2);
    if (!(data->ball_throw.time % 5))
        data->ball_throw.frame = (data->ball_throw.frame + 1) % 12;
    if (data->ball_throw.time == 1)
        data->map[(int)round(data->ball_throw.x / SPRITE_SIZE)][(int)round(data->ball_throw.y / SPRITE_SIZE)] = 'C';
    data->ball_throw.time--;
}


// void    move_pika(t_data2 *data, int i)
// {

//     int direction = data->pika[i][2] / 2;
//     int co = (int)cos(direction * PI / 2);
//     int si = (int)sin(direction * PI / 2);
    
//     if (abs(data->time_frame - data->pika[i][3]) % SLOWING + i)
//         return ;
//     data->pika[i][0] += co;
//     data->pika[i][1] += si;
//     if (!((data->pika[i][0] + data->pika[i][1]) % SPRITE_SIZE % 8))
//         data->pika[i][2] += 1 - 2 * (data->pika[i][2] % 2);
//     if (((data->pika[i][0] + data->pika[i][1]) % SPRITE_SIZE == 63 && co + si > 0) || 
//         ((data->pika[i][0] + data->pika[i][1]) % SPRITE_SIZE == 1 && co + si < 0))
//     {
//         data->pika[i][0] += co;
//         data->pika[i][1] += si;
//         data->pika[i][2] += 1 - 2 * (data->pika[i][2] % 2);
//         data->pika[i][3] = -1;
//     }
// }
