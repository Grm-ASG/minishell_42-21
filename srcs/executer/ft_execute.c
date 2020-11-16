/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:25 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 16:46:59 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_command(t_shell *s_shell)
{
	char *const	cmd = s_shell->cmd_line;
	int const	fd = s_shell->fd;
	int			i;
	
	if (cmd[0] == '\0')
		return ;
	s_shell->argv = ft_split(s_shell->cmd_line, ' ');
	if (!s_shell->argv)
		ft_error(ALLOCATION_FAILED);
	if (ft_strnstr(cmd, "pwd", 3))
		ft_pwd(fd);
	else if (ft_strnstr(cmd, "cd", 3))
		ft_cd(s_shell->argv, s_shell->envp);
	else
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd("\n", fd);
	}
	i = -1;
	while (s_shell->argv[++i])
		free(s_shell->argv[i]);
	free(s_shell->argv[i]);
	free(s_shell->cmd_line);
	ft_bzero(s_shell, sizeof(t_shell));
}