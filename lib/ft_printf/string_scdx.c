/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_scdx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:18:37 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 19:18:37 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//////////////////////////////////////////////////////////// (%s)
//	flag [width][.] !width must be = 1;
//	%<how many time>.<truncate string>s
char	*pt_string(va_list args, t_flags *f)
{
	char	*str_arg;
	int		i;

	str_arg = va_arg(args, char *);
	f->rtrn = NULL;
	i = -1;
	while (++i < f->width)
		f->rtrn = join(f->rtrn, str_arg, 0b10, f->preci);
	return (f->rtrn);
}

//////////////////////////////////////////////////////////// (%c)
//	flag [.]
char	*pt_char(va_list args, t_flags *f)
{
	char	c;
	int		i;

	c = (char)va_arg(args, int);
	f->rtrn = (char *)malloc(f->preci + 1);
	if (!f->rtrn)
		return (NULL);
	i = -1;
	while (++i < f->preci)
		f->rtrn[i] = c;
	f->rtrn[i] = '\0';
	return (f->rtrn);
}

//////////////////////////////////////////////////////////// (%d)
//
char	*pt_num(va_list args, t_flags *f)
{
	int		num;
	int		i;

	num = va_arg(args, int);
	if (num == -2147483648)
		return (str("-2147483648"));
	f->size += size_num_base(num, 10) + (num < 0);
	f->rtrn = (char *)malloc(f->size + 1);
	if (!f->rtrn)
		return (NULL);
	f->rtrn[f->size] = '\0';
	if (num < 0)
	{
		f->rtrn[0] = '-';
		num = -num;
	}
	i = 0;
	while (num >= 10)
	{
		f->rtrn[f->size - i++ - 1] = (num % 10) + '0';
		num /= 10;
	}
	f->rtrn[f->size - i - 1] = (num % 10) + '0';
	return (f->rtrn);
}

//////////////////////////////////////////////////////////// (%x)
//	f->point > precise base as argument
char	*pt_hex(va_list args, t_flags *f)
{
	long long	num;
	int			i;
	char		*base;

	base = "0123456789abcdef";
	if (f->point)
		base = (char *)va_arg(args, char *);
	f->tmp_a = ft_strlen666(base);
	num = (long long)va_arg(args, long long);
	if (num < 0 && ++f->size && ++f->minus)
		num = -num;
	f->size += size_num_base(num, f->tmp_a);
	f->rtrn = (char *)malloc(f->size + 1);
	f->rtrn[f->size] = '\0';
	i = 0;
	if (f->minus)
		f->rtrn[0] = '-';
	while (num >= f->tmp_a)
	{
		f->rtrn[f->size - i++ - 1] = base[num % f->tmp_a];
		num /= f->tmp_a;
	}
	f->rtrn[f->size - i - 1] = base[num % f->tmp_a];
	return (f->rtrn);
}
