/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:07:00 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 18:35:40 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

////////////////////////////////////////////////////////////
//	#	THE RETURN OF THE KING
int	ft_strlen666(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

////////////////////////////////////////////////////////////
//	#	RETURN THE LENGTH OF I TO JUMP OVER, UPDATE THE CORRESPONDING SIZE
int	atoi_print(const char *str, int *preci_width, t_flags *f, va_list args)
{
	int		i;
	long	rtrn;

	i = 0;
	rtrn = 0;
	if (str[i] == '*')
	{
		*preci_width = va_arg(args, int);
		if (*preci_width < 0)
			f->error = -2;
		return (1);
	}
	while (str[i] >= '0' && str[i] <= '9')
		rtrn = rtrn * 10 + (str[i++] - '0');
	if (rtrn > 2147483647)
		f->error = -2;
	*preci_width = (int)rtrn;
	return (i);
}

////////////////////////////////////////////////////////////
//	#	RETURN THE SIZE OF A NUMBER WITHOUT -
int	size_num_base(long long num, int base)
{
	int	size;

	size = 0;
	if (num < 0)
		num = -num;
	while (num >= base)
	{
		num /= base;
		size++;
	}
	return (size + 1);
}

////////////////////////////////////////////////////////////
//	#	SIZE FLOAT + f
int	size_float(double nbr, t_flags *f)
{
	int	size;

	size = size_num_base((long long)nbr, 10);
	if (!(f->point && f->preci == 0) || f->hash)
		size++;
	if (!f->point)
		f->preci = 6;
	size += f->preci;
	return (size);
}

////////////////////////////////////////////////////////////
//	#	SIZE EXP
int	size_exp(t_flags *f)
{
	int	size;

	size = 0;
	if (!(f->point && f->preci == 0) || f->hash)
		size++;
	if (!f->point)
		f->preci = 6;
	size += f->preci;
	return (size + 5);
}
