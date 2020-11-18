/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:16:40 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/18 23:01:49 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**			Our "pwd" takes 2 argument:
**			1) int fd_stdout = filedescriptor to write standart output
**			2) int fd_stderr = filedescriptor to write standart errors
*/

void		ft_pwd(int fd_stdout, int fd_strerr)
{
	const char	*path_name = getcwd(NULL, 0);
	char		*err;

	if (!path_name)
	{
		if (!(err = strerror(errno)))
			ft_dprintf(fd_strerr, "ERRNO return NULL in ft_pwd ¯\\_(ツ)_/¯\n"); 
		else
			ft_dprintf(fd_strerr, "-csh: pwd: %s\n", err);
	}
	else
		ft_dprintf(fd_stdout, "%s\n", (char *)path_name);
	free((char *)path_name);
}
