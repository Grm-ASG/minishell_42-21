/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:39:34 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 10:41:20 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		Our "ft_echo" takes 3 arguments:
**		1) char *str	= formated string need to output
**		2) int fd		= filedescriptor to write
**		3) char fl_n	= flag "-n", if 1, don't print "\n" (newline) in fd,
**		otherwise print "\n" in fd
*/

/*
**		Wrong implementation "ft_echo" need to take only 2 argumetns:
**		1) char *agrv[]	= arguments of echo
**		2) int fd		= filedescriptor to write
**
**		parsing the "-n" flag need to realise in "ft_echo"
*/

void	ft_echo(char *str, int fd, char fl_n)
{
	ft_putstr_fd(str, fd);
	if (!fl_n)
		ft_putstr_fd("\n", fd);
}