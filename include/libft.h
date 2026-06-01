/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:06:26 by agallon           #+#    #+#             */
/*   Updated: 2024/06/11 18:25:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
// # include <sys/wait.h>
# include <time.h>

# include "ft_printf.h"
# include "libft.h"
////////////////////////////////////////////////////////////
// # 	GET NEXT LINE									///
# define BUFFER_SIZE 32

typedef struct s_gnl {
	char			buff[BUFFER_SIZE];
	struct s_gnl	*next;
}	t_gnl;

char		*gnl(int fd);
t_gnl		*ini_node(t_gnl *first_list, char (*g_temp)[BUFFER_SIZE], int fd);
void		clean_buff(char *buff, int sw);
void		free_all(t_gnl **first_list);
void		f_copy_rest(t_gnl *last_list, char (*g_temp)[BUFFER_SIZE], int fd);
char		*f_rtrn_2(t_gnl *first_list, char *rtrn, int size);
char		*f_rtrn_1(t_gnl *first_list, int fd, char (*g_temp)[BUFFER_SIZE]);
int			is_there_n(t_gnl *node);
int			rtrn_size(t_gnl *first_list, int fd, char (*g_temp)[BUFFER_SIZE]);

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
int			ft_atoi_v2(char *str, int *i, int *error);
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
void		*free_tab(char **tab);
void		*free_s(void *ptr);
//
int			find_str(char *str, char *str_pattern);
int			same_str(char *str, char *str_pattern);
//	QUARANTINE
char		*fjoin(int how_many_string, int bit_32, ...);

#endif
