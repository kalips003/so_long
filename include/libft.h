/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:06:26 by agallon           #+#    #+#             */
/*   Updated: 2024/05/31 15:46:00 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <time.h>

# include "ft_printf.h"
# include "libft.h"
////////////////////////////////////////////////////////////
// # 	GET NEXT LINE									///
# define BUFFER_SIZE 32

typedef struct s_list {
	char			buff[BUFFER_SIZE];
	struct s_list	*next;
}	t_list;

char		*gnl(int fd);
t_list		*ini_node(t_list *first_list, char (*g_temp)[BUFFER_SIZE], int fd);
void		clean_buff(char *buff, int sw);
void		free_all(t_list **first_list);
void		f_copy_rest(t_list *last_list, char (*g_temp)[BUFFER_SIZE], int fd);
char		*f_rtrn_2(t_list *first_list, char *rtrn, int size);
char		*f_rtrn_1(t_list *first_list, int fd, char (*g_temp)[BUFFER_SIZE]);
int			is_there_n(t_list *node);
int			rtrn_size(t_list *first_list, int fd, char (*g_temp)[BUFFER_SIZE]);

////////////////////////////////////////////////////////////
// # 	LIBFT											///
char		**split(char *str, char *sep);
//
int			len(char *s);
int			len_m(char *s, char *dico);
int			wii(char c, char *dico);
int			tab_size(char **tab);
//
int			atoi_v(const char *str);
int			ft_atoi(char *str, int *error);
//
char		*ft_memset(void *s, char c, int size);
void		*mem(char c, int size);
//
// int			abs(int num);
int			min(int a, int b);
int			max(int a, int b);
int			min_all(int how_many, ...);
int			max_all(int how_many, ...);
//
void		*expand(void *ptr, int size, int add);
char		**expand_tab(char **tab, char *new_line);
void		free_tab(char **tab);
void		free_s(void **ptr);
//
int			find_str(char *str, char *str_pattern);
int			same_str(char *str, char *str_pattern);
//	QUARANTINE
char		*fjoin(int how_many_string, int bit_32, ...);

#endif
