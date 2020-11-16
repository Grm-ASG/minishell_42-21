/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:15:51 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 16:59:34 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd(char *argv[], char *envp[])
{
	static t_cd		s_cd;
	const char		fl_last_path = (argv[1][0] == '-' && !argv[1][1]);
	const char		*work_dir = getcwd(NULL, 0);
	int				ret;
	char			*home_dir;

	if (!work_dir)
		ft_error(ALLOCATION_FAILED);
	if (!argv[1])
	{
		home_dir = ft_get_env_value(envp, "HOME");
		if (!home_dir)
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("$HOME env not set", 2);
			ft_putstr_fd(DEFLT, 2);
			free((void *)work_dir);
			return ;
		}
		ret = chdir(home_dir);
	}
	if (argv[2])
		ft_putendl_fd("-csh: cd: too many arguments", 2);
	else if (fl_last_path)
	{
		if (!s_cd.last_path)
		{
			free((void *)work_dir);
			ft_putendl_fd("-csh: cd: OLDPWD not set", 2);
			return ;
		}
		else
			ret = chdir(s_cd.last_path);
	}
	else
	{
		ret = chdir(argv[1]);
	}
	if (ret == -1)
	{
		//TODO errno how to;
		ft_putendl_fd("-csh: cd: No such file or directory", 2);
	}
	else
	{
		free(s_cd.last_path);
		s_cd.tmp_dir = getcwd(NULL, 0);
		if (ft_strcmp(s_cd.tmp_dir, work_dir) != 0)
			s_cd.last_path = s_cd.tmp_dir;
		else
		{
			free(s_cd.tmp_dir);
		}
		//TODO s_cd.last_path = current path;
	}
	free((void *)work_dir);
	return ;
}
