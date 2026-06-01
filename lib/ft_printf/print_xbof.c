/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tableau_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:35:52 by agallon           #+#    #+#             */
/*   Updated: 2023/12/08 16:35:54 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//////////////////////////////////////////////////////////// (%x)(%X)
int	ft_hexa(va_list args, t_flags *f)
{
	long long	hex;
	int			size;
	int			num_size;

	hex = va_arg(args, unsigned);
	if (!hex && f->point && f->preci == 0)
		return (f_spacing(f, 0));
	num_size = size_num_base(hex, 16);
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num(hex, f, num_size));
	size += f_format_num(f, hex, num_size);
	if (f->flag == 'x')
		size += ft_putnbr_base(f->fd, hex, "0123456789abcdef");
	else
		size += ft_putnbr_base(f->fd, hex, "0123456789ABCDEF");
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num(hex, f, num_size));
	return (size);
}

//////////////////////////////////////////////////////////// (%%)
int	ft_percent(va_list args, t_flags *f)
{
	if (args || f)
		return (write(f->fd, "%", 1));
	return (write(f->fd, "%", 1));
}

//////////////////////////////////////////////////////////// (%b)
int	ft_binary(va_list args, t_flags *f)
{
	long long	bi;
	int			size;
	int			num_size;

	bi = va_arg(args, unsigned);
	if (!bi && f->point && f->preci == 0)
		return (f_spacing(f, 0));
	num_size = size_num_base(bi, 2);
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num(bi, f, num_size));
	size += f_format_num(f, bi, num_size);
	size += ft_putnbr_base(f->fd, bi, "01");
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num(bi, f, num_size));
	return (size);
}

//////////////////////////////////////////////////////////// (%o)
int	ft_octal(va_list args, t_flags *f)
{
	long long	oct;
	int			size;
	int			num_size;

	oct = va_arg(args, unsigned);
	if (!oct && f->point && f->preci == 0)
		return (f_spacing(f, 0));
	num_size = size_num_base(oct, 8);
	if (f->hash && ((f->point && num_size < f->preci) || (f->zero
				&& num_size < f->width)))
		f->hash = 0;
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num(oct, f, num_size));
	size += f_format_num(f, oct, num_size);
	size += ft_putnbr_base(f->fd, oct, "01234567");
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num(oct, f, num_size));
	return (size);
}

//////////////////////////////////////////////////////////// (%f)
int	ft_float(va_list args, t_flags *f)
{
	double	fl;
	int		size;
	int		num_size;

	fl = va_arg(args, double);
	num_size = size_float(fl, f);
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num(fl, f, num_size));
	size += f_format_num(f, fl, num_size);
	size += ft_put_float(fl, f);
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num(fl, f, num_size));
	return (size);
}
