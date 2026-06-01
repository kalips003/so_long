#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx_linux/mlx.h"
// # include <X11/X.h>
// # include <X11/keysym.h>
# include <math.h>
# include <sys/stat.h>
// # include <sys/wait.h>

# include "libft.h"


# define ERR "\033[0;31mError - \e[0m"
# define PI 3.14159265358979323846

///////////////////////////////////////////////////////////////////////////////]
//
//			▒█▀▄▀█ ░█▀▀█ ▒█▄░▒█ ▒█▀▀▄ ░█▀▀█ ▀▀█▀▀ ▒█▀▀▀█ ▒█▀▀█ ▒█░░▒█
//			▒█▒█▒█ ▒█▄▄█ ▒█▒█▒█ ▒█░▒█ ▒█▄▄█ ░▒█░░ ▒█░░▒█ ▒█▄▄▀ ▒█▄▄▄█
//			▒█░░▒█ ▒█░▒█ ▒█░░▀█ ▒█▄▄▀ ▒█░▒█ ░▒█░░ ▒█▄▄▄█ ▒█░▒█ ░░▒█░░
//
///////////////////////////////////////////////////////////////////////////////]
typedef struct s_coor
{
	int	x;
	int	y;
}	t_coor;

typedef struct s_valid_path
{

	char	**map;
	int		how_many;
	int		x;
	int		y;
	int 	i;
}	t_valid_path;

///////////////////////////////////////////////////////////////////////////////]
typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;

	void	*img_player[16];
	void	*img_pika[16];
	void	*img_ground;
	void	*img_wall;
	void	*img_ball;
	void	*img_exit;

	int		wid;
	int		hei;
	//  of xpm
	int		map_x;
	int		map_y;
	// of map

	int		num_ball;
	int		num_collected;
	int		num_pika;
	int		walk_count;

	int		player[3];
	int		exit[3];
	int		ptr[2];
	int		(*pika)[3];

	int		time_frame;
	int		player_time;
	int		pika_time[10];

	int 	is_dying;
}	t_data;

///////////////////////////////////////////////////////////////////////////////]
/********************************
		[A] MAPPING
********************************/
int		fill_map(t_data *data, int fd_map);
	// static void copy_posi(t_data *data, int *ptr, int x, int y)
	// static void ft_posi_pika(t_data *data, int x, int y)
	// static int small_check(t_data *data)
int 	count_check(t_data *data);
/********************************
		[B] PATHING
********************************/
void 	is_map_ok(t_data *data, char *path);
	// static int    check_cardinal2(t_data *data, char **map)
	// static int find_next_to_explore2(t_data *data, char **map_path)
int 	valid_path(t_data *data);
/********************************
		[B] PATHING 2
********************************/
	// void static	f_exit(t_data *data)
int 	check_path_player(t_data *data, int dx, int dy);
int 	check_path_pika(t_data *data, int i, int random);
/********************************
		[C] RENDERING
********************************/
int 	render(t_data *data);
void 	put_background(t_data *data);
void 	put_foreground(t_data *data);
// static void ini_anim(t_data *data)
void 	ini_texture(t_data *data);
/********************************
		[D] MOVING PARTS
********************************/
	// static void    f_save_time_player(t_data *data, int dx, int dy, int frame)
int		key_press(int keysym, t_data *data);
void    f_move_player(t_data *data);
void    f_move_pika(t_data *data);
void    anim_pika(t_data *data, int i);
/********************************
		[Z] OUTILS
********************************/
// static void	exit_img(t_data *data)
int		exit_all(t_data *data);
int		exit_all_2(t_data *data, char *string);
void	put_map(char *txt, char **map);
///////////////////////////////////////////////////////////////////////////////]
//
//						▒█▀▀█ ▒█▀▀▀█ ▒█▄░▒█ ▒█░▒█ ▒█▀▀▀█
//						▒█▀▀▄ ▒█░░▒█ ▒█▒█▒█ ▒█░▒█ ░▀▀▀▄▄
//						▒█▄▄█ ▒█▄▄▄█ ▒█░░▀█ ░▀▄▄▀ ▒█▄▄▄█
//
///////////////////////////////////////////////////////////////////////////////]
# define ANIM_1 50
# define ANIM_T 200
# define TIME_F 4096
# define MAX_CHANCE 5000

# define SPRITE_SIZE 64
# define DEMI_SPRITE 32
# define BALL_SIZE 16// * 12 * 16 = 196
# define HIT_BOX 32

# define BLACK_BOT 80
# define BOT_STAMINA -10
# define BALL_START_X 72
# define PIKA_START_X 72
# define BALL_START_Y 8

