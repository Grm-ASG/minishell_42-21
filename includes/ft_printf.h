/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 20:57:47 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/18 19:32:31 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define ERROR -2

typedef struct	s_fl
{
	int			fd;
	char		pdn;
	char		zer;
	char		type;
	char		neg_width;
	char		neg_prec;
	long long	prec;
	long long	width;
}				t_fl;

int				ft_dprintf(int fd, const char *format, ...);
int				ft_form_prnt(va_list factor, const char **format, int fd);
void			ft_prec(const char **str, va_list factor, t_fl *fl);
int				ft_type(t_fl *fl, const char *str, \
						va_list factor, const char **format);
int				ft_putchars(char c, int nbr, char *str, t_fl *fl);
int				ft_print_char(char c, t_fl *fl);
int				ft_print_str(char *str, t_fl *fl);
int				ft_print_adr(long long num, t_fl *fl);
int				ft_print_nbr(long long adr, t_fl *fl, char base, char x);
void			ft_init(t_fl *fl);
long long		ft_star_width(long long star, t_fl *fl);

#endif
