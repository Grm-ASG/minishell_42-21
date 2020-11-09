/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:04:47 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 20:43:22 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		TODO maybe rewrite with structure?
*/

void	ft_env(int fd, char *envp[])
{
	int i;

	i = -1;
	while (envp[++i])
	{
		ft_putstr_fd(envp[i], fd);
		ft_putstr_fd("\n", 1);
	}
}
