/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:25 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 13:28:12 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_command(t_shell *s_shell)
{
	char *const	cmd = s_shell->cmd_line;
	int const	fd = s_shell->fd;
	char		up_key[3];

	up_key[0] = 0x1B;
	up_key[1] = 0x5B;
	up_key[2] = 0x41;
	if (cmd[0] == '\0')
		return ;
	if (!ft_memcmp(cmd, up_key, 3))
	{
		ft_putstr_fd("UPKEY PRESSED\n", fd);
	}
	if (ft_strnstr("pwd", cmd, 3))
		ft_pwd(fd);
	else
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd("\n", fd);
	}
	free(s_shell->cmd_line);
	ft_bzero(s_shell, sizeof(t_shell));
}