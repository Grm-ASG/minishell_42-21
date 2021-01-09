/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:25 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/24 01:36:00 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_call_execve(char *cmd, t_shell *s_shell)
{
	int			pid;
	int			ret;
	int			status;

	s_shell->s_cmd.fd_stderr = 2;
	s_shell->s_cmd.fd_stdout = 1;
	s_shell->s_cmd.fd_stdin = 0;
	(void)cmd;

	if ((pid = fork()) < 0)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		if ((ret = execve(s_shell->argv[0], s_shell->argv, s_shell->envp)) == -1)
		{
			if (!(s_shell->errno_str = strerror(errno)))
				ft_dprintf(2, "strerror return NULL in %s: ¯\\_(ツ)_/¯\n", \
							s_shell->argv[0]);
			else
				ft_dprintf(2, "-csh: %s: %s\n", s_shell->argv[0], \
							s_shell->errno_str);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(0, &status, 0);
		if (WIFSIGNALED(status))
			ft_dprintf(2, "Error\n");
		else if (WEXITSTATUS(status))
			ft_dprintf(2, "Exited Normally\n");
	}
	return (EXIT_SUCCESS);
}

void	ft_clear_exit(t_shell *s_shell)
{
	s_shell->s_cmd.exit = 1;
	if (s_shell->argv[1])
		s_shell->exit_status = ft_atoi(s_shell->argv[1]);
	else 	//TODO check argument of exit
		s_shell->exit_status = 0;
	get_next_line(0, NULL);
	ft_free_array(&s_shell->envp);
	free( s_shell->home_dir_init);
}

void	ft_exec_builtin(t_shell *s_shell)
{
	if (!ft_strcmp(s_shell->argv[0], "echo"))
		ft_echo(s_shell->argv);
	else if (!ft_strcmp(s_shell->argv[0], "cd"))
		ft_cd(s_shell);
	else if (!ft_strcmp(s_shell->argv[0], "pwd"))
		ft_pwd(STDOUT);
	else if (!ft_strcmp(s_shell->argv[0], "exit"))
		ft_clear_exit(s_shell);
}

void	ft_find_cmd_path(t_shell *s_shell)
{
	char	*tmp;

	tmp = s_shell->argv[0];
	if (!(s_shell->argv[0] = ft_strjoin("/usr/bin/", s_shell->argv[0])))
		ft_error(ALLOCATION_FAILED);
	free(tmp);
}

void	ft_exec_extern(t_shell *s_shell)
{
	int			i;

	ft_find_cmd_path(s_shell);
	if (ft_call_execve(s_shell->argv[0], s_shell))
	{
		if (!(s_shell->errno_str = strerror(errno)))
			ft_dprintf(2, "strerror return NULL in %s: ¯\\_(ツ)_/¯\n", \
						s_shell->argv[0]);
		else
			ft_dprintf(2, "-csh: %s: %s\n", s_shell->argv[0], \
						s_shell->errno_str);
	}
	//DELETE Debug printf
	if (1)
	{
		i = 0;
		ft_dprintf(STDOUT, "\n!DEBUG!\ncmd = %s: \n", s_shell->argv[0]);
		while (s_shell->argv[++i])
			ft_dprintf(STDOUT, "%dst argv = %s\n", i, s_shell->argv[i]);
	}
}

int		ft_check_cmd_builtin(char *cmd)
{
	int			i;
	const char	*cmds[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};

	i = 0;
	while (cmds[i])
		if (!ft_strcmp(cmds[i++], cmd))
			return (1);
	return (0);
}

void	ft_get_next_cmd(t_shell *s_shell)
{
	if (s_shell->s_cmd.start->next == NULL)
		s_shell->s_cmd.end = 1;
	//TODO
}

void	ft_execute_command(t_shell *s_shell)
{
	while (!s_shell->s_cmd.end)
	{
		ft_get_next_cmd(s_shell);
		if (ft_check_cmd_builtin(s_shell->argv[0]))
			ft_exec_builtin(s_shell);
		else
			ft_exec_extern(s_shell);
		ft_free_array(&s_shell->argv);
	}
}