# define SLOWING 8
# define TIME_PLAYER 2
# define TIME_PIKA 1
# define TIME_BALL 1
# define TIME_ATK 1
# define THROW_RANGE 5
# define OFFSET_BALL_THR 22
# define PIKA_MOVE_CHANCE 5000
# define ATTACK_CHANCE 1
# define PIKA_TURN_CHANCE 8
# define ATTAK_TIME 100
# define CHANNELING_TIME -80
# define MAX_ENDURANCE 10000


# define START_X_SCORE = 5
# define START_Y_SCORE = -5
# define DECIMAL_SCORE = -5

typedef struct	s_img {
	void	*img;
	char	*addr;

	int		bpp;
	int		ll;
	int		endian;
	int		sz_x;
	int		sz_y;
}			t_img;


typedef struct	s_circle {
	int     center_x;
	int     center_y;
	int     radius;

	int 	(*color)(void);
}			t_circle;

typedef struct	s_npc {
	int     x;
	int     y;
	int     f;
	int     time;
	int     dx;
	int     dy;
}			t_npc;


typedef struct s_sprite {
	int				i;
	int				j;
	int				f_x;
	int				f_y;
	int				pixel_index;
	unsigned int	pixel_color;
	int				buffer_index;
}	t_sprite;

typedef struct {
    int sz;

    int frame_start_x;
    int frame_start_y;
	int src_x;
	int src_y;

	int pixel_index;
	int pixel_color;

	int	dest_x;
	int	dest_y;

	int buffer_index;

    int i;
    int j;
} t_frame;

typedef struct s_event1
{
	t_npc	ball;
	int		pika_caught;
}	t_event1;

typedef struct s_event2
{
    t_circle circle;
    t_circle circlend;
	int	time;

	int	pika_attaking;
}	t_attack;

///////////////////////////////////////////////////////////////////////////////]
typedef struct s_data2
{
	t_img	buffer;
//
	t_img	i_player;
	t_img	i_pika[8];
	t_img	i_ground[2];
	t_img	i_wall;
	t_img	i_ball[2];
	t_img	i_big_ball[2];
	t_img	i_throw;
	t_img	i_numbers;
	t_img	i_exit[2];
//
	void	*mlx;
	void	*win;
	char	**map;
//
	//  of xpm
	int		map_x;
	int		map_y;
	// of map

	int		walk_count;
	int		num_ball;
	int		num_collected;
	int		num_holding;
	int		num_pika;
	int		num_pika_caught;

	t_npc	player;
	// int		player[4];
	// int		player[5];	x,y,dx,dy,f
	int		exit[5];// exit[2]for is_all_collec [3,4] for ptr
	int		ptr[2];
	// int		(*pika)[4];
	t_npc		*pika;

	int		time;

	int 	is_all_collected;
	int 	boy_or_girl;
	int 	running;
	int 	time_freeze;
	int 	starter;
	int 	stamina;

	t_event1	throw;
	t_attack	attack;
	// throw_ball_event
}	t_data2;
///////////////////////////////////////////////////////////////////////////////]

///////////////////////////////////////////////////////////////////////////////]
//	  A
int		fill_map_v2(t_data2 *data, int fd_map);
	// static void copy_posi(t_data2 *data, int *ptr, int x, int y)
	// static void ft_posi_pika(t_data2 *data, int x, int y)
	// static int small_check(t_data2 *data)
int 	count_check_v2(t_data2 *data);
//	  B
void 	is_map_ok_v2(t_data2 *data, char *path);
	// static int    check_cardinal2(t_data2 *data, char **map)
	// static int find_next_to_explore2(t_data2 *data, char **map_path)
int 	valid_path_v2(t_data2 *data);
//	  C
	// static int helper_texture(t_data2 *data, char *path, t_img *img, int sw)
	// static void ini_anim_v3(t_data2 *data)
void 	ini_sprites(t_data2 *data);
//	  D
void    f_move_player_v2(t_data2 *data);
void    ft_move_enemy(t_data2 *data);
void    move_pika_v2(t_data2 *data, int i);
void    move_ball(t_data2 *data);
//	  D2
	// static void    f_save_time_player(t_data2 *data, int n0123, int frame);
	// static void    f_save_time_ball(t_data2 *data);
int		key_press_v2(int keysym, t_data2 *data);
int		key_release(int keysym, t_data2 *data);
//	  E
int		check_path_player_v3(t_data2 *data, t_npc npc, int current_pika);
void	check_what_your_walking_on(t_data2 *data);
void 	check_throw_path(t_data2 *data);
//	  F
int 	ft_loop(t_data2 *data);
	// static void ft_stamina(t_data2 *data)
