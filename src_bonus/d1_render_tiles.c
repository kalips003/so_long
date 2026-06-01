#include "so_long_bonus.h"

void	ft_put_tile(t_data2 *data, int x, int y, t_img img);
void	put_background_to_buffer(t_data2 *data);
void	put_small_background_to_buffer(t_data2 *data);
static	void	h_444(t_data2 *data, int x, int y);
static	void	h_555(t_data2 *data, t_npc	npc);

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	efficient put sprite to buffer
	doesnt ask questions
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
// 		main render for the full the map
void	put_background_to_buffer(t_data2 *data)
{
	int x;
	int y;

	y = -1;
	while (++y < data->map_y)
	{
		x = -1;
		while (++x < data->map_x)
			h_444(data, x, y);
	}
}

// 		redraw only around players
void	put_small_background_to_buffer(t_data2 *data)
{
	int	i;

	h_555(data, data->player);
	i = -1;
	while (++i < data->num_pika)
		h_555(data, data->pika[i]);
	if (data->throw.ball.time)
		h_555(data, data->throw.ball);
}

// 														HELPER - put one sprite
static	void	h_444(t_data2 *data, int x, int y)
{
	if (data->map[y][x] == '1')
		ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_wall);
	else if (data->map[y][x] == '0' || data->map[y][x] == 'P' || data->map[y][x] == 'z')
		ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_ground[0]);
	else if (data->map[y][x] == '*')
		ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_ground[1]);
	else if (data->map[y][x] == 'C' || data->map[y][x] == 'c')
		ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_ball[(data->map[y][x] == 'c')]);
	else if (data->map[y][x] == 'E')
		ft_put_tile(data, x * SPRITE_SIZE, y * SPRITE_SIZE, data->i_exit[0 + data->exit[2]]);
}

// 										   HELPER - render 4 direction (cross)
static	void	h_555(t_data2 *data, t_npc	npc)
{
	int	x;
	int	y;
	
	x = (int)round(npc.x / SPRITE_SIZE);
	y = (int)round(npc.y / SPRITE_SIZE);
	h_444(data, x, y);
	h_444(data, x + 1, y);
	h_444(data, x - 1, y);
	h_444(data, x, y + 1);
	h_444(data, x, y - 1);
}
