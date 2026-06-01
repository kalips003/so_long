/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lengh.c                           		            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:18:30 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 18:06:51 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	len(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

////////////////////////////////////////////////////////
//  return lenght, stops when a char in the dico is found
int	len_m(char *s, char *dico)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && wii(s[i], dico) < 0)
		i++;
	return (i);
}

////////////////////////////////////////////////////////
//  return position of c in dico, -1 if not found
int	wii(char c, char *dico)
{
	int		i;

	if (!dico)
		return (-2);
	i = -1;
	while (dico[++i])
	{
		if (c == dico[i])
			return (i);
	}
	return (-1);
}

int	tab_size(char **tab)
{
	int		size;

	size = 0;
	if (!tab)
		return (0);
	while (tab[size])
		size++;
	return (size);
}
