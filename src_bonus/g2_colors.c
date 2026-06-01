#include "so_long_bonus.h"

void	put_pixel_buffer(t_data2 *data, int x, int y, unsigned color);
unsigned int random_white(void);
unsigned int random_yellow(int min_rg, int max_rg);
unsigned int random_yellow_v2(void);
unsigned int random_blue(int min_b, int max_b, int min_rg, int max_rg);
unsigned int random_green_bot(int min_g, int max_g, int min_rb, int max_rb);
unsigned int ft_black(void);


///////////////////////////////////////////////////////////////////////////////]
// 			put pixel to buffer, secure for out_of_bounds
void	put_pixel_buffer(t_data2 *data, int x, int y, unsigned color)
{
	char	*dst;
	int		offset;

	if (x < 0 || y < 0 || x >= data->buffer.sz_x || y >= data->buffer.sz_y)
		return ;
	offset = (y * data->buffer.ll + x * (data->buffer.bpp / 8));
	dst = data->buffer.addr + offset;
	*(unsigned int*)dst = color;
}

// random color = (rand() % (max - min + 1)) + min;
// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- </?>
unsigned int random_white(void)
{
	int	color;

	color = (rand() % (255 - 240 + 1)) + 240;
	return (color << 16 | color << 8 | color);
}

unsigned int random_yellow(int min_rg, int max_rg)
{
	int	color;

	color = (rand() % (max_rg - min_rg + 1)) + min_rg;
	return (color << 16 | color << 8);
}

unsigned int random_yellow_v2(void)
{
	int	color;

	color = (rand() % (255 - 30 + 1)) + 30;
	return (color << 16 | color << 8);
}

unsigned int random_blue(int min_b, int max_b, int min_rg, int max_rg)
{
	int	color_b;
	int	color_rg;

	color_b = (rand() % (max_b - min_b + 1)) + min_b;
	color_rg = (rand() % (max_rg - min_rg + 1)) + min_rg;
	return (color_rg << 16 | color_rg << 8 | color_b);
}

unsigned int random_green_bot(int min_g, int max_g, int min_rb, int max_rb)
{
	int	color_r;
	int	color_g;
	int	color_b;

	color_r = (rand() % (max_rb - min_rb + 1)) + min_rb;
	color_b = (rand() % (max_rb - min_rb + 1)) + min_rb;
	color_g = (rand() % (max_g - min_g + 1)) + min_g;
	return (color_r << 16 | color_g << 8 | color_b);
}

unsigned int ft_black(void)
{
    return (0x00000000);
}

// <!> - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </?>
