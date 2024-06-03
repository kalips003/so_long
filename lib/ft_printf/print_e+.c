/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_e+.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:35:59 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 18:58:56 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//////////////////////////////////////////////////////////// (%e)(%E)
int	ft_scientific(va_list args, t_flags *f)
{
	double	exp;
	int		size;
	int		num_size;

	exp = va_arg(args, double);
	num_size = size_exp(f);
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num(exp, f, num_size));
	size += f_format_num(f, exp, num_size);
	size += ft_put_science(exp, f);
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num(exp, f, num_size));
	return (size);
}

//////////////////////////////////////////////////////////// (%S)
// [ % S ] > spacing
// [ %*S ] > print memory
// [ %.*S ] > color sizeof (bit)
// [ %#S ] > hexadecimal
// [ %-#S ] > no 2 precision for hexa
// [ %+S ] > colors +128
int	ft_string_hexa(va_list args, t_flags *f)
{
	char	*str;
	int		i;

	i = -1;
	str = va_arg(args, char *);
	if (!str)
		return (put(BLINK REVERSE "NULL" RESET) - 12);
	while (str[++i] || i < f->width)
	{
		if (!f->preci || (f->preci && i % f->preci == 0))
			put(RESET "\033[38;5;0;48;5;%um", ((unsigned)str[i] + 128
					* (f->plus)) % 256);
		if (f->hash)
			f->size += put("%.*x", 2 - f->minus, (unsigned char)str[i]);
		else
			f->size += put("%d", str[i]);
		f->size += put("%.*s", ((str[i] == ' ' || str[i] == '\n') && !f->hash)
				|| f->space, " ");
	}
	put(RESET);
	return (f->size);
}

//////////////////////////////////////////////////////////// (%t)
int	ft_tab(va_list args, t_flags *flags)
{
	char	**tab;
	int		i;

	i = -1;
	tab = (char **)va_arg(args, char *);
	if (!tab)
		return (put(BLINK REVERSE "NULL" RESET) - 12);
	while (tab[++i])
		flags->size += put("%s\n", tab[i]);
	return (flags->size);
}
