#include "so_long_bonus.h"

void	ft_put_tile(t_data2 *data, int x, int y, t_img img)
{
	t_sprite	s;

	s.i = -1;
	while (++s.i < img.sz_x)
	{
		s.j = -1;
		while (++s.j < img.sz_y)
		{
			s.pixel_color = *(int *)(img.addr + s.j * img.ll + s.i * img.bpp / 8);
			s.buffer_index = (y + s.j) * data->buffer.ll + (x + s.i) * (data->buffer.bpp / 8);
			*((unsigned int *)(data->buffer.addr + s.buffer_index)) = s.pixel_color;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
//      clean the bottom
static void	put_black_background(t_data2 *data)
{
	int	i;
	int	j;
	int	buffer_index;

	j = data->map_y * SPRITE_SIZE - 1;
	while (++j < data->buffer.sz_y)
	{
		i = -1;
		while (++i < data->buffer.sz_x)
		{
			buffer_index = j * data->buffer.ll + i * (data->buffer.bpp / 8);
			*(int *)(data->buffer.addr + buffer_index) = 0x00000000;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// 		main render of the map
void	put_background_to_buffer(t_data2 *data)
{
	int x;
	int y;

	y = -1;
	while (++y < data->map_y)
	{
		x = -1;
		while (++x < data->map_x)
		{
			if (data->map[y][x] == '1')
				ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_wall);// <!> - - - - - - - - - - - - - - - - - </?>
			else if (data->map[y][x] == '0' || data->map[y][x] == 'P' || data->map[y][x] == 'z')
				ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_ground[0]);
			else if (data->map[y][x] == '*')
				ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_ground[1]);
			else if (data->map[y][x] == 'C' || data->map[y][x] == 'c')
				ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_ball[(data->map[y][x] == 'c')]);
			else if (data->map[y][x] == 'E')
				ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_exit[0 + data->exit[2]]);
		}
	}
	put_black_background(data);
}

///////////////////////////////////////////////////////////////////////////////]
// update stamina, and render it
static void	ft_stamina(t_data2 *data)
{
	int i;
	int j;
	int current_stamina;

	if (data->running)
		data->stamina = max(data->stamina - 1, 0);
	else
		data->stamina = min(data->stamina + 1, MAX_ENDURANCE);
	current_stamina = (int)(((double)data->stamina / MAX_ENDURANCE) * data->buffer.sz_x);
	i = data->buffer.sz_y + BOT_STAMINA - 1;
	while (++i < data->buffer.sz_y)
	{
		j = -1;
		while (++j < current_stamina)
			put_pixel_buffer(data, j, i, random_green_bot(128, 255, 0, 25));
	}
}

///////////////////////////////////////////////////////////////////////////////]
//      put retrieved balls and caught pika on bottom
static void put_balls_foreground(t_data2 *data)
{
    int i;
    int x;
	int y;

    y = data->map_y * SPRITE_SIZE + BALL_START_Y;
    i = -1;
    while (++i < data->num_holding)
    {
        x = data->map_x * SPRITE_SIZE - BALL_START_X * (i + 1);
        f_put_sprite_to_buffer(data, x, y, data->i_big_ball[0]);
    }
    i = -1;
    while (++i < data->num_pika_caught)
    {
        x = PIKA_START_X + BALL_START_X * i;
        f_put_sprite_to_buffer(data, x, y, data->i_big_ball[1]);
    }
}
// draw_frame(t_data2 *data, t_img img, int xyfe[4], int (* color)(void));
///////////////////////////////////////////////////////////////////////////////]
// 			UPDATE THE BACKGROUND
void	background(t_data2 *data)
{
	put_background_to_buffer(data);
	put_black_background(data);
	ft_stamina(data);
	put_balls_foreground(data);
}
