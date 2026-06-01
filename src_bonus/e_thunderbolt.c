# include "so_long.h"

static int random_y(void)
{
	int color = (rand() % (255 - 30 + 1)) + 30;
	int yellow = color << 16 | color << 8;
	return (yellow);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
    int offset;

    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

    offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*(unsigned int*)dst = color;
}


/*
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

random color = (rand() % (255 - 10 + 1)) + 10;
random yellow = color << 16 | color << 8;

*/
// void f_draw_oneline(t_data2 * data, t_coor a, t_coor b)
// {


// }

void draw_square_2(t_data2 *data, int x, int y, int len_side)
{
    int i;
    int j;
	t_img img;

    i = -1;
	img.img = mlx_new_image(data->mlx, 64, 64);
    while (++i < len_side)
    {
        j = -1;
        while (++j < len_side)
            my_mlx_pixel_put(&img, i, j, random_y());
    }
	mlx_put_image_to_window(data->mlx, data->win, img.img, x, y);
}


// void	draw_sprite(t_data2 *game, t_img *img, int x, int y)
// {
// 	int				i;
// 	int				j;
// 	unsigned int	color;

// 	i = 0;
// 	while (i < img->width * game->scale)
// 	{
// 		j = -1;
// 		while (++j < img->height * game->scale)
// 		{
// 			if (j + y < 0 || j + y >= (game->scale * game->max_y * 32)
// 				|| i + x < 0 || i + x >= (game->scale * game->max_x * 32))
// 				continue ;
// 			color = ((int *)img->data)[(int)
// 				(j / game->scale) * img->width + (int)(i / game->scale)];
// 			if (color == 0xFF000000)
// 				continue ;
// 			((int *)game->screen->data)[(y + j)
// 				* game->screen->width + (x + i)] = color;
// 		}
// 		i++;
// 	}
// }
