# include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
//      clean the bottom
void put_black_background(t_data2 *data)
{
    int i;
    int j;
    int buffer_index;

    j = data->map_y * SPRITE_SIZE - 1;
    while (++j < data->buffer.sz_y)
    {
        i = -1;
        while (++i < data->buffer.sz_x)
        {
			buffer_index = j * data->buffer.line_length + i * (data->buffer.bits_per_pixel / 8);
			*(int *)(data->buffer.addr + buffer_index) = 0x00FFFFFF;
        }
    }
}

//      put retrieved balls and caught pika on bottom
void put_balls_foreground(t_data2 *data)
{
    int i;
    int xy[2];

    xy[1] = data->map_y * SPRITE_SIZE + BALL_START_Y;
    i = -1;
    while (++i < data->num_holding)
    {
        xy[0] = data->map_x * SPRITE_SIZE - BALL_START_X * (i + 1);
        f_put_sprite_to_buffer(data, xy, data->i_big_ball[0]);
    }
    i = -1;
    while (++i < data->num_pika_caught)
    {
        xy[0] = PIKA_START_X + BALL_START_X * i;
        f_put_sprite_to_buffer(data, xy, data->i_big_ball[1]);
    }
}
///////////////////////////////////////////////////////////////////////////////]
// 		put sprite at coordonate xy, avec transparence, not white if negative
// 			used for bottom inventory
void	f_put_sprite_to_buffer(t_data2 *data, int xy[2], t_img img)
{
	int		i;
	int		j;
    int pixel_index;
    int pixel_color;
    int buffer_index;

    if (xy[0] < 0 || xy[1] < 0)
        return ;
    i = -1;
	while (++i < img.sz_x)
	{
		j = -1;
		while (++j < img.sz_y)
		{
			pixel_index = (j * img.line_length + i * (img.bits_per_pixel / 8));
			pixel_color = *(int *)(img.addr + pixel_index);
			if (pixel_color == 0xFF000000)
				continue ;
			buffer_index = (xy[1] + j) * data->buffer.line_length + (xy[0] + i) * (data->buffer.bits_per_pixel / 8);
			*(int *)(data->buffer.addr + buffer_index) = pixel_color;
		}
	}
}

// 		put sprite at coordonate xy, avec transparence, white if negative
// 		used for pika, if x or y is negative, skipped
// 		color is passed as function argument
void	f_put_sprite_to_buffer_v2(t_data2 *data, int xy[3], t_img img, int (* color)(void))
{
	int		i;
	int		j;
    int pixel_index;
    int pixel_color;
    int buffer_index;

    if (xy[0] < 0 || xy[1] < 0)
        return ;
    i = -1;
	while (++i < img.sz_x)
	{
		j = -1;
		while (++j < img.sz_y)
		{
			pixel_index = (j * img.line_length + i * (img.bits_per_pixel / 8));
			pixel_color = *(int *)(img.addr + pixel_index);
            if (xy[3] < 0)
                pixel_color = color();
			if (pixel_color == 0xFF000000)
				continue ;
			buffer_index = (xy[1] + j) * data->buffer.line_length + (xy[0] + i) * (data->buffer.bits_per_pixel / 8);
			*(int *)(data->buffer.addr + buffer_index) = pixel_color;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////]
// 		put sprite player, avec transparence, white if negative
// 			white if negative
void	f_put_player_to_buffer_v2(t_data2 *data, int rotation, int (* color)(void))
{
	int		i;
	int		j;
    int     x;
    int     y;

	i = -1;
	while (++i < SPRITE_SIZE)
	{
		j = -1;
		while (++j < SPRITE_SIZE)
		{
            if (rotation == 1)
                x = ((SPRITE_SIZE - 1 - i) + (data->player[2] % 4) * SPRITE_SIZE) * (data->i_player.bits_per_pixel / 8);
            else
                x = (i + (data->player[2] % 4) * SPRITE_SIZE) * (data->i_player.bits_per_pixel / 8);
			y = (j + (data->player[2] / 4) * SPRITE_SIZE) * data->i_player.line_length;
			int pixel_color = *(int *)(data->i_player.addr + x + y);
            if (data->player[3] < 0)
                pixel_color = color();
			if (pixel_color != 0xFF000000)
			{
				int buffer_index = (data->player[1] + j) * data->buffer.line_length + (data->player[0] + i) * (data->buffer.bits_per_pixel / 8);
				*(int *)(data->buffer.addr + buffer_index) = pixel_color;
			}
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
            x = i * (data->i_ball_throw.bits_per_pixel / 8);
			y = (j + (data->ball_throw.frame) * BALL_SIZE) * data->i_ball_throw.line_length;
			int pixel_color = *(int *)(data->i_ball_throw.addr + x + y);
            if (data->ball_throw.time < 0)
                pixel_color = 0x00FFFFFF;
			if (pixel_color != 0xFF000000)
			{
				int buffer_index = (data->ball_throw.y + j) * data->buffer.line_length + (data->ball_throw.x + i) * (data->buffer.bits_per_pixel / 8);
				*(int *)(data->buffer.addr + buffer_index) = pixel_color;
			}
		}
	}
}
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
// 		ARCHIVES

/* * * * * * * * * * * * * * * * * * * * * * * * * * * */
// void	f_put_player_to_buffer(t_data2 *data, t_coor xy, int frame, int rotation)
// {
// 	t_img	img;
// 	int		x;
// 	int		y;

// 	img.addr = mlx_get_data_addr(data->i_player.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	frame = frame % 16;
// 	x = -1;
// 	while (++x < data->wid)
// 	{
// 		y = -1;
// 		while (++y < data->hei)
// 		{
//             int new_x;
//             if (rotation == 1)
//                 new_x = ((data->wid - 1 - x) + (frame % 4) * data->wid) * (img.bits_per_pixel / 8);
//             else
//                 new_x = (x + (frame % 4) * data->wid) * (img.bits_per_pixel / 8);
//             new_x = (x + (frame % 4) * data->wid) * (img.bits_per_pixel / 8);
// 			int new_y = (y + (frame / 4) * data->hei) * img.line_length;
// 			int pixel_index = new_x + new_y;
// 			int pixel_color = *(int *)(img.addr + pixel_index);
// 			if (pixel_color != 0xFF000000)
// 			{
// 				int buffer_index = (xy.y + y) * data->buffer.line_length + (xy.x + x) * (data->buffer.bits_per_pixel / 8);
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
//             x = i * (data->i_ball_throw.bits_per_pixel / 8);
// 			y = (j + (data->ball_throw.frame) * BALL_SIZE) * data->i_ball_throw.line_length;
// 			int pixel_color = *(int *)(data->i_ball_throw.addr + x + y);
// 			if (pixel_color != 0xFF000000)
// 			{
// 				int buffer_index = (data->ball_throw.y + j) * data->buffer.line_length + (data->ball_throw.x + i) * (data->buffer.bits_per_pixel / 8);
// 				*(int *)(data->buffer.addr + buffer_index) = pixel_color;
// 			}
// 		}
// 	}
// }