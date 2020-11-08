/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:24:18 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/08 22:40:41 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	TODO Delete stdio.h
*/
#include <stdio.h>

char	*ft_get_username(char *envp[])
{
	int i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "USERNAME=", 9))
			return (ft_strdup(&envp[i][9]));
	}
	return (NULL);
}

void	ft_type_promt(char *envp[])
{
	char	*user;

	user = ft_get_username(envp);
	ft_putstr_fd(user, 1);
	ft_putstr_fd("@MyOwnShell$ ", 1);
	free(user);
}

void	ft_read_command(void)
{
	char	buf[2];
	int		ret;

	while (1)
	{
		if ((ret = read(0, buf, 1)) < 0)
			break ;
		if (buf[0] == 10)
			break ;
		ft_putstr_fd(buf, 1);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	if (argc || argv)
	{
	}
	while (1)
	{
		ft_type_promt(envp);
		ft_read_command();
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
