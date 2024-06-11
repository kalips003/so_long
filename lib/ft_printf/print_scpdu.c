/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tableau.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <agallon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:06:53 by agallon           #+#    #+#             */
/*   Updated: 2023/12/08 14:29:23 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//////////////////////////////////////////////////////////// (%s)
int	ft_string(va_list args, t_flags *f)
{
	char	*str;
	int		size;
	int		i;
	int		space;

	str = va_arg(args, char *);
	size = ft_strlen666(str);
	if (!str && !(f->point && f->preci < 6))
		size = 6;
	else if (str && (f->point && f->preci < size))
		size = f->preci;
	if (!f->minus)
		space = f_spacing(f, size);
	i = 0;
	if (!str && size >= 6)
		write(f->fd, "(null)", size);
	else if (str)
		while (str[i] && i < size)
			write(f->fd, &str[i++], 1);
	if (f->minus)
		space = f_spacing(f, size);
	return (size + space);
}

//////////////////////////////////////////////////////////// (%c)
//	unsigned?
int	ft_char(va_list args, t_flags *f)
{
	char	c;
	int		size;
	int		i;

	c = (char)va_arg(args, int);
	if (!f->minus)
		size = f_spacing(f, f->preci);
	i = -1;
	while (++i < f->preci)
		write(f->fd, &c, 1);
	if (f->minus)
		size = f_spacing(f, f->preci);
	return (f->preci + size);
}

//////////////////////////////////////////////////////////// (%p)
int	ft_pointer(va_list args, t_flags *f)
{
	unsigned long	p;
	int				size;
	int				num_size;

	p = (unsigned long)va_arg(args, void *);
	num_size = size_num_base_un(p, 16);
	if (!p)
		num_size = 5;
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num_un(p, f, num_size));
	if (p)
	{
		size += f_format_num_un(f, p, num_size);
		size += ft_putnbr_base_un(f->fd, p, "0123456789abcdef");
	}
	else
		size += write(f->fd, "(nil)", 5);
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num_un(p, f, num_size));
	return (size);
}

//////////////////////////////////////////////////////////// (%d)(%i)
int	ft_int(va_list args, t_flags *f)
{
	int	num;
	int	size;
	int	num_size;

	num = va_arg(args, int);
	if (!num && f->point && f->preci == 0)
		return (f_spacing(f, 0));
	num_size = size_num_base(num, 10);
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num(num, f, num_size));
	size += f_format_num(f, num, num_size);
	size += ft_putnbr_base(f->fd, num, "0123456789");
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num(num, f, num_size));
	return (size);
}

//////////////////////////////////////////////////////////// (%u)
int	ft_unsigned(va_list args, t_flags *f)
{
	long long	num;
	int			size;
	int			num_size;

	num = va_arg(args, unsigned);
	if (!num && f->point && f->preci == 0)
		return (f_spacing(f, 0));
	num_size = size_num_base(num, 10);
	size = 0;
	if (!f->minus)
		size += f_spacing(f, num_size + size_format_num(num, f, num_size));
	size += f_format_num(f, num, num_size);
	size += ft_putnbr_base(f->fd, num, "0123456789");
	if (f->minus)
		size += f_spacing(f, num_size + size_format_num(num, f, num_size));
	return (size);
}
