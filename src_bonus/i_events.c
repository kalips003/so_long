#include "so_long_bonus.h"

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
        if (data->pika[i].x != 0)
            continue ;
        dist = abs(data->player.x - data->pika[i].x) + abs(data->player.y - data->pika[i].y);
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
void find_pika_for_attak(t_data2 *data)
{
	int i;
	double angle;

	i = helper_78(data);
	if (i < 0)
		return ;
	data->attack.pika_attaking = i;
	data->attack.circle.center_x = data->pika[data->attack.pika_attaking].x + DEMI_SPRITE - 1;
	data->attack.circle.center_y = data->pika[data->attack.pika_attaking].y + DEMI_SPRITE - 1;
	data->attack.circle.color = random_yellow_v2;
	data->attack.circlend.center_x = data->player.x + DEMI_SPRITE - 1;
	data->attack.circlend.center_y = data->player.y + DEMI_SPRITE - 1;
	data->attack.circlend.color = random_yellow_v2;
	data->pika[i].time = -1;
	angle = atan2(data->player.y - data->pika[i].y, data->player.x - data->pika[i].x);
	if (angle < 0)
		angle += 2 * PI;
	data->pika[i].f = ((int)round(angle / (PI / 2)) % 4) * 2;
	data->attack.time = CHANNELING_TIME;

}

///////////////////////////////////////////////////////////////////////////////]
// calculating the perpendicular distance from the player's position to the line segment
// prerequisite attack.time > 0
int is_player_touched(int atk_start_xy[2], int atk_end_xy[2], int player_xy[2])
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


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    render_attack, advance time of the atk
    burns the ground at the end (time == 1)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void	render_attack(t_data2 *data)
{
	t_attack	atk;

	atk = data->attack;
	if (data->time == -1)
		atk.time = ATTAK_TIME;
	if (data->time == 1)
	{
		data->pika[atk.pika_attaking].time = 0;
		data->map[(int)round((double)atk.circlend.center_y / SPRITE_SIZE - 0.5)]\
				[(int)round((double)atk.circlend.center_x / SPRITE_SIZE - 0.5)] = '*';
	}
	if (atk.time < 0)
	{
		atk.circlend.radius = -data->attack.time / 4;
		atk.circle.radius = -(CHANNELING_TIME - data->attack.time) / 4;
		draw_circle(data, atk.circle);
		draw_circle(data, atk.circlend);
	}
	else
		draw_line_v4(data, &atk.circle.center_x, &atk.circlend.center_x, random_yellow_v2);
	atk.time += 1 - 2 * (atk.time > 0);
}
