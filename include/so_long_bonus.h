/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:30 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 17:22:53 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include "../mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft.h"

# define PI 3.14159265358979323846

///////////////////////////////////////////////////////////////////////////////]
//
//						▒█▀▀█ ▒█▀▀▀█ ▒█▄░▒█ ▒█░▒█ ▒█▀▀▀█
//						▒█▀▀▄ ▒█░░▒█ ▒█▒█▒█ ▒█░▒█ ░▀▀▀▄▄
//						▒█▄▄█ ▒█▄▄▄█ ▒█░░▀█ ░▀▄▄▀ ▒█▄▄▄█
//
///////////////////////////////////////////////////////////////////////////////]

# define TIME_F 4096

# define SZ 64
# define HALF 32
# define BALL_SIZE 16
# define HIT_BOX 34

# define BLACK_BOT 80
# define BOT_STAMINA -10
# define BALL_START_X 72
# define OFFSET_BALL 30
# define PIKA_START_X 150
# define BALL_START_Y 8

# define SLOWING 8
# define TIME_PLAYER 2
# define TIME_PIKA 2
# define TIME_BALL 1
# define TIME_ATK 1
# define THROW_RANGE 4
# define THROW_SPEED 4
# define OFF_B 22
# define PIKA_MOVE_CHANCE 128
# define ATTACK_CHANCE 100
# define PIKA_TURN_CHANCE 8
# define ATTAK_TIME 100
# define ATTAK_TIME_2 64
# define CHANNELING_TIME -120
# define MAX_ENDURANCE 500
# define TIME_TO_DIE -300
# define PLAYER_SPEED 2

# define START_X_SCORE 80
# define END_X_BB 132
# define START_Y_SCORE -75
# define DECIMAL_SCORE -40

# define FRAME_DURATION_MILLISECONDS 17

typedef struct s_img
{
	void	*img;
	char	*addr;

	int		bpp;
	int		ll;
	int		end;
	int		sz_x;
	int		sz_y;
}	t_img;

typedef struct s_npc
{
	int		x;
	int		y;
	int		f;
	int		time;
	int		dx;
	int		dy;
}	t_npc;

typedef struct s_circle
{
	int				x;
	int				y;
	int				rad;
	unsigned int	(*color)(void);
}	t_circle;

typedef struct s_frame
{
	int				sz;

	int				fsx;
	int				fsy;
	int				src_x;
	int				src_y;

	int				pix_i;
	unsigned int	pix_c;

	int				dest_x;
	int				dest_y;

	int				buf_i;

	int				i;
	int				j;
}	t_frame;

typedef struct s_sprite
{
	int				i;
	int				j;
	int				f_x;
	int				f_y;
	int				pix_i;
	unsigned int	pix_c;
	int				buf_i;
}	t_sprite;

typedef struct s_event1
{
	t_npc	ball;
	int		pika_caught;
}	t_throw;

typedef struct s_event2
{
	t_circle	circle;
	t_circle	circlend;
	int			dx;
	int			dy;
	int			time;
	int			enemy;
}	t_attack;

///////////////////////////////////////////////////////////////////////////////]
// exit[2]for is_all_collec [3,4] for ptr
typedef struct s_data2
{
	t_img			buffer;

	t_img			i_player;
	t_img			i_pika;
	t_img			i_ground[2];
	t_img			i_wall;
	t_img			i_ball[2];
	t_img			i_big_ball[2];
	t_img			i_throw;
	t_img			i_exit[2];
	t_img			i_numbers[10];

	void			*mlx;
	void			*win;
	char			**map;

	unsigned int	(*color)(void);
	unsigned int	(*color_r)(void);

	int				time;

	t_throw			throw;
	t_attack		attack;
	t_npc			player;
	t_npc			*pika;

	int				exit[5];

	int				steps;
	int				map_x;
	int				map_y;

	int				n_ball;
	int				n_collec;
	int				n_hold;
	int				n_pika;
	int				n_gotta;

	int				boy_or_girl;
	int				starter;
	int				running;
	int				stamina;
	int				tmp_bit;
	int				is_winning;
}	t_data2;
///////////////////////////////////////////////////////////////////////////////]

