/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:55:43 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 17:16:24 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft.h"

# define ERR "\033[0;31mError - \e[0m"
# define ERRM "\033[0;32mError - \e[0m"
# define PI 3.14159265358979323846

///////////////////////////////////////////////////////////////////////////////]
//
//			▒█▀▄▀█ ░█▀▀█ ▒█▄░▒█ ▒█▀▀▄ ░█▀▀█ ▀▀█▀▀ ▒█▀▀▀█ ▒█▀▀█ ▒█░░▒█
//			▒█▒█▒█ ▒█▄▄█ ▒█▒█▒█ ▒█░▒█ ▒█▄▄█ ░▒█░░ ▒█░░▒█ ▒█▄▄▀ ▒█▄▄▄█
//			▒█░░▒█ ▒█░▒█ ▒█░░▀█ ▒█▄▄▀ ▒█░▒█ ░▒█░░ ▒█▄▄▄█ ▒█░▒█ ░░▒█░░
//
///////////////////////////////////////////////////////////////////////////////]
# define ANIM_1 50
# define ANIM_T 200
# define TIME_F 4096
# define MAX_CHANCE 5000

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
	int		i;
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

	int		map_x;
	int		map_y;

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

	int		is_dying;
}	t_data;

///////////////////////////////////////////////////////////////////////////////]
/********************************
		[A] MAPPING
********************************/
int		fill_map(t_data *data, int fd_map);
int		count_check(t_data *data);
/********************************
		[B] PATHING
********************************/
void	is_map_ok(t_data *data, char *path);
int		valid_path(t_data *data);
/********************************
		[B] PATHING 2
********************************/
int		check_path_player(t_data *data, int dx, int dy);
int		check_path_pika(t_data *data, int i, int random);
/********************************
		[C] RENDERING
********************************/
int		render(t_data *data);
void	put_background(t_data *data);
void	put_foreground(t_data *data);
void	ini_texture(t_data *data);
/********************************
		[D] MOVING PARTS
********************************/
int		key_press(int keysym, t_data *data);
void	f_move_player(t_data *data);
void	f_move_pika(t_data *data);
void	anim_pika(t_data *data, int i);
/********************************
		[Z] OUTILS
********************************/
int		exit_all(t_data *data);
int		exit_all_2(t_data *data, char *string);
void	put_map(char *txt, char **map);

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
