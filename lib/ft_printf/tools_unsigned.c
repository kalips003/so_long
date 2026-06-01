/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:50:30 by agallon           #+#    #+#             */
/*   Updated: 2024/06/19 18:01:21 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

////////////////////////////////////////////////////////////
//	#
int	size_format_num_un(unsigned long num, t_flags *f, int num_size)
{
	int	size;

	size = 0;
	if ((f->plus || f->space) && num)
		size++;
	if (f->flag == 'p' && num)
		size += 2;
	if (f->preci > num_size && num)
		size += f->preci - num_size;
	else if (f->zero && f->width > (size + num_size))
		size += f->width - size - num_size;
	return (size);
}

////////////////////////////////////////////////////////////
//	#	RETURN THE SIZE OF A NUMBER WITHOUT -
int	size_num_base_un(unsigned long num, int base)
{
	int	size;

	size = 0;
	while (num >= (unsigned long)base)
	{
		num /= base;
		size++;
	}
	return (size + 1);
}

////////////////////////////////////////////////////////////
//	#	DOES THE PRINTING OF ARGS FORMAT, RETURN SIZE OF FORMAT

int	f_format_num_un(t_flags *f, unsigned long num, int size_num)
{
	int	prefix;
	int	i;

	prefix = 0;
	if (num == 0 && f->space)
		prefix += write(f->fd, " ", 1);
	if (num == 0 && f->plus)
		prefix += write(f->fd, "+", 1);
	if (num)
		prefix += write(f->fd, "0x", 2);
	i = 0;
	if (f->point)
		while (i < f->preci - size_num)
			i += write(f->fd, "0", 1);
	else if (f->zero)
		while (i < f->width - size_num - prefix)
			i += write(f->fd, "0", 1);
	return (i + prefix);
}

////////////////////////////////////////////////////////////
//	#	WRITE NUM IN CORRESPONDING BASE, NO SIGN
int	ft_putnbr_base_un(int fd, unsigned long nbr, char *base)
{
	int			size;
	int			rtrn;

	rtrn = 0;
	size = ft_strlen666(base);
	if (nbr >= (unsigned long)size)
		rtrn += ft_putnbr_base(fd, nbr / size, base);
	write(fd, &base[nbr % size], 1);
	return (rtrn + 1);
}

void	*free_333(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
