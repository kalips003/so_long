#include "so_long_bonus.h"

///////////////////////////////////////////////////////////////////////////////]
//      use v64 for empty circle
//      use v360 for full circle
void static helper_v64(t_data2 *data, t_circle *c, int x, int y)
{

    put_pixel_buffer(data, c->center_x + x, c->center_y + y, c->color());
    put_pixel_buffer(data, c->center_x - x, c->center_y + y, c->color());
    put_pixel_buffer(data, c->center_x + x, c->center_y - y, c->color());
    put_pixel_buffer(data, c->center_x - x, c->center_y - y, c->color());
    put_pixel_buffer(data, c->center_x + y, c->center_y + x, c->color());
    put_pixel_buffer(data, c->center_x - y, c->center_y + x, c->color());
    put_pixel_buffer(data, c->center_x + y, c->center_y - x, c->color());
    put_pixel_buffer(data, c->center_x - y, c->center_y - x, c->color());
}

void helper_v360(t_data2 *data, t_circle *circle, int x, int y)
{
    int i;

    i = -x -1;
    while (++i <= x)
    {
        put_pixel_buffer(data, circle->center_x + i, circle->center_y + y, circle->color());
        put_pixel_buffer(data, circle->center_x + i, circle->center_y - y, circle->color());
    }
    i = -y -1;
    while (++i <= y)
    {
        put_pixel_buffer(data, circle->center_x + i, circle->center_y + x, circle->color());
        put_pixel_buffer(data, circle->center_x + i, circle->center_y - x, circle->color());
    }
}

void draw_circle(t_data2 *data, t_circle circle)
{
    int x;
    int y;
    int determinant;

    x = 0;
    y = circle.radius;
    determinant = 1 - circle.radius;
    helper_v64(data, &circle, x, y);
    while (++x < y)
    {
        if (determinant < 0)
            determinant += 2 * x + 1;
        else
            determinant += 2 * (x - --y) + 1;
        helper_v64(data, &circle, x, y);
    }
}

// combinne fonctionality
void draw_circle_v2(t_data2 *data, t_circle circle, void helper(t_data2 *, t_circle *, int , int))
{
    int x;
    int y;
    int determinant;

    x = 0;
    y = circle.radius;
    determinant = 1 - circle.radius;
    helper(data, &circle, x, y);
    while (++x < y)
    {
        if (determinant < 0)
            determinant += 2 * x + 1;
        else
            determinant += 2 * (x - --y) + 1;
        helper(data, &circle, x, y);
    }
}
///////////////////////////////////////////////////////////////////////////////]

///////////////////////////////////////////////////////////////////////////////]
void draw_square_random_yellow(t_data2 *data, int x, int y, int len_side)
{
    int i;
    int j;

    i = -1;
    while (++i < len_side)
    {
        j = -1;
        while (++j < len_side)
            put_pixel_buffer(data, x + i, y + j, random_yellow(30, 255));
    }
}


// void draw_gradient_square(t_data2 *img, int x, int y, int len_side, int color)
// {
//     int i;
//     int j;

//     i = -1;
//     while (++i < len_side)
//     {
//         j = -1;
//         while (++j < len_side)
//             my_mlx_pixel_put(img, x + i, y + j, color + i + j);
//     }
// }


// void draw_circle_v2(t_data2 *data, int xc, int yc, int radius, int (*color)(void))
// {
//     t_circle    circle;
//     int x;
//     int y;
//     int determinant;

//     circle.center_x = xc;
//     circle.center_y = yc;
//     circle.radius = radius;
//     circle.color = color;
//     x = 0;
//     y = radius;
//     determinant = 1 - radius;
//     helper_v360(data, &circle, x, y);
//     while (++x < y)
//     {
//         if (determinant < 0)
//             determinant += 2 * x + 1;
//         else
//             determinant += 2 * (x - --y) + 1;
//         helper_v360(data, &circle, x, y);
//     }
// }
