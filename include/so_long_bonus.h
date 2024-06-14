/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:30 by marvin            #+#    #+#             */
/*   Updated: 2024/06/11 18:33:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx_linux/mlx.h"
// # include <X11/X.h>
// # include <X11/keysym.h>
# include <math.h>
# include <sys/stat.h>
// # include <sys/wait.h>

# include "libft.h"

# define PI 3.14159265358979323846

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
# define PIKA_MOVE_CHANCE 16
# define ATTACK_CHANCE 1
# define PIKA_TURN_CHANCE 8
# define ATTAK_TIME 100
# define CHANNELING_TIME -80
# define MAX_ENDURANCE 1000
# define TIME_TO_DIE -500


# define START_X_SCORE 75
# define START_Y_SCORE -75
# define DECIMAL_SCORE -14

#define FRAME_DURATION_MILLISECONDS 17

typedef struct	s_img {
	void	*img;
	char	*addr;

	int		bpp;
	int		ll;
	int		endian;
	int		sz_x;
	int		sz_y;
}			t_img;

typedef struct	s_npc {
	int		x;
	int		y;
	int		f;
	int		time;
	int		dx;
	int		dy;
}			t_npc;

typedef struct	s_circle {
	int	center_x;
	int	center_y;
	int	radius;

	unsigned int 	(*color)(void);
}			t_circle;

typedef struct {
    int sz;

    int frame_start_x;
    int frame_start_y;
	int src_x;
	int src_y;

	int pixel_index;
	unsigned int	pixel_color;

	int	dest_x;
	int	dest_y;

	int buffer_index;

    int i;
    int j;
} t_frame;



typedef struct s_sprite {
	int				i;
	int				j;
	int				f_x;
	int				f_y;
	int				pixel_index;
	unsigned int	pixel_color;
	int				buffer_index;
}	t_sprite;

typedef struct s_event1
{
	t_npc	ball;
	int		pika_caught;
}	t_throw;

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
	t_img	i_player;//	0
	t_img	i_pika;
	t_img	i_ground[2];
	t_img	i_wall;
	t_img	i_ball[2];//	5-6
	t_img	i_big_ball[2];
	t_img	i_throw;
	t_img	i_exit[2];//	10-11
	t_img	i_numbers[10];
//
	void	*mlx;
	void	*win;
	char	**map;
//  	in tiles
	int		time;

	int		map_x;
	int		map_y;

	int		walk_count;
	int		num_ball;
	int		num_collected;
	int		num_holding;
	int		num_pika;
	int		num_pika_caught;

	t_npc	player;
	t_npc	*pika;
	int		exit[5];// exit[2]for is_all_collec [3,4] for ptr

	int 	boy_or_girl;
	int 	running;
	int 	time_freeze;
	int 	starter;
	int 	stamina;

	t_throw		throw;
	t_attack	attack;
}	t_data2;
///////////////////////////////////////////////////////////////////////////////]

///////////////////////////////////////////////////////////////////////////////]
//	  A
int	fill_map_v2(t_data2 *data, int fd_map);
int	count_check_v2(t_data2 *data);
//	  B
int	valid_path_v2(t_data2 *data);
//	  C
void ini_sprites(t_data2 *data);
//	  D1 - RENDERING
void	ft_put_tile(t_data2 *data, int x, int y, t_img img);
void	put_background_to_buffer(t_data2 *data);
void	put_small_background_to_buffer(t_data2 *data);
//	  D2
void	ft_background(t_data2 *data, int sw);
//	  D3
void	ft_foreground(t_data2 *data);
void draw_frame(t_data2 *data, t_img img, int xyfe[4], unsigned int (* color)(void));
//	  E
int	key_press(int keysym, t_data2 *data);
int	key_release(int keysym, t_data2 *data);
//	  E2 - MOVEMENTS
void	f_move_player_v2(t_data2 *data);
void	ft_move_enemy(t_data2 *data);
void	move_ball(t_data2 *data);
//	  E3 - PATHING
int		check_path_npc(t_data2 *data, t_npc npc, int current_pika);
void	check_what_your_walking_on(t_data2 *data);
void	check_throw_path(t_data2 *data);
// 	  F - LOOP
int ft_loop_v2(t_data2 *data);
//	  G2 - COLORS
void	put_pixel_buffer(t_data2 *data, int x, int y, unsigned color);
unsigned int random_white(void);
unsigned int random_yellow(int min_rg, int max_rg);
unsigned int random_yellow_v2(void);
unsigned int random_blue(int min_b, int max_b, int min_rg, int max_rg);
unsigned int random_green_bot(int min_g, int max_g, int min_rb, int max_rb);
unsigned int ft_black(void);
//	  H - RECTANGLES
void	ft_put_rectangle(t_data2 *data, int xy[2], int dxy[2], unsigned int (*color)(void));
void	ft_put_square(t_data2 *data, int xy[2], int size, unsigned int color);
void	draw_gradient_square(t_data2 *img, int x, int y, int len_side, int color);
//	  H2 -  CIRCLES
void	draw_circle(t_data2 *data, t_circle circle);
void	draw_circle_v2(t_data2 *data, t_circle circle, int what_helper);
//	  H3 -  LINES
void draw_line_v2(t_data2 *data, int a[2], int b[2], unsigned int color);
void draw_line_v3(t_data2 *data, int a[2], int b[2], unsigned int (*color)(void));
void draw_line_v4(t_data2 *data, int *a, int *b, unsigned int (*color)(void));
//	  I
void check_attack(t_data2 *data);
//	  Z
int	exit_all_v2(t_data2 *data);
void	ft_break(int n, char *string, t_data2 *data);
///////////////////////////////////////////////////////////////////////////////]
// static void	ft_put_tile(t_data2 *data, int x, int y, t_img img);



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
