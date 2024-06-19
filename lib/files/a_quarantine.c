/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_quarantine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:34:49 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 17:57:12 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

//////////////////////////////////////////////////////
//  #   join the read bits free with info from bit
char	*fjoin(int str_num, int bit_32, ...)
{
	va_list		args;
	int			i;
	char		*rtrn;

	va_start(args, bit_32);
	rtrn = NULL;
	i = -1;
	while (++i < str_num && i < 32)
		rtrn = join(rtrn, (char *)va_arg(args, char *), \
		((bit_32 >> (str_num - i - 1)) & 1) + 2 * !!rtrn, 0);
	va_end(args);
	return (rtrn);
}

//////////////////////////////////////////////////////////// (%S)
//	%<size>S return ptr to copied memory
char	*pt_memcpy(char *str)
{
	return (str);
}

//////////////////////////////////////////////////////////// (%I)
//	%I return ptr to written int tab
// 	int **tab = str(1,2,3,-4,5\n3,-1,-5,1\n);
/*
	= [{3} ;
		(5) 1,2,3,-4,5 ;
		(4) 3,-1,-5,1 ;
		(0) ]
*/
int	**pt_numtab(char *num_tab)
{
	return ((int **)num_tab);
}
