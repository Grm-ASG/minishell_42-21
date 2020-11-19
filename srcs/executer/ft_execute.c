/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:25 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/19 21:55:19 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_call_execve(char *cmd, t_shell *s_shell)
{
	s_shell->s_cmd.fd_stderr = 2;
	s_shell->s_cmd.fd_stdout = 1;
	s_shell->s_cmd.fd_stdin = 0;
	(void)cmd;
	(void)s_shell;
	//return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	ft_execute_command(t_shell *s_shell)
{
	char *const	cmd = s_shell->cmd_line;
	int const	fd = s_shell->fd;
	int			i;

	if (cmd[0] == '\0')
		return ;
	if (!(s_shell->argv = ft_split(cmd, ' ')))
		ft_error(ALLOCATION_FAILED);
	if (ft_strnstr(s_shell->argv[0], "pwd", 3))
		ft_pwd(fd);
	else if (!ft_strcmp(s_shell->argv[0], "cd"))
		ft_cd(s_shell);
	else
	{
		if (ft_call_execve(s_shell->argv[0], s_shell))
		{
			if (!(s_shell->errno_str = strerror(errno)))
				ft_dprintf(2, "ERRNO return NULL in ft_cd ¯\\_(ツ)_/¯\n");
			else
				ft_dprintf(2, "-csh: cd: %s: %s\n", s_shell->argv[0], s_shell->errno_str);
		}

		/*
		**	PRINT COMMAND
		*/
		i ^= i;
		ft_dprintf(fd, "cmd = %s: \n", s_shell->argv[0]);
		while (s_shell->argv[++i])
		{
			ft_dprintf(fd, "%dst argv = %s\n", i, s_shell->argv[i]);
		}
	}
	i = -1;
	while (s_shell->argv[++i])
		ft_free_all(1, &s_shell->argv[i]);
	ft_free_all(1, &s_shell->argv[i]);
	ft_free_all(1, &s_shell->cmd_line);
	ft_bzero(&s_shell->fd, sizeof(t_shell) - 8);
}
