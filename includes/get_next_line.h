/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:07:33 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 20:46:59 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct		s_gnl
{
	int				fd;
	char			*tail;
	char			*start_tail;
	char			*line_back_up;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(int fd, char **line);
int					ft_exit_gnl(char *buf, int fd, t_gnl **prime, int result);
char				*ft_strchr_gnl(const char *s, int c);
char				*ft_strdup_gnl(const char *s);
t_gnl				*ft_lst_new_gnl(int fd);
t_gnl				*ft_find_lst_gnl(int fd, t_gnl **prime);

#endif
