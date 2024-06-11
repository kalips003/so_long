# include "so_long_bonus.h"

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
*******************************************************************************/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
				░█████╗░  ███████╗░█████╗░██╗██████╗░███████╗
				██╔══██╗  ██╔════╝██╔══██╗██║██╔══██╗██╔════╝
				███████║  █████╗░░███████║██║██████╔╝█████╗░░
				██╔══██║  ██╔══╝░░██╔══██║██║██╔══██╗██╔══╝░░
				██║░░██║  ██║░░░░░██║░░██║██║██║░░██║███████╗
				╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚══════╝



bulbizare create grass behind him, grass is 0 or '*'


use empty sprites to create elec sprites rendered when player time < 0



// ### <!> - - - - - - - - - - - </!>
#define DESIRED_FPS 60
#define FRAME_DURATION_MICROSECONDS (1000000 / DESIRED_FPS)

void mainLoop() {
    while (1) {

        startTime = getCurrentTime();
            // Process input, update game state, render graphics, etc.
        frameTime = getCurrentTime() - startTime;

        if (frameTime < FRAME_DURATION_MICROSECONDS) {
            printf("Time difference: %ld microseconds\n", FRAME_DURATION_MICROSECONDS - frameTime);
            usleep(FRAME_DURATION_MICROSECONDS - frameTime);
        }
    }
}
// ### <!> - - - - - - - - - - - </!>

// Method 2: Use a compound literal (since C99)
// draw_line(data, (int[]){some_variable + 123, 59}, int b[2], int color);


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*******************************************************************************
*******************************************************************************/
///////////////////////////////////////////////////////////////////////////////]
void	is_map_ok_v2(t_data2 *data, char *path);
static void what_starter(t_data2 *data);
static void	boy_or_girl(t_data2 *data);

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void what_starter(t_data2 *data)
{
	data->starter = (int)(rand() % 4);
	// random(0,1,2,3) = data->starter;
	// data->function_color_ememy = ??;
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void boy_or_girl(t_data2 *data)
{
	char *answer;

	put(COLOR_3R_2G_1B"Are you a boy or a girl?\n>\t: "RESET);
	answer = gnl(0);
	if (find_str(answer, "boy") >= 0)
		data->boy_or_girl = 0;
	else if (find_str(answer, "girl") >= 0)
		data->boy_or_girl = 1;
	else
		data->boy_or_girl = 2;
	free_s(answer);
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
		MEMSET DATA
	create map, free it in all cases
	do all the tests, exit in case of any error
*******************************************************************************/
void is_map_ok_v2(t_data2 *data, char *path)
{
	int fd_map;

	ft_memset(data, 0, sizeof(t_data2));
// map path end in ".ber"
	if (find_str(path, ".ber") != len(path) - 4)
		(put(ERRM"map name should end with \'.ber\'\n"), exit(1));
// create map struct
	fd_map = open(path, O_RDONLY);
	if (fd_map == -1)
		(perror(ERRM"open"), exit(1));
// fill map
	if (fill_map_v2(data, fd_map) || count_check_v2(data))
		exit_all_v2(data);
// valid path?
	if (valid_path_v2(data))
		exit_all_v2(data);
}

///////////////////////////////////////////////////////////////////////////////]
# define KeyPress 0
# define KeyPressMask 0
# define KeyRelease 0
# define KeyReleaseMask 0

int main(int ac, char **av)
{
	t_data2  data;

	if (ac != 2)
		return (put(ERRM"need one map_argument\n"), 1);
	is_map_ok_v2(&data, av[1]);
	boy_or_girl(&data);
	what_starter(&data);
////////////////////////////////////////
	ini_sprites(&data);
////////////////////////////////////////
	ft_background(&data, 1);
	mlx_loop_hook(data.mlx, &ft_loop_v2, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data);
	mlx_hook(data.win, 17, 0, &exit_all_v2, &data);
	mlx_loop(data.mlx);
////////////////////////////////////////
	exit_all_v2(&data);
}