///////////////////////////////////////////////////////////////////////////////]
//	  A
int				fill_map_v2(t_data2 *data, int fd_map);
int				count_check_v2(t_data2 *data);
//	  B
int				valid_path_v2(t_data2 *data);
//	  C
void			ini_sprites(t_data2 *data);
//	  D1
void			ft_put_tile(t_data2 *data, int x, int y, t_img img);
void			put_background_to_buffer(t_data2 *data);
void			put_small_background_to_buffer(t_data2 *data);
//	  D2
void			ft_background(t_data2 *data, int sw);
//	  D3
void			ft_foreground(t_data2 *data);
void			draw_frame(t_data2 *data, t_img img, int xyfe[4], unsigned int \
(*color)(void));
//	  E
int				key_press(int keysym, t_data2 *data);
int				key_release(int keysym, t_data2 *data);
//	  E2
void			f_move_player_v2(t_data2 *data);
void			ft_move_enemy(t_data2 *data);
void			move_ball(t_data2 *data);
//	  E3
int				check_path_npc(t_data2 *data, t_npc npc, int current_pika);
void			check_what_your_walking_on(t_data2 *data);
void			check_throw_path(t_data2 *data);
int				is_touched(int *atk_start_xy, int *atk_end_xy, int *player_xy);
// 	  F
int				ft_loop_v2(t_data2 *data);
//	  G2
void			put_pixel_buffer(t_data2 *data, int x, int y, unsigned int co);
unsigned int	ft_yellow(void);
unsigned int	ft_green(void);
unsigned int	ft_red(void);
unsigned int	ft_blue(void);
// 	  G3	11
unsigned int	ft_r_yellow(void);
unsigned int	ft_r_green(void);
unsigned int	ft_r_red(void);
unsigned int	ft_r_blue(void);
// 	  G4	11
unsigned int	ft_black(void);
unsigned int	ft_white(void);
unsigned int	ft_r_white(void);
//	  H - RECTANGLES
void			ft_put_rectangle(t_data2 *data, int xy[2], int dxy[2], \
unsigned int (*color)(void));
void			ft_put_square(t_data2 *data, int xy[2], int size, \
unsigned int color);
//	  H2 -  CIRCLES
void			draw_circle(t_data2 *data, t_circle circle);
void			draw_circle_v2(t_data2 *data, t_circle circle, int what_helper);
//	  H3 -  LINES
void			draw_line_v2(t_data2 *data, int a[2], int b[2], \
unsigned int color);
void			draw_line_v3(t_data2 *data, int a[2], int b[2], \
unsigned int (*color)(void));
void			draw_line_v4(t_data2 *data, int *a, int *b, \
unsigned int (*color)(void));
//	  I
void			check_attack(t_data2 *data);
// 	  Y
void			is_map_ok_v2(t_data2 *data, char *path);
void			what_starter(t_data2 *data);
void			boy_or_girl(t_data2 *data);
double			distance_squared(int x1, int y1, int x2, int y2);
void			ft_1(t_data2 *data);
//	  Z
int				exit_all_v2(t_data2 *data);
void			print_data(t_data2 *data);

///////////////////////////////////////////////////////////////////////////////]
# define MSG_DEAD "\e[5m\033[38;5;196m\n\
\t██╗░░░██╗░█████╗░██╗░░░██╗  ██████╗░██╗███████╗██████╗░\n\
\t╚██╗░██╔╝██╔══██╗██║░░░██║  ██╔══██╗██║██╔════╝██╔══██╗\n\
\t░╚████╔╝░██║░░██║██║░░░██║  ██║░░██║██║█████╗░░██║░░██║\n\
\t░░╚██╔╝░░██║░░██║██║░░░██║  ██║░░██║██║██╔══╝░░██║░░██║\n\
\t░░░██║░░░╚█████╔╝╚██████╔╝  ██████╔╝██║███████╗██████╔╝\n\
\t░░░╚═╝░░░░╚════╝░░╚═════╝░  ╚═════╝░╚═╝╚══════╝╚═════╝░\e[25m\n\n"

# define MSG_WIN "\e[5m\033[38;5;77m\n\
\t██╗░░░██╗░█████╗░██╗░░░██╗  ░██╗░░░░░░░██╗██╗███╗░░██╗  ██╗\n\
\t╚██╗░██╔╝██╔══██╗██║░░░██║  ░██║░░██╗░░██║██║████╗░██║  ██║\n\
\t░╚████╔╝░██║░░██║██║░░░██║  ░╚██╗████╗██╔╝██║██╔██╗██║  ██║\n\
\t░░╚██╔╝░░██║░░██║██║░░░██║  ░░████╔═████║░██║██║╚████║  ╚═╝\n\
\t░░░██║░░░╚█████╔╝╚██████╔╝  ░░╚██╔╝░╚██╔╝░██║██║░╚███║  ██╗\n\
\t░░░╚═╝░░░░╚════╝░░╚═════╝░  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝  ╚═╝\e[25m\n\n"

#endif
