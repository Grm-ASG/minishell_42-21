/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:15:51 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/24 00:48:06 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Bad comment for norminette error and check errno value
//HOME == NULL need to handle

static void	ft_go_home(t_shell *s_shell, int fd_err)
{
	if (!s_shell->s_cd.home_dir)
		ft_dprintf(fd_err, "-csh: cd: HOME not set\n");
	else if (!ft_strcmp(s_shell->s_cd.home_dir, ""))
		;
	else if ((s_shell->s_cd.ret = chdir(s_shell->s_cd.home_dir)) != -1 && \
			(ft_strcmp(s_shell->s_cd.home_dir, s_shell->s_cd.init_dir)))
	{
		ft_change_env(s_shell->envp, "PWD", s_shell->s_cd.home_dir);
		ft_change_env(s_shell->envp, "OLDPWD", s_shell->s_cd.init_dir);
	}
	else
	{
		if (!(s_shell->errno_str = strerror(errno)))
			ft_dprintf(fd_err, "ERRNO return NULL in ft_cd ¯\\_(ツ)_/¯\n");
		else
			ft_dprintf(fd_err, "-csh: cd: %s: %s\n",\
						s_shell->s_cd.home_dir, s_shell->errno_str);
	}
}

void		ft_go_last_path(t_shell *s_shell, int fd_stdout)
{
	s_shell->s_cd.last_path = ft_get_env_value(s_shell->envp, "OLDPWD");
	if (!s_shell->s_cd.last_path)
		ft_dprintf(s_shell->s_cmd.fd_stderr, "-csh: cd: OLDPWD not set\n");
	else
	{
		s_shell->s_cd.ret = chdir(s_shell->s_cd.last_path);
		if (s_shell->s_cd.ret == -1)
		{
			if (!(s_shell->errno_str = strerror(errno)))
				ft_dprintf(s_shell->s_cmd.fd_stderr, \
							"ERRNO return NULL in ft_cd ¯\\_(ツ)_/¯\n");
			else
				ft_dprintf(s_shell->s_cmd.fd_stderr, "-csh: cd: %s: %s\n",\
							s_shell->s_cd.home_dir, s_shell->errno_str);
		}
		else
		{
			ft_putendl_fd(s_shell->s_cd.last_path, fd_stdout);
			ft_change_env(s_shell->envp, "OLDPWD", s_shell->s_cd.init_dir);
		}
	}
}

static void	ft_go_arg(t_shell *s_shell, int fd_stderr, char **tmp_argv)
{
	if (s_shell->argv[1][0] == '~' && !((*tmp_argv) = \
	ft_strjoin(s_shell->s_cd.home_dir, &s_shell->argv[1][1])))
		ft_error(ALLOCATION_FAILED);
	if (!ft_strcmp(s_shell->argv[1], "-"))
		ft_go_last_path(s_shell, s_shell->s_cmd.fd_stdout);
	else
	{
		s_shell->s_cd.ret = chdir((*tmp_argv) ? (*tmp_argv) : s_shell->argv[1]);
		if (s_shell->s_cd.ret == -1)
		{
			if (!(s_shell->errno_str = strerror(errno)))
				ft_dprintf(fd_stderr,\
							"ERRNO return NULL in ft_cd ¯\\_(ツ)_/¯\n");
			else
			{
				ft_dprintf(fd_stderr, "-csh: cd: ");
				if (!ft_strcmp(s_shell->argv[1], "~") || \
					s_shell->argv[1][1] == '/')
					ft_dprintf(fd_stderr, "%s", (*tmp_argv));
				else
					ft_dprintf(fd_stderr, "%s", s_shell->argv[1]);
				ft_dprintf(fd_stderr, ": %s\n", s_shell->errno_str);
			}
		}
	}
}

void		ft_cd(t_shell *s_shell)
{
	if (!(s_shell->s_cd.home_dir = ft_get_env_value(s_shell->envp, "HOME")))
		if (!(s_shell->s_cd.home_dir = ft_strdup(s_shell->home_dir_init)))
			ft_error(ALLOCATION_FAILED);
	if (!(s_shell->s_cd.init_dir = getcwd(NULL, 0)))
		ft_error(ALLOCATION_FAILED);
	if (s_shell->argv[1] == NULL)
		ft_go_home(s_shell, s_shell->s_cmd.fd_stderr);
	else if (s_shell->argv[2] != NULL)
		ft_putendl_fd("-csh: cd: too many arguments", s_shell->s_cmd.fd_stderr);
	else
		ft_go_arg(s_shell, s_shell->s_cmd.fd_stderr, &s_shell->s_cd.tmp_argv);
	if (!(s_shell->s_cd.new_dir = (char *)getcwd(NULL, 0)))
		ft_error(ALLOCATION_FAILED);
	if (ft_strcmp(s_shell->s_cd.new_dir, s_shell->s_cd.init_dir))
	{
		ft_change_env(s_shell->envp, "PWD", s_shell->s_cd.new_dir);
		ft_change_env(s_shell->envp, "OLDPWD", (char *)s_shell->s_cd.init_dir);
	}
	ft_free_all(5, &s_shell->s_cd.init_dir, &s_shell->s_cd.new_dir, \
				&s_shell->s_cd.home_dir, &s_shell->s_cd.last_path, \
				&s_shell->s_cd.tmp_argv);
}
