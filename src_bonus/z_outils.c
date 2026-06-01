#include "so_long.h"

static void destroy_img_v3(t_data2 *d)
{
	int	i;

	if (d->i_ground[0].img)
		mlx_destroy_image(d->mlx, d->i_ground[0].img);
	if (d->i_ground[1].img)
		mlx_destroy_image(d->mlx, d->i_ground[1].img);
	if (d->i_wall.img)
		mlx_destroy_image(d->mlx, d->i_wall.img);
	if (d->i_exit[0].img)
		mlx_destroy_image(d->mlx, d->i_exit[0].img);
	if (d->i_exit[1].img)
		mlx_destroy_image(d->mlx, d->i_exit[1].img);
	if (d->i_ball[0].img)
		mlx_destroy_image(d->mlx, d->i_ball[0].img);
	if (d->i_ball[1].img)
		mlx_destroy_image(d->mlx, d->i_ball[1].img);
	if (d->buffer.img)
		mlx_destroy_image(d->mlx, d->buffer.img);
	if (d->i_player.img)
		mlx_destroy_image(d->mlx, d->i_player.img);
	if (d->i_big_ball[0].img)
		mlx_destroy_image(d->mlx, d->i_big_ball[0].img);
	if (d->i_big_ball[1].img)
		mlx_destroy_image(d->mlx, d->i_big_ball[1].img);
	if (d->i_ball_throw.img)
		mlx_destroy_image(d->mlx, d->i_ball_throw.img);
	i = -1;
	while (++i < 8)
		if (d->i_pika[i].img)
			mlx_destroy_image(d->mlx, d->i_pika[i].img);
}

///////////////////////////////////////////////////////////////////////////////]
// static void destroy_img_v4(t_data2 *d)
// {
// 	int	i;
// 	t_img	*curseur;

// 	curseur = &d->buffer;
// 	i = -1;
// 	while (++i < 20)
// 	{
// 		if (curseur->img)
// 			mlx_destroy_image(d->mlx, curseur->img);
// 		curseur++;
// 	}
// }

int	exit_all_v2(t_data2 *data)
{
	free_tab(data->map);
	if (data->pika)
		free(data->pika);
	destroy_img_v3(data);
	if (data->mlx)
	{
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
draw growing square around player, leave room for YOU DIED?


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void    f_is_dying(t_data2 *data)
{
	t_circle	circle;

	if (data->player[2] == -(data->buffer.sz_x + data->buffer.sz_y))
	{
		put(CLEAR MSG_DEAD);
		put(MSG_WIN"You died in %d moves, and got %d/%d pokeballs...\n", data->walk_count, data->num_collected, data->num_ball);
		exit_all_v2(data);
	}
	circle.center_x = data->player[0] + DEMI_SPRITE;
	circle.center_y = data->player[1] + DEMI_SPRITE;
	circle.radius = -data->player[2];
	circle.color = random_yellow_v2;
	data->player[3]--;
	draw_circle_v2(data, circle, helper_v360);
	f_put_player_to_buffer_v2(data, data->time_frame % 2, ft_black);
}

void f_print_memory(t_data2 *data)
{
    put(CLS"%#*.*S", offsetof(t_data2, walk_count), sizeof(t_img), data);// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
    put(BLINK"[%.8d]"R_BLINK, data->walk_count);
    put("%#*S", sizeof(t_data2) - offsetof(t_data2, num_ball), &data->walk_count);
    put("\nPIKA--->%#*.4S<---\n", sizeof(int[4]) * data->num_pika, &data->pika[0]);
    // put(CLS"%#*.*S\n", sizeof(t_data2), sizeof(t_img), data);
}

void f_print_memory_v2(t_data2 *data)
{
	int	size;

	size = data->buffer.sz_x * data->buffer.sz_y;
	put("\nsz_x = %d, sz_y = %d\n", data->buffer.sz_x, data->buffer.sz_y);
	put("\nmap = \n%+#*S\n", 10, data->buffer.addr);
}


static void	put_map(char *txt, char **map)
{
	
	if (!map)
		return ;
	put("%s", txt);
	while (*map)
	{
		put("\t%S\n", *map);
		map++;
	}
}