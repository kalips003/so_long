/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:34:49 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 18:23:11 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	w_len(char *str, char *sep)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (str[++i] && wii(str[i], sep) < 0)
		len++;
	return (len);
}

static int	count_w(char *str, char *sep)
{
	int	num_w;
	int	i;

	num_w = 0;
	i = -1;
	while (str[++i])
	{
		if (wii(str[i], sep) < 0 && (wii(str[i + 1], sep) \
			>= 0 || !str[i + 1]))
			num_w++;
	}
	return (num_w);
}

static void	split_help(char **str, char *sep, int *i, char **rtrn)
{
	int	w_l;
	int	j;

	w_l = w_len(*str, sep);
	j = -1;
	*rtrn = (char *)malloc(w_l + 1);
	if (!(*rtrn))
		return ;
	while (++j < w_l)
	{
		(*rtrn)[j] = **str;
		(*str)++;
	}
	(*rtrn)[j] = '\0';
	(*i)++;
}

//////////////////////////////////////////////////////
//  #   split
char	**split(char *str, char *sep)
{
	char	**rtrn;
	int		num_w;
	int		i;

	if (!str)
		return (NULL);
	num_w = count_w(str, sep);
	rtrn = (char **)malloc(sizeof(char *) * (num_w + 1));
	if (!rtrn)
		return (NULL);
	i = 0;
	while (i < num_w)
	{
		if (wii(*str, sep) < 0)
			split_help(&str, sep, &i, &rtrn[i]);
		else
			str++;
	}
	rtrn[i] = NULL;
	return (rtrn);
}
