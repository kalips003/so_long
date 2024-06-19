/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:01:33 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 19:01:33 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
 #   join the read bits
 	if bit 10 = begin is malloc'd
 	if bit 01 = append is malloc'd
	if size = 0, join full size
		always return at least a '\0' that can be free
		return NULL on error
*******************************************************************************/
char	*join(char *begin, char *append, int bit, int size)
{
	int		i;
	int		ptr;
	char	*str;

	if (begin && !append && ((bit >> 1) & 1))
		return (begin);
	i = ft_strlen666(append);
	size = i * (i <= size || !size) + size * (i > size && size);
	str = (char *)malloc(ft_strlen666(begin) + size + 1);
	if (str)
	{
		ptr = 0;
		while (++ptr && begin && begin[ptr - 1])
			str[ptr - 1] = begin[ptr - 1];
		i = 0;
		while (++i && append && i - 1 < size)
			str[ptr + i - 2] = append[i - 1];
		str[ptr + i - 2] = '\0';
	}
	if ((bit >> 1) & 1 && begin)
		free(begin);
	if (bit & 1 && append)
		free(append);
	return (str);
}

////////////////////////////////////////////////////////////
//	#	[scpiduxX%bofeES]
t_str	g_tab[] = {NULL,
	pt_string,
	pt_char,
	NULL,
	pt_num, // ft_int,
	pt_num,
	pt_num, // ft_unsigned,
	pt_hex, // ft_hexa,
	pt_hex,
	NULL,
	NULL, // ft_binary,
	NULL, // ft_octal,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL};

////////////////////////////////////////////////////////////
static char	*le(char *s, char *app, int *inc)
{
	int		i;

	i = 0;
	while (app && app[i] && app[i] != '%')
		i++;
	s = join(s, app, 0b10, i);
	*inc += i;
	return (s);
}

////////////////////////////////////////////////////////////
//	#	CREATE STRUCT
char	*f_2(char *str, int *i, va_list args)
{
	t_flags	f;
	char	*rtrn;

	f_ini_struct(&f, 1);
	f_fill_struct(&str[*i + 1], &f, args);
	f_error_check(&f);
	rtrn = NULL;
	if (f.error)
	{
		if (f.error == -2)
			return (NULL);
		*i += 1;
		return (join(NULL, "%", 0b00, 0));
	}
	if (g_tab[wii_print(f.flag)])
		rtrn = g_tab[wii_print(f.flag)](args, &f);
	*i += f.increment;
	return (rtrn);
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
	(char *)printf
		return NULL on error
*******************************************************************************/
//	#	(char *)printf

char	*str(char *str, ...)
{
	va_list	args;
	int		i;
	char	*rtrn;

	if (!str)
		return (join(NULL, NULL, 0b00, 0));
	va_start(args, str);
	rtrn = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			rtrn = join(rtrn, f_2(str, &i, args), 0b11, 0);
		else
			rtrn = le(rtrn, &str[i], &i);
		if (!rtrn)
			return (NULL);
	}
	va_end(args);
	return (rtrn);
}
