/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:15:51 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 21:49:30 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	HOWTO check errno value and print error depending on errno
**	need to improve this!
*/
//Bad comment for norminette error and check errno value

static void	ft_go_home(t_shell *s_shell, const char *init_dir)
{
	char	*home_dir;
	int		ret;

	home_dir = ft_get_env_value(s_shell->envp, "HOME");
	if (!home_dir)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("-csh: cd: HOME not set", 2);
		ft_putstr_fd(DEFLT, 2);
		ft_free_all(1, &init_dir);
		return ;
	}
	ret = chdir(home_dir);
	if (!(ft_strcmp(home_dir, init_dir)))
		ft_change_env(s_shell->envp, "PWD", home_dir);
	ft_change_env(s_shell->envp, "OLDPWD", (char *)init_dir);
	ft_free_all(1, &home_dir);
	if (ret == -1)
	{
		ft_putendl_fd("-csh: cd: No such file or directory", 2);
	}
}

static void	ft_go_arg(t_shell *s_shell, const char *init_dir)
{
	const char		fl_last_path = !ft_strcmp(s_shell->argv[1], "-");
	const char		*last_path = ft_get_env_value(s_shell->envp, "OLDPWD");
	const char		tilda = s_shell->argv[1][0] == '~';
	char			*tmp_argv;
	const char		*home = ft_get_env_value(s_shell->envp, "HOME");
	int				ret;

	ret = 0;
	tmp_argv = NULL;
	if (tilda)
		tmp_argv = ft_strjoin(home, &s_shell->argv[1][1]);
	if (fl_last_path)
	{
		if (!last_path)
		{
			ft_putendl_fd("-csh: cd: OLDPWD not set", 2);
		}
		else
		{
			ret = chdir(last_path);
			ft_putendl_fd((char *)last_path, 1);
			ft_change_env(s_shell->envp, "OLDPWD", (char *)init_dir);
		}
	}
	else
		ret = chdir(tmp_argv ? tmp_argv : s_shell->argv[1]);
	if (ret == -1)
	{
		ft_putstr_fd("-csh: cd: ", 2);
		ft_putstr_fd(tmp_argv ? tmp_argv : s_shell->argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	ft_free_all(3, &last_path, &tmp_argv, &home);
}

void		ft_cd(t_shell *s_shell)
{
	char		*new_dir;
	const char	*init_dir = getcwd(NULL, 0);

	if (!init_dir)
		ft_error(ALLOCATION_FAILED);
	if (!s_shell->argv[1])
		ft_go_home(s_shell, init_dir);
	else if (s_shell->argv[2])
		ft_putendl_fd("-csh: cd: too many arguments", 2);
	else
		ft_go_arg(s_shell, init_dir);
	new_dir = getcwd(NULL, 0);
	if (ft_strcmp(new_dir, init_dir))
	{
		ft_change_env(s_shell->envp, "PWD", new_dir);
		ft_change_env(s_shell->envp, "OLDPWD", (char *)init_dir);
	}
	ft_free_all(2, &init_dir, &new_dir);
}