void 	put_background_to_buffer(t_data2 *data);
void 	put_foreground_to_buffer(t_data2 *data);
//	  F2
void	f_put_sprite_to_buffer(t_data2 *data, int x, int y, t_img img);
void	f_put_sprite_to_buffer_v2(t_data2 *data, t_npc npc, t_img img, int (* color)(void));
void	f_put_player_to_buffer_v2(t_data2 *data, int rotation, int (* color)(void));
void	f_put_event_ball_to_buffer_v2(t_data2 *data);
//	  F3
	// static void	put_black_background(t_data2 *data);
void	put_background_to_buffer(t_data2 *data);
	// static void 	ft_stamina(t_data2 *data);
	// static void	put_balls_foreground(t_data2 *data);
void	background(t_data2 *data);
//	  G
void	put_pixel_buffer(t_data2 *data, int x, int y, int color);
int 	random_white(void);
int 	random_yellow(int min_rg, int max_rg);
int 	random_yellow_v2(void);
int 	random_blue(int min_b, int max_b, int min_rg, int max_rg);
int 	random_green_bot(int min_g, int max_g, int min_rb, int max_rb);
int 	ft_black(void);
	// static void helper_v555(int *err, int a[2], int dxy[2], int sxy[2])
void 	draw_line_v2(t_data2 *data, int a[2], int b[2], int color);
void 	draw_line_v3(t_data2 *data, int a[2], int b[2], int (*color)(void));
void	draw_line_v4(t_data2 *data, int a[2], int b[2], int (*color)(void));
//	  H
	// static void helper_v64(t_data2 *data, t_circle *c, int x, int y)
void 	helper_v360(t_data2 *data, t_circle *circle, int x, int y);
void 	draw_circle(t_data2 *data, t_circle circle);
void 	draw_circle_v2(t_data2 *data, t_circle circle, void helper(t_data2 *, t_circle *, int , int));
void 	draw_square_random_yellow(t_data2 *data, int x, int y, int len_side);
//	  I
	// static int  helper_78(t_data2 *data);
void	find_pika_for_attak(t_data2 *data);
int		is_player_touched(int atk_start_xy[2], int atk_end_xy[2], int player_xy[2]);
void	render_attack(t_data2 *data);
//	  Z
	// static void destroy_img_v3(t_data2 *d)
	// static void destroy_img_v4(t_data2 *d)
int		exit_all_v2(t_data2 *data);
int		f_is_dying(t_data2 *data);
void 	f_print_memory_v2(t_data2 *data);
void 	f_print_memory(t_data2 *data);
///////////////////////////////////////////////////////////////////////////////]




# define MSG_DEAD "\e[5m\033[38;5;147m\
/t██╗░░░██╗░█████╗░██╗░░░██╗  ██████╗░██╗███████╗██████╗░\n\
/t╚██╗░██╔╝██╔══██╗██║░░░██║  ██╔══██╗██║██╔════╝██╔══██╗\n\
/t░╚████╔╝░██║░░██║██║░░░██║  ██║░░██║██║█████╗░░██║░░██║\n\
/t░░╚██╔╝░░██║░░██║██║░░░██║  ██║░░██║██║██╔══╝░░██║░░██║\n\
/t░░░██║░░░╚█████╔╝╚██████╔╝  ██████╔╝██║███████╗██████╔╝\n\
/t░░░╚═╝░░░░╚════╝░░╚═════╝░  ╚═════╝░╚═╝╚══════╝╚═════╝░\e[0m\n"

# define MSG_WIN "\e[5m\033[38;5;77m\
\t██╗░░░██╗░█████╗░██╗░░░██╗  ░██╗░░░░░░░██╗██╗███╗░░██╗  ██╗\n\
\t╚██╗░██╔╝██╔══██╗██║░░░██║  ░██║░░██╗░░██║██║████╗░██║  ██║\n\
\t░╚████╔╝░██║░░██║██║░░░██║  ░╚██╗████╗██╔╝██║██╔██╗██║  ██║\n\
\t░░╚██╔╝░░██║░░██║██║░░░██║  ░░████╔═████║░██║██║╚████║  ╚═╝\n\
\t░░░██║░░░╚█████╔╝╚██████╔╝  ░░╚██╔╝░╚██╔╝░██║██║░╚███║  ██╗\n\
\t░░░╚═╝░░░░╚════╝░░╚═════╝░  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝  ╚═╝\e[0m\n"

#endif
