/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c		                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:13:21 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 17:57:07 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

///////////////////////////////////////////////////////
// #	RESET TEMP || CLEAN BUFFER
void	clean_buff(char *buff, int sw)
{
	int	i;

	i = 0;
	if (sw == 0)
	{
		while (i < BUFFER_SIZE)
			buff[i++] = '\0';
	}
	else
	{
		while (i < BUFFER_SIZE && buff[i] != '\0')
			buff[i++] = '\0';
	}
}

///////////////////////////////////////////////////////
// #	FREE ALL NODES FROM FIRST
void	free_all(t_gnl **first_list)
{
	t_gnl	*current_list;
	t_gnl	*temp_list;

	current_list = *first_list;
	while (current_list != NULL)
	{
		temp_list = current_list->next;
		free(current_list);
		current_list = temp_list;
	}
	*first_list = NULL;
}

///////////////////////////////////////////////////////
// #	RETURN SIZE OF NEXT \N		+1 if \n found
int	is_there_n(t_gnl *node)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (node->buff[i] == '\0')
			return (-i);
		if (node->buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-i);
}

////////////////////////////////////////[0000][0123][4\n56]
// #	RETURN RESULT	1 > 2
char	*f_rtrn_2(t_gnl *first_list, char *rtrn, int size)
{
	t_gnl	*current_list;
	int		i;
	int		j;

	i = 0;
	j = 0;
	current_list = first_list;
	while (j < size)
	{
		if (i == BUFFER_SIZE || current_list->buff[i] == '\0')
		{
			current_list = current_list->next;
			i = 0;
		}
		if (current_list->buff[i] != '\0')
			rtrn[j++] = current_list->buff[i];
		i++;
	}
	rtrn[j] = '\0';
	return (rtrn);
}
