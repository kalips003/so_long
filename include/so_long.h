#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "libft.h"


typedef struct	s_img {
	void	*img;
	char	*addr;

	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct	s_circle {
	int     center_x;
	int     center_y;
	int     radius;

	int		color;
}			t_circle;


# define ANIM_1 50
# define ANIM_T 200
# define TIME_F 1024
# define MAX_CHANCE 5000


#define PI 3.14159265358979323846

typedef struct s_coor
{
	int	x;
	int	y;
}	t_coor;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	t_img	buffer;

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



/********************************
			MAIN
********************************/
void 	is_map_ok(t_data *data, char *path);


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
// static int    check_cardinal(t_data *data, char **map)
// static int find_next_to_explore(t_data *data, char **map_path)
int 	valid_path(t_data *data);
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

int	key_release(int keysym, t_data *data);
/********************************
		[E] THUNDERBOLT
********************************/
void draw_square_2(t_data *data, int x, int y, int len_side);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/********************************
		OUTILS
********************************/
int    exit_all(t_data *data);

/********************************
		OUTILS 2
********************************/


#endif
