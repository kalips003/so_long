# include "so_long.h"


/////////////////////////////////////////////////////////////////////////////////////
// void delay(int milliseconds)
// {
//     struct timeval start;
//     struct timeval current;

//     gettimeofday(&start, NULL);
//     while (1)
//     {
//         gettimeofday(&current, NULL);
//         int elapsed = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000;
//         if (elapsed >= milliseconds)
//             break;
//     }
// }


/*
int rtrn_color(int tr, int r, int g, int b)
{
    return (tr << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data2 *data, int x, int y, int color)
{
	char	*dst;
    int offset;

    offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

void static draw_circle_help(t_data2 *img, t_circle *data, int x, int y)
{

    my_mlx_pixel_put(img, data->center_x + x, data->center_y + y, data->color);
    my_mlx_pixel_put(img, data->center_x - x, data->center_y + y, data->color);
    my_mlx_pixel_put(img, data->center_x + x, data->center_y - y, data->color);
    my_mlx_pixel_put(img, data->center_x - x, data->center_y - y, data->color);
    my_mlx_pixel_put(img, data->center_x + y, data->center_y + x, data->color);
    my_mlx_pixel_put(img, data->center_x - y, data->center_y + x, data->color);
    my_mlx_pixel_put(img, data->center_x + y, data->center_y - x, data->color);
    my_mlx_pixel_put(img, data->center_x - y, data->center_y - x, data->color);

}

void draw_circle(t_data2 *img, int xc, int yc, int radius, int color)
{
    t_circle    data;
    int x;
    int y;
    int determinant;

    data.center_x = xc;
    data.center_y = yc;
    data.radius = radius;
    data.color = color;
    x = 0;
    y = radius;
    determinant = 1 - radius;
    draw_circle_help(img, &data, x, y);
    while (++x < y)
    {
        if (determinant < 0)
            determinant += 2 * x + 1;
        else
            determinant += 2 * (x - --y) + 1;
        draw_circle_help(img, &data, x, y);
    }
}

void draw_square(t_data2 *img, int x, int y, int len_side, int color)
{
    int i;
    int j;

    i = -1;
    while (++i < len_side)
    {
        j = -1;
        while (++j < len_side)
            my_mlx_pixel_put(img, x + i, y + j, color);
    }
}

void draw_gradient_square(t_data2 *img, int x, int y, int len_side, int color)
{
    int i;
    int j;

    i = -1;
    while (++i < len_side)
    {
        j = -1;
        while (++j < len_side)
            my_mlx_pixel_put(img, x + i, y + j, color + i + j);
    }
}
*/
