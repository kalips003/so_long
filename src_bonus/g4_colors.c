/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g4_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:31 by marvin            #+#    #+#             */
/*   Updated: 2024/06/19 16:37:04 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

unsigned int	ft_black(void);
unsigned int	ft_white(void);
unsigned int	ft_r_white(void);

///////////////////////////////////////////////////////////////////////////////]
// random color = (rand() % (max - min + 1)) + min;
unsigned int	ft_black(void)
{
	return (0x00000000);
}

unsigned int	ft_white(void)
{
	return (0x00FFFFFF);
}

///////////////////////////////////////////////////////////////////////////////]
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
