/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:34:49 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 18:03:09 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

//////////////////////////////////////////////////////
//  #   FIND SUBSTRING, RETURN POSI, -1 IF NOT FOUND
int	find_str(char *str, char *str_pattern)
{
	int	i;
	int	j;
	int	k;
	int	len_max;

	i = -1;
	if (!str || !str_pattern)
		return (-1);
	len_max = len(str) - len(str_pattern);
	while (str[++i] && i <= len_max)
	{
		j = -1;
		k = i;
		while (str_pattern[++j] && str[k] == str_pattern[j])
			k++;
		if (!str_pattern[j])
			return (i);
	}
	return (-1);
}

//////////////////////////////////////////////////////
//  #   FIND SUBSTRING, RETURN POSI, -1 IF NOT FOUND
int	same_str(char *str, char *str_pattern)
{
	int	lenght;
	int	lenght2;

	lenght = len(str);
	lenght2 = len(str_pattern);
	if (lenght == lenght2 && !find_str(str, str_pattern))
		return (0);
	return (-1);
}
