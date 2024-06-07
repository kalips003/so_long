# include "so_long.h"

///////////////////////////////////////////////////////////////////////////////]
// put pixel to buffer, secure for out_of_bounds
void	put_pixel_buffer(t_data2 *data, int x, int y, int color)
{
	char	*dst;
    int     offset;

    if (x < 0 || y < 0 || x >= data->buffer.sz_x || y >= data->buffer.sz_y)
        return ;
    offset = (y * data->buffer.ll + x * (data->buffer.bpp / 8));
	dst = data->buffer.addr + offset;
	*(unsigned int*)dst = color;
}

// random color = (rand() % (max - min + 1)) + min;
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
int random_white(void)
{
	int color;

    color = (rand() % (255 - 240 + 1)) + 240;
	return (color << 16 | color << 8 | color);
}

int random_yellow(int min_rg, int max_rg)
{
	int color;

    color = (rand() % (max_rg - min_rg + 1)) + min_rg;
	return (color << 16 | color << 8);
}

int random_yellow_v2(void)
{
	int color;

    color = (rand() % (255 - 30 + 1)) + 30;
	return (color << 16 | color << 8);
}

int random_blue(int min_b, int max_b, int min_rg, int max_rg)
{
	int color_b;
	int color_rg;

    color_b = (rand() % (max_b - min_b + 1)) + min_b;
    color_rg = (rand() % (max_rg - min_rg + 1)) + min_rg;
	return (color_rg << 16 | color_rg << 8 | color_b);
}

int random_green_bot(int min_g, int max_g, int min_rb, int max_rb)
{
	int color_r;
	int color_g;
	int color_b;

    color_r = (rand() % (max_rb - min_rb + 1)) + min_rb;
    color_b = (rand() % (max_rb - min_rb + 1)) + min_rb;
    color_g = (rand() % (max_g - min_g + 1)) + min_g;
	return (color_r << 16 | color_g << 8 | color_b);
}

int ft_black(void)
{
    return (0x00000000);
}

// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>

///////////////////////////////////////////////////////////////////////////////]
//      Bresenham's Line Algorithm
static void helper_v555(int *err, int a[2], int dxy[2], int sxy[2])
{
    int e2;

    e2 = 2 * (*err);
    if (e2 > -dxy[1])
    {
        *err -= dxy[1];
        a[0] += sxy[0];
    }
    if (e2 < dxy[0])
    {
        *err += dxy[0];
        a[1] += sxy[1];
    }
}

//      Single color
void draw_line_v2(t_data2 *data, int a[2], int b[2], int color)
{
    int dxy[2];
    int sxy[2];
    int err;

    dxy[0] = abs(b[0] - a[0]);
    dxy[1] = abs(b[1] - a[1]);
    sxy[0] = 1 - 2 * !(a[0] < b[0]);
    sxy[1] = 1 - 2 * !(a[1] < b[1]);
    err = dxy[0] - dxy[1];
    while (1) {
        put_pixel_buffer(data, a[0], a[1], color);
        if (a[0] == b[0] && a[1] == b[1])
            break;
        helper_v555(&err, a, dxy, sxy);
    }
}

//      Color passed as function
void draw_line_v3(t_data2 *data, int a[2], int b[2], int (*color)(void))
{
    int dxy[2];
    int sxy[2];
    int err;

    dxy[0] = abs(b[0] - a[0]);
    dxy[1] = abs(b[1] - a[1]);
    sxy[0] = 1 - 2 * !(a[0] < b[0]);
    sxy[1] = 1 - 2 * !(a[1] < b[1]);
    err = dxy[0] - dxy[1];
    while (1)
    {
        put_pixel_buffer(data, a[0] + HIT_BOX, a[1] + HIT_BOX, color());
        if (a[0] == b[0] && a[1] == b[1])
            break;
        helper_v555(&err, a, dxy, sxy);
    }
}

# define EPAISSEUR 3

// ligne + epaisse
void draw_line_v4(t_data2 *data, int a[2], int b[2], int (*color)(void))
{
    int i_j[2];
    int a_shifted[2];
    int b_shifted[2];

    i_j[0] = -EPAISSEUR;
    while (++i_j[0] < EPAISSEUR)
    {
        i_j[1] = -EPAISSEUR;
        while (++i_j[1] < EPAISSEUR)
        {
            a_shifted[0] = a[0] + i_j[0];
            a_shifted[1] = a[1] + i_j[1];
            b_shifted[0] = b[0] + i_j[0];
            b_shifted[1] = b[1] + i_j[1];
            draw_line_v3(data, a_shifted, b_shifted, color);
        }
    }
}
