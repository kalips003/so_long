# include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
░█████╗░  ███████╗░█████╗░██╗██████╗░███████╗
██╔══██╗  ██╔════╝██╔══██╗██║██╔══██╗██╔════╝
███████║  █████╗░░███████║██║██████╔╝█████╗░░
██╔══██║  ██╔══╝░░██╔══██║██║██╔══██╗██╔══╝░░
██║░░██║  ██║░░░░░██║░░██║██║██║░░██║███████╗
╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚══════╝



bulbizare create grass behind him, grass is 0 or '*'

! PRINT MEMORY REAL TIME

use empty sprites to create elec sprites rendered when player time < 0



///////////////////////////////////////////////////////////////////////////////]
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
///////////////////////////////////////////////////////////////////////////////]
// Method 2: Use a compound literal (since C99)
// draw_line(data, (int[]){some_variable + 123, 59}, int b[2], int color);

lib > comment line of norm size\
random cat color makefile
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static void boy_or_girl(t_data2 *data)
{
    char *answer;

    put(COLOR_3R_0G_0B"Are you a boy or a girl?\n\t: "RESET);
    answer = gnl(0);
    if (find_str(answer, "boy") >= 0)
        data->boy_or_girl = 0;
    else if (find_str(answer, "girl") >= 0)
        data->boy_or_girl = 1;
    else
        data->boy_or_girl = 2;
    free_s(answer);
}

int main(int ac, char **av)
{
	t_data2  data;

    if (ac != 2)
        return (put("bad arguments\n"), 1);
    is_map_ok_v2(&data, av[1]);
    boy_or_girl(&data);
////////////////////////////////////////
	data.mlx = mlx_init();
    if (!data.mlx)
        exit_all_v2(&data);
    ini_sprites(&data);
    //<?> - - -- - - - - </?>
    // put("%2t", data.map);
    // f_print_memory(&data);
    put(COLOR_2R_3G_3B"--------------------------->player[3] = %d\n"RESET, data.player[3]);
////////////////////////////////////////
    mlx_loop_hook(data.mlx, &ft_loop, &data);
    mlx_hook(data.win, KeyPress, KeyPressMask, &key_press_v2, &data);
    mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data);
    mlx_hook(data.win, 17, 0, &exit_all_v2, &data);
	mlx_loop(data.mlx);
////////////////////////////////////////
    exit_all_v2(&data);
}
