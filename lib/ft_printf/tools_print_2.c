/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:07:00 by agallon           #+#    #+#             */
/*   Updated: 2023/12/06 16:07:02 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_float(t_flags *f)
{
	if (f->flag == 'f' || f->flag == 'e' || f->flag == 'E')
		return (1);
	return (0);
}

////////////////////////////////////////////////////////////
//	#	DOES THE PRINTING OF ARGS FORMAT, RETURN SIZE OF FORMAT
static int	f_prefix_hash(t_flags *f)
{
	if (is_float(f))
		return (0);
	if ((f->hash && f->flag == 'x') || f->flag == 'p')
		return (write(f->fd, "0x", 2));
	if (f->hash && f->flag == 'X')
		return (write(f->fd, "0X", 2));
	if (f->hash && f->flag == 'b')
		return (write(f->fd, "0b", 2));
	if (f->hash && f->flag == 'o')
		return (write(f->fd, "0", 1));
	return (0);
}

int	f_format_num(t_flags *f, long long num, int size_num)
{
	int	prefix;
	int	i;

	prefix = 0;
	if (num < 0)
		prefix += write(f->fd, "-", 1);
	if (num >= 0 && f->space)
		prefix += write(f->fd, " ", 1);
	if (num >= 0 && f->plus)
		prefix += write(f->fd, "+", 1);
	if (num)
		prefix += f_prefix_hash(f);
	i = 0;
	if (f->point && !(is_float(f)))
		while (i < f->preci - size_num)
			i += write(f->fd, "0", 1);
	else if (f->zero)
		while (i < f->width - size_num - prefix)
			i += write(f->fd, "0", 1);
	return (i + prefix);
}

////////////////////////////////////////////////////////////
//	#	RETURN THE SIZE OF FLAG FORMAT, NO WHITE SPACE PADDING
int	size_format_num(long long num, t_flags *f, int num_size)
{
	int	size;

	size = 0;
	if (num < 0)
		size++;
	else if ((f->plus || f->space) && !(f->flag == 'p' && num == 0))
		size++;
	if (f->flag == 'p' && num != 0)
		size += 2;
	if (f->hash && num != 0 && (f->flag == 'x' || \
					f->flag == 'X' || f->flag == 'b'))
		size += 2;
	if (f->hash && num != 0 && f->flag == 'o')
		size++;
	if (f->preci > num_size && !(is_float(f)) && !(f->flag == 'p' && num == 0))
		size += f->preci - num_size;
	else if (f->zero && f->width > (size + num_size))
		size += f->width - size - num_size;
	return (size);
}

////////////////////////////////////////////////////////////
//	#	DO THE WHITE SPACING BEFORE OR AFTER, RETURN THE PADDING DONE
int	f_spacing(t_flags *f, int size)
{
	int	to_print;
	int	i;

	to_print = f->width - size;
	i = 0;
	if (f->zero)
		return (0);
	if (!f->zero)
		while (i < to_print)
			i += write(f->fd, " ", 1);
	return (i);
}
