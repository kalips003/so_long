#include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
// return the n*i of the closest pika
static int  helper_78(t_data2 *data)
{
    int i;
    int dist;
    int saved_smallest;
    int saved_pika;

    saved_smallest = INT_MAX;
    i = -1;
    while (++i < data->num_pika)
    {
        if (data->pika[i][0] != 0)
            continue ;
        dist = abs(data->player[0] - data->pika[i][0]) + abs(data->player[1] - data->pika[i][1]);
        if (dist < saved_smallest)
        {
            saved_smallest = dist;
            saved_pika = i;
        }
    }
    if (saved_smallest == INT_MAX)
        return (-1);
    else
        return (saved_pika);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    find closest pika available, 
    if it exist, fill attack struct
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void find_pika_for_attak(t_data2 *data)
{
    int i;
    double angle;

    i = helper_78(data);
    if (i < 0)
        return ;
    data->attack.pika_attaking = i;
    data->attack.circle.center_x = data->pika[data->attack.pika_attaking][0] + DEMI_SPRITE;
    data->attack.circle.center_y = data->pika[data->attack.pika_attaking][1] + DEMI_SPRITE;
    data->attack.circle.color = random_yellow_v2;
    data->attack.circlend.center_x = data->player[0] + DEMI_SPRITE;
    data->attack.circlend.center_y = data->player[1] + DEMI_SPRITE;
    data->attack.circlend.color = random_yellow_v2;
    data->pika[i][3] = -1; 
    angle = atan2(data->player[1] - data->pika[i][1], data->player[0] - data->pika[i][0]);
    if (angle < 0)
        angle += 2 * PI;
    data->pika[i][2] = ((int)round(angle / (PI / 2)) % 4) * 2;
    data->attack.time = CHANNELING_TIME;

}

///////////////////////////////////////////////////////////////////////////////]
// calculating the perpendicular distance from the player's position to the line segment
// prerequisite attack.time > 0
static int is_player_touched(int atk_start_xy[2], int atk_end_xy[2], int player_xy[2])
{
    double t;
    double proch_x;
    double proch_y;
    double dist_squared;
    
    t = ((player_xy[0] - atk_start_xy[0]) * (atk_end_xy[0] - atk_start_xy[0]) +
        (player_xy[1] - atk_start_xy[1]) * (atk_end_xy[1] - atk_start_xy[1])) /
        ((atk_end_xy[0] - atk_start_xy[0]) * (atk_end_xy[0] - atk_start_xy[0]) +
        (atk_end_xy[1] - atk_start_xy[1]) * (atk_end_xy[1] - atk_start_xy[1]));
    t = fmax(0.0, fmin(1.0, t));
    proch_x = atk_start_xy[0] + t * (atk_end_xy[0] - atk_start_xy[0]);
    proch_y = atk_start_xy[1] + t * (atk_end_xy[1] - atk_start_xy[1]);
    dist_squared = (player_xy[0] - proch_x) * (player_xy[0] - proch_x) +
                    (player_xy[1] - proch_y) * (player_xy[1] - proch_y);
    return (dist_squared <= HIT_BOX * HIT_BOX);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
decide each loop if a pika shall attak
if there is an attack ongoing, check if player touched
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    check_random_attak(t_data2 *data)
{
    if (data->attack.time > 0)
        if (is_player_touched(&data->attack.circle.center_x, &data->attack.circlend.center_x, &data->player))
            data->player[3] = -1;
    if (data->attack.time || !data->num_pika || (rand() % (ATTACK_CHANCE + 1)))
        return ;
    find_pika_for_attak(data);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    render_attack, advance time of the atk
    burns the ground at the end (time == 1)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    render_attack(t_data2 *data)
{
    t_attack atk;

    atk = data->attack;
    if (!data->attack.time)
        return ;
    if (atk.time < 0)
    {
        atk.circlend.radius = -data->attack.time / 4;
        atk.circle.radius = -(CHANNELING_TIME - data->attack.time) / 4;
        return (draw_circle(data, atk.circle), draw_circle(data, atk.circlend));
    }
    else
        draw_line_v4(data, &atk.circle.center_x, &atk.circlend.center_x, random_yellow_v2);
    if (data->time_frame == -1)
        atk.time = ATTAK_TIME;
    else if (data->time_frame == 1)
    {
        data->pika[atk.pika_attaking][3] = 0;
        data->map[(int)round((atk.circlend.center_y - DEMI_SPRITE) / SPRITE_SIZE)][(int)round((atk.circlend.center_x - DEMI_SPRITE) / SPRITE_SIZE)] = '*';
    }
    if (!(data->time_frame % TIME_ATK))
        atk.time += 1 - 2 * (atk.time > 0);
}
