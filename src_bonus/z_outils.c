#include "so_long_bonus.h"

int	exit_all_v2(t_data2 *data);
static void destroy_img_v4(t_data2 *d);
void f_print_memory(t_data2 *data);
void f_print_memory_v2(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	exit at any point, with security for all
*******************************************************************************/
int	exit_all_v2(t_data2 *data)
{
	free_tab(data->map);
	if (data->pika)
	{
		// put("PIKA=\n[%*S]\n", sizeof(t_npc), data->pika);
		// put("------->\n");
		free_s(data->pika);
	}
	destroy_img_v4(data);
	if (data->mlx)
	{
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free_s(data->mlx);
	}
	exit(0);
	return (0);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	helper destroy all img in a loop
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void destroy_img_v4(t_data2 *d)
{
	int	i;
	t_img	*curseur;

	curseur = &d->buffer;
	i = -1;
	while (++i <= 21)
	{
		if (curseur->img)
			mlx_destroy_image(d->mlx, curseur->img);
		curseur++;
	}
}

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	print blinking walk count
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void f_print_memory(t_data2 *data)// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
{
	put(CLS"[%#+*S", offsetof(t_data2, time), data);
	put(BLINK RED"[%.8d]"R_BLINK, data->time);
	put("%#+*S", 2 * sizeof(int), &data->map_x);
	put(BLINK BLUE"[%.8d]"R_BLINK, data->walk_count);
	put("%#+*S]", sizeof(t_data2) - offsetof(t_data2, num_ball), &data->num_ball);
	put("\nPIKA--->:\n%#*.4S<---\n", sizeof(t_npc) * data->num_pika, &data->pika[0]);
	put("MAP=\n%.1t\n", data->map);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	print for testing
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// void f_print_memory_v2(t_data2 *data)
// {
// 	put("\nsz_x = %d, sz_y = %d\n", data->buffer.sz_x, data->buffer.sz_y);
// 	put("\nmap = \n%+#*S\n", 10, data->buffer.addr);
// }
void	ft_break(int n, char *string, t_data2 *data);
void	ft_break(int n, char *string, t_data2 *data)
{
	f_print_memory(data);
	put(BLINK COLOR_3R_0G_1B"\nBREAK ( %d ) ---------------------->\n"RESET, n);
	put(COLOR_4R_4G_1B"> %s\n", string);
	// put("> %s\n"RESET, string);
	put(BLINK COLOR_1R_4G_2B"\n\t\t>>> PRESS ENTER TO CONTINUE <<<\n"RESET);
	free_s(gnl(0));
}



///////////////////////////////////////////////////////////////////////////////]
// 														OLD VERSION WITHOUT LOOP
// static void destroy_img_v3(t_data2 *d)
// {
// 	int	i;
// 
// 	if (d->i_ground[0].img)
// 		mlx_destroy_image(d->mlx, d->i_ground[0].img);
// 	if (d->i_ground[1].img)
// 		mlx_destroy_image(d->mlx, d->i_ground[1].img);
// 	if (d->i_wall.img)
// 		mlx_destroy_image(d->mlx, d->i_wall.img);
// 	if (d->i_exit[0].img)
// 		mlx_destroy_image(d->mlx, d->i_exit[0].img);
// 	if (d->i_exit[1].img)
// 		mlx_destroy_image(d->mlx, d->i_exit[1].img);
// 	if (d->i_ball[0].img)
// 		mlx_destroy_image(d->mlx, d->i_ball[0].img);
// 	if (d->i_ball[1].img)
// 		mlx_destroy_image(d->mlx, d->i_ball[1].img);
// 	if (d->buffer.img)
// 		mlx_destroy_image(d->mlx, d->buffer.img);
// 	if (d->i_player.img)
// 		mlx_destroy_image(d->mlx, d->i_player.img);
// 	if (d->i_big_ball[0].img)
// 		mlx_destroy_image(d->mlx, d->i_big_ball[0].img);
// 	if (d->i_big_ball[1].img)
// 		mlx_destroy_image(d->mlx, d->i_big_ball[1].img);
// 	if (d->i_throw.img)
// 		mlx_destroy_image(d->mlx, d->i_throw.img);
// 	if (d->i_numbers.img)
// 		mlx_destroy_image(d->mlx, d->i_numbers.img);
// 	i = -1;
// 	while (++i < 8)
// 		if (d->i_pika[i].img)
// 			mlx_destroy_image(d->mlx, d->i_pika[i].img);
// }
///////////////////////////////////////////////////////////////////////////////]
