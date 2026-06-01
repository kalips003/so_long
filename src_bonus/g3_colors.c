/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g3_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/18 00:43:21 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

unsigned int	ft_yellow(void);
unsigned int	ft_green(void);
unsigned int	ft_red(void);
unsigned int	ft_blue(void);
unsigned int	ft_black(void);
unsigned int	ft_white(void);
unsigned int	ft_r_yellow(void);
unsigned int	ft_r_green(void);
unsigned int	ft_r_red(void);
unsigned int	ft_r_blue(void);
unsigned int	ft_r_white(void);

///////////////////////////////////////////////////////////////////////////////]
// random color = (rand() % (max - min + 1)) + min;
unsigned int	ft_yellow(void)
{
	return (0xF8D050);
}

unsigned int	ft_green(void)
{
	return (0x88E020);
}

unsigned int	ft_red(void)
{
	return (0xE02828);
}

unsigned int	ft_blue(void)
{
	return (0x58B8F0);
}

unsigned int	ft_black(void)
{
	return (0x00000000);
}

unsigned int	ft_white(void)
{
	return (0x00FFFFFF);
}
///////////////////////////////////////////////////////////////////////////////]
unsigned int	ft_r_yellow(void)
{
	int	color;

	color = (rand() % (255 - 30 + 1)) + 30;
	return (color << 16 | color << 8);
}

unsigned int	ft_r_green(void)
{
	int	color_r;
	int	color_g;
	int	color_b;

	color_r = (rand() % (50 + 1));
	color_b = (rand() % (50 + 1));
	color_g = (rand() % (255 - 30 + 1)) + 30;
	return (color_r << 16 | color_g << 8 | color_b);
}

unsigned int	ft_r_red(void)
{
	int	color_r;
	int	color_gb;

	color_r = (rand() % (255 - 128 + 1)) + 128;
	color_gb = (rand() % (100 + 1));
	return (color_r << 16 | color_gb << 8 | color_gb / 2);
}

unsigned int	ft_r_blue(void)
{
	int	color_b;
	int	color_rg;

	color_b = (rand() % (255 - 70 + 1)) + 70;
	color_rg = (rand() % (70 + 1));
	return (color_rg << 16 | color_rg << 8 | color_b);
}

unsigned int	ft_r_white(void)
{
	int	color_r;
	int	color_g;
	int	color_b;

	color_r = (rand() % (255 - 240 + 1)) + 240;
	color_b = (rand() % (255 - 240 + 1)) + 240;
	color_g = (rand() % (255 - 240 + 1)) + 240;
	return (color_r << 16 | color_g << 8 | color_b);
}

/*
unsigned int random_green_bot(int min_g, int max_g, int min_rb, int max_rb)
{
	int	color_r;
	int	color_g;
	int	color_b;

	color_r = (rand() % (max_rb - min_rb + 1)) + min_rb;
	color_b = (rand() % (max_rb - min_rb + 1)) + min_rb;
	color_g = (rand() % (max_g - min_g + 1)) + min_g;
	return (color_r << 16 | color_g << 8 | color_b);
}*/