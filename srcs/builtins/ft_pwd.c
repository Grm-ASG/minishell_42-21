/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:16:40 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/20 20:50:50 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pwd(int fd)
{
	const char	*path_name = getcwd(NULL, 0);
	char		*err;
	const int	fd_strerr = 2;
	const int	fd_stdout = fd;

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
