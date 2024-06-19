/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g3_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/19 16:36:58 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

unsigned int	ft_r_yellow(void);
unsigned int	ft_r_green(void);
unsigned int	ft_r_red(void);
unsigned int	ft_r_blue(void);

///////////////////////////////////////////////////////////////////////////////]
// random color = (rand() % (max - min + 1)) + min;
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

	color_r = (rand() % (100 + 1));
	color_b = (rand() % (100 + 1));
	color_g = (rand() % (255 - 100 + 1)) + 100;
	return (color_r << 16 | color_g << 8 | color_b);
}

unsigned int	ft_r_red(void)
{
	int	color_r;
	int	color_gb;

	color_r = (rand() % (255 - 200 + 1)) + 200;
	color_gb = (rand() % (150 + 1));
	return (color_r << 16 | color_gb << 8 | color_gb / 2);
}

unsigned int	ft_r_blue(void)
{
	int	color_b;
	int	color_rg;

	color_b = (rand() % (255 - 200 + 1)) + 200;
	color_rg = (rand() % (150 + 1));
	return (color_rg << 16 | color_rg << 8 | color_b);
}
