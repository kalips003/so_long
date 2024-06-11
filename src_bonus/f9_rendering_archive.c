#include "so_long_bonus.h"

/*


void	f_put_sprite_to_buffer(t_data2 *data, int x, int y, t_img img);
void	f_put_sprite_to_buffer_v2(t_data2 *data, t_npc npc, t_img img, int (* color)(void));
void	f_put_player_to_buffer_v2(t_data2 *data, int rotation, int (* color)(void));
void	f_put_event_ball_to_buffer_v2(t_data2 *data);
void	f_put_event_ball_to_buffer_v3(t_data2 *data);
void	f_put_player_to_buffer_v4(t_data2 *data);





///////////////////////////////////////////////////////////////////////////////]
// 		put sprite at coordonate xy, avec transparence, not white if negative
// 			used for bottom inventory
void	f_put_sprite_to_buffer(t_data2 *data, int x, int y, t_img img)
{
	t_sprite	s;

	if (x < 0 || y < 0)
		return ((void)put(ERR"------> out of bounds 2\n"));
	s.i = -1;
	while (++s.i < img.sz_x)
	{
		s.j = -1;
		while (++s.j < img.sz_y)
		{
			s.pixel_index = (s.j * img.ll + s.i * (img.bpp / 8));
			s.pixel_color = *(int *)(img.addr + s.pixel_index);
			if (s.pixel_color == 0xFF000000)
				continue ;
			s.buffer_index = (y + s.j) * data->buffer.ll + (x + s.i) * (data->buffer.bpp / 8);
			*((unsigned int *)(data->buffer.addr + s.buffer_index)) = s.pixel_color;
		}
	}
}


// 		put sprite at coordonate xy, avec transparence, white if negative
// 		used for pika, if x or y is negative, skipped
// 		color is passed as function argument
void	f_put_sprite_to_buffer_v2(t_data2 *data, t_npc npc, t_img img, int (* color)(void))
{
	t_sprite	s;

	if (npc.x < 0 || npc.y < 0 || npc.x + img.sz_x >= data->buffer.sz_x || npc.y + img.sz_y >= data->buffer.sz_y)
		return ((void)put(ERR"------> out of bounds 3\n"));
	s.i = -1;
	while (++s.i < img.sz_x)
	{
		s.j = -1;
		while (++s.j < img.sz_y)
		{
			s.pixel_index = (s.j * img.ll + s.i * (img.bpp / 8));
			s.pixel_color = *(int *)(img.addr + s.pixel_index);
			if (s.pixel_color == 0xFF000000)
				continue ;
			if (npc.time < 0)
				s.pixel_color = color();
			s.buffer_index = (npc.y + s.j) * data->buffer.ll + (npc.x + s.i) * (data->buffer.bpp / 8);
			*(unsigned int *)(data->buffer.addr + s.buffer_index) = s.pixel_color;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// 		put sprite player, avec transparence, white if negative
// 			white if negative
void	f_put_player_to_buffer_v2(t_data2 *data, int rotation, int (* color)(void))
{
	t_sprite	img_player;

	img_player.i = -1;
	while (++img_player.i < SPRITE_SIZE)
	{
		img_player.j = -1;
		while (++img_player.j < SPRITE_SIZE)
		{
            if (rotation == 1)
                img_player.f_x = ((SPRITE_SIZE - 1 - img_player.i) + (data->player.f % 4) * SPRITE_SIZE) * (data->i_player.bpp / 8);
            else
                img_player.f_x = (img_player.i + (data->player.f % 4) * SPRITE_SIZE) * (data->i_player.bpp / 8);
			img_player.f_y = (img_player.j + (data->player.f / 4) * SPRITE_SIZE) * data->i_player.ll;
			img_player.pixel_color = *(int *)(data->i_player.addr + img_player.f_x + img_player.f_y);
			if (img_player.pixel_color == 0xFF000000)
				continue ;
            if (data->player.time < 0)
                img_player.pixel_color = color();
			img_player.buffer_index = (data->player.y + img_player.j) * data->buffer.ll + (data->player.x + img_player.i) * (data->buffer.bpp / 8);
			*(int *)(data->buffer.addr + img_player.buffer_index) = img_player.pixel_color;

		}
	}
}

///////////////////////////////////////////////////////////////////////////////]
// 		put ball throwned, avec transparence, white if negative
void	f_put_event_ball_to_buffer_v2(t_data2 *data)
{
    int		i;
	int		j;
    int     x;
    int     y;

	i = -1;
	while (++i < BALL_SIZE)
	{
		j = -1;
		while (++j < BALL_SIZE)
		{
            x = i * (data->i_throw.bpp / 8);
			y = (j + (data->throw.ball.f) * BALL_SIZE) * data->i_throw.ll;
			unsigned int pixel_color = *(int *)(data->i_throw.addr + x + y);
            if (data->throw.ball.time < 0)
                pixel_color = 0x00FFFFFF;
			if (pixel_color != 0xFF000000)
			{
				int buffer_index = (data->throw.ball.y + j) * data->buffer.ll + (data->throw.ball.x + i) * (data->buffer.bpp / 8);
				*(int *)(data->buffer.addr + buffer_index) = pixel_color;
			}
		}
	}
}
*/

// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
// 		ARCHIVES

/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
// void	f_put_player_to_buffer(t_data2 *data, t_coor xy, int frame, int rotation)
// {
// 	t_img	img;
// 	int		x;
// 	int		y;

// 	img.addr = mlx_get_data_addr(data->i_player.img, &img.bpp, &img.ll, &img.endian);
// 	frame = frame % 16;
// 	x = -1;
// 	while (++x < data->wid)
// 	{
// 		y = -1;
// 		while (++y < data->hei)
// 		{
//             int new_x;
//             if (rotation == 1)
//                 new_x = ((data->wid - 1 - x) + (frame % 4) * data->wid) * (img.bpp / 8);
//             else
//                 new_x = (x + (frame % 4) * data->wid) * (img.bpp / 8);
//             new_x = (x + (frame % 4) * data->wid) * (img.bpp / 8);
// 			int new_y = (y + (frame / 4) * data->hei) * img.ll;
// 			int pixel_index = new_x + new_y;
// 			int pixel_color = *(int *)(img.addr + pixel_index);
// 			if (pixel_color != 0xFF000000)
// 			{
// 				int buffer_index = (xy.y + y) * data->buffer.ll + (xy.x + x) * (data->buffer.bpp / 8);
// 				*(int *)(data->buffer.addr + buffer_index) = pixel_color;
// 			}
// 		}
// 	}
// }

// void	f_put_event_ball_to_buffer(t_data2 *data)
// {
//     int		i;
// 	int		j;
//     int     x;
//     int     y;

// 	i = -1;
// 	while (++i < BALL_SIZE)
// 	{
// 		j = -1;
// 		while (++j < BALL_SIZE)
// 		{
//             x = i * (data->i_throw.bpp / 8);
// 			y = (j + (data->throw.frame) * BALL_SIZE) * data->i_throw.ll;
// 			int pixel_color = *(int *)(data->i_throw.addr + x + y);
// 			if (pixel_color != 0xFF000000)
// 			{
// 				int buffer_index = (data->throw.y + j) * data->buffer.ll + (data->throw.x + i) * (data->buffer.bpp / 8);
// 				*(int *)(data->buffer.addr + buffer_index) = pixel_color;
// 			}
// 		}
// 	}
// }
