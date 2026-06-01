/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_min_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:34:49 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 17:57:12 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	abs(int num)
{
	if (num == -2147483648)
		return (2147483647);
	if (num < 0)
		return (-num);
	return (num);
}

int	min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	min_all(int how_many, ...)
{
	va_list	args;
	int		num;
	int		smallest;

	va_start(args, how_many);
	smallest = INT_MAX;
	while (--how_many >= 0)
	{
		num = va_arg(args, int);
		if (num < smallest)
			smallest = num;
	}
	va_end(args);
	return (smallest);
}

int	max_all(int how_many, ...)
{
	va_list	args;
	int		num;
	int		biggest;

	va_start(args, how_many);
	biggest = INT_MIN;
	while (--how_many >= 0)
	{
		num = va_arg(args, int);
		if (num > biggest)
			biggest = num;
	}
	va_end(args);
	return (biggest);
}
