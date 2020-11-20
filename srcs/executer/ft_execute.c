/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:25 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/20 15:26:57 by imedgar          ###   ########.fr       */
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
	return (EXIT_SUCCESS);
	//return (EXIT_FAILURE);
}

void	ft_clear_exit(t_shell *s_shell)
{
	int i;

	s_shell->fl_work = 1;
	if (s_shell->argv[1]) //TODO check argument of exit
		s_shell->exit_status = ft_atoi(s_shell->argv[1]);
	else
		s_shell->exit_status = 0;
	get_next_line(0, NULL);
	i = 0;
	while (s_shell->envp[i])
		ft_free_all(1, &s_shell->envp[i++]);
	ft_free_all(3, &s_shell->envp, &s_shell->s_cd.home_dir_init, &s_shell->cmd_line);

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
	else if (!ft_strcmp(s_shell->argv[0], "exit"))
		ft_clear_exit(s_shell);
	else
	{
		if (ft_call_execve(s_shell->argv[0], s_shell))
		{
			//TODO ERR CASE
			if (!(s_shell->errno_str = strerror(errno)))
				ft_dprintf(2, "ERRNO return NULL in %s: ¯\\_(ツ)_/¯\n", s_shell->argv[0]);
			else
				ft_dprintf(2, "-csh: %s: %s\n", s_shell->argv[0], s_shell->errno_str);
		}
		/*
		**	PRINT COMMAND
		*/
		i = 0;
		ft_dprintf(fd, "cmd = %s: \n", s_shell->argv[0]);
		while (s_shell->argv[++i])
		{
			ft_dprintf(fd, "%dst argv = %s\n", i, s_shell->argv[i]);
		}
	}
	i = 0;
	while (s_shell->argv[i])
		ft_free_all(1, &s_shell->argv[i++]);
	ft_free_all(1, &s_shell->argv);
	ft_free_all(1, &s_shell->cmd_line);
}
