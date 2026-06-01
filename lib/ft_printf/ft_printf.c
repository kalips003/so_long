/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:06:22 by agallon           #+#    #+#             */
/*   Updated: 2024/06/11 18:32:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

////////////////////////////////////////////////////////////
//	#	[scpiduxX%bofeESt]
t_func		g_function_pointer[] = {NULL,
	ft_string,
	ft_char,
	ft_pointer,
	ft_int,
	ft_int,
	ft_unsigned,
	ft_hexa,
	ft_hexa,
	ft_percent,
	ft_binary,
	ft_octal,
	ft_float,
	ft_scientific,
	ft_scientific,
	ft_string_hexa,
	ft_tab,
	NULL};

////////////////////////////////////////////////////////////
//	#	CREATE STRUCT
static int	f_1(const char *str, int *i, va_list args, int fd)
{
	t_flags	f;
	int		rtrn;

	if (fd < 0 || fd > 1024)
		return (-1);
	f_ini_struct(&f, fd);
	f_fill_struct(&str[*i + 1], &f, args);
	f_error_check(&f);
	if (f.error)
	{
		if (f.error == -2)
			return (-1);
		*i += write(fd, "%", 1);
		return (1);
	}
	rtrn = g_function_pointer[wii_print(f.flag)](args, &f);
	*i += f.increment;
	return (rtrn);
}

////////////////////////////////////////////////////////////
//	#
int	put(const char *str, ...)
{
	va_list	args;
	int		i;
	int		sum;
	int		r;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	sum = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			r = f_1(str, &i, args, 1);
			if (r < 0)
				return (-1);
			sum += r;
		}
		else
			sum += write(1, &str[i++], 1);
	}
	va_end(args);
	return (sum);
}

////////////////////////////////////////////////////////////
//	#
int	print_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		sum;
	int		r;

	if (!str || fd < 0)
		return (-1);
	va_start(args, str);
	i = 0;
	sum = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			r = f_1(str, &i, args, fd);
			if (r < 0)
				return (-1);
			sum += r;
		}
		else
			sum += write(fd, &str[i++], 1);
	}
	va_end(args);
	return (sum);
}


/*******************************************************************************
 * 		PRINT CAT RANDOM COLOR
*******************************************************************************/
void	ft_print_cat(int num,  char *string2, int cls)
{
	int color1;
	int color2;
	int color3;

	color1 = (int)(rand() % (255  + 1));
	color2 = (int)(rand() % (255  + 1));
	color3 = (int)(rand() % (255  + 1));

	if (cls)
		put(CLS);
	put("\033[38;5;%dm\
	\tにゃ~\033[38;5;%dm\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀\033[38;5;%dm~ %d ~\033[38;5;%dm\n\
	\t\t⠀|、˜\\\t\t\t\033[38;5;%dm~ %s\033[38;5;%dm\n\
	\t\t⠀じしˍ)ノ\n", \
	color2, color1, color2, num, color1, color2, string2, color1);
	put(BLINK "\033[38;5;%dm\n\t\t>>>  PRISS ENTER TO CONTINUE  <<<\n"RESET, color3);
	free_333(gnl(0));
}