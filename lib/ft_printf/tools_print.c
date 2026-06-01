/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:31:39 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 18:33:49 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

////////////////////////////////////////////////////////////
//	#	RETURN INT != 0 IF IN SET
int	wii_print(char c)
{
	char	*char_set;
	int		i;

	char_set = "0# -+.123456789scpiduxX%bofeESt";
	i = -1;
	while (char_set[++i])
		if (char_set[i] == c)
			break ;
	if (i < 5)
		return (-1);
	if (i == 5)
		return (-2);
	if (i < 15)
		return (-3);
	if (i < ft_strlen666(char_set))
		return (i - 14);
	return (0);
}

////////////////////////////////////////////////////////////
//	#	WRITE NUM IN CORRESPONDING BASE, NO SIGN
int	ft_putnbr_base(int fd, long long nbr, char *base)
{
	int			size;
	int			rtrn;

	rtrn = 0;
	size = ft_strlen666(base);
	if (size < 2)
		return (-1);
	if (nbr < 0)
		nbr = -nbr;
	if (nbr >= size)
		rtrn += ft_putnbr_base(fd, nbr / size, base);
	write(fd, &base[nbr % size], 1);
	return (rtrn + 1);
}

////////////////////////////////////////////////////////////
//	#	WRITE FLOAT
int	ft_put_float(double nbr, t_flags *f)
{
	long long	int_part;
	double		fract_part;
	int			size;
	int			i;

	if (nbr < 0)
		nbr = -nbr;
	int_part = (long long)nbr;
	fract_part = nbr - (long long)nbr;
	size = ft_putnbr_base(f->fd, (long long)nbr, "0123456789");
	if (!(f->point && f->preci == 0) || f->hash)
		size += write(f->fd, ".", 1);
	i = 0;
	while (i < f->preci)
	{
		int_part = (long long)(fract_part * 10) + '0';
		fract_part = (fract_part * 10) - \
				(unsigned long long)((fract_part * 10));
		write(f->fd, &int_part, 1);
		i++;
	}
	return (size + i);
}

////////////////////////////////////////////// 0.[preci]e+00
//	#	WRITE SCIENCE, THE CAKE IS NOT WRITTEN
static int	ft_put_science_zero(t_flags *f)
{
	int	size;
	int	i;

	size = write(f->fd, "0", 1);
	if (!(f->point && f->preci == 0) || f->hash)
		size += write(f->fd, ".", 1);
	i = 0;
	while (i++ < f->preci)
		size += write(f->fd, "0", 1);
	size += write(f->fd, &f->flag, 1);
	size += write(f->fd, "+00", 3);
	return (size);
}

int	ft_put_science(double nbr, t_flags *f)
{
	int	size;
	int	puissance;

	if (nbr == 0)
		return (ft_put_science_zero(f));
	size = 0;
	if (nbr < 0)
		nbr = -nbr;
	puissance = 0;
	while (nbr >= 10 && ++puissance)
		nbr /= 10;
	while (nbr < 1 && --puissance && nbr != 0)
		nbr *= 10;
	size += print_fd(f->fd, "%0.*f%c%+.2d", f->preci, nbr, f->flag, puissance);
	return (size);
}
