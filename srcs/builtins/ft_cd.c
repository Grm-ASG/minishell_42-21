/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:15:51 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 20:11:21 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free((void *)init_dir);
		return ;
	}
	ret = chdir(home_dir);
	if (!(ft_strcmp(home_dir, init_dir)))
		ft_change_env(s_shell->envp, "PWD", home_dir);
	ft_change_env(s_shell->envp, "OLDPWD", (char *)init_dir);
	free(home_dir);
	if (ret == -1)
	{
		//TODO errno how to;
		ft_putendl_fd("-csh: cd: No such file or directory", 2);
	}

}

static void ft_go_arg(t_shell *s_shell, const char *init_dir)
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
			ft_change_env(s_shell->envp, "OLDPWD", (char *)init_dir);
		}
	}
	else
		ret = chdir(tmp_argv ? tmp_argv : s_shell->argv[1]);
	if (ret == -1)
	{
		//TODO errno how to check value and print error about errno;
		ft_putstr_fd("-csh: cd: ", 2);
		ft_putstr_fd(tmp_argv ? tmp_argv : s_shell->argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	free((void*)last_path);
	free(tmp_argv);
	free((void*)home);
}

void		ft_cd(t_shell *s_shell)
{
	static t_cd		s_cd;
	const char		*init_dir = getcwd(NULL, 0);

	if (!init_dir)
		ft_error(ALLOCATION_FAILED);
	if (!s_shell->argv[1])
		ft_go_home(s_shell, init_dir);
	else if (s_shell->argv[2])
		ft_putendl_fd("-csh: cd: too many arguments", 2);
	else
		ft_go_arg(s_shell, init_dir);
		
	s_cd.new_dir = getcwd(NULL, 0);
	if (ft_strcmp(s_cd.new_dir, init_dir))
	{
		ft_change_env(s_shell->envp, "PWD", s_cd.new_dir);
		ft_change_env(s_shell->envp, "OLDPWD", (char *)init_dir);
	}	
	free((void *)init_dir);
	free((void *)s_cd.new_dir);
	return ;
}
