/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:15:51 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 18:28:20 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_go_home(t_shell *s_shell, \
					t_cd *s_cd,const char *current_dir)
{
	char	*home_dir;
	int		ret;

	home_dir = ft_get_env_value(s_shell->envp, "HOME");
	if (!home_dir)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("-csh: cd: HOME not set", 2);
		ft_putstr_fd(DEFLT, 2);
		free((void *)current_dir);
		return ;
	}
	ret = chdir(home_dir);
	if (!(ft_strcmp(home_dir, current_dir)))
		ft_change_env(s_shell->envp, "PWD", home_dir);
	free(home_dir);
	free(s_cd->last_path);
	if (!(s_cd->last_path = ft_strdup(current_dir)))	
		ft_error(ALLOCATION_FAILED);
	if (ret == -1)
	{
		//TODO errno how to;
		ft_putendl_fd("-csh: cd: No such file or directory", 2);
	}

}

void		ft_cd(t_shell *s_shell)
{
	static t_cd		s_cd;
	char			fl_last_path;
	const char		*current_dir = getcwd(NULL, 0);
	int				ret;

	if (!current_dir)
		ft_error(ALLOCATION_FAILED);
	if (!s_shell->argv[1])
		ft_go_home(s_shell, &s_cd, current_dir);
	else if (s_shell->argv[2])
		ft_putendl_fd("-csh: cd: too many arguments", 2);
	else
	{		
		fl_last_path = (s_shell->argv[1][0] == '-' && !s_shell->argv[1][1]);
		if (fl_last_path)
		{
			if (!s_cd.last_path)
			{
				free((void *)current_dir);
				ft_putendl_fd("-csh: cd: OLDPWD not set", 2);
				return ;
			}
			else
			{	
				ret = chdir(s_cd.last_path);
				free(s_cd.last_path);
				if (!(s_cd.last_path = ft_strdup(current_dir)))	
					ft_error(ALLOCATION_FAILED);
			}
		}
		else
		{
			ret = chdir(s_shell->argv[1]);
		}
		if (ret == -1)
		{
			//TODO errno how to;
			ft_putendl_fd("-csh: cd: No such file or directory", 2);
		}
		/*
		else
		{
			free(s_cd.last_path);
			s_cd.new_dir = getcwd(NULL, 0);
			if (ft_strcmp(s_cd.new_dir, current_dir) != 0)
				s_cd.last_path = s_cd.new_dir;
			else
			{
				free(s_cd.new_dir);
			}
			TODO s_cd.last_path = current path;
		}*/
	}
	s_cd.new_dir = getcwd(NULL, 0);
	if (ft_strcmp(s_cd.new_dir, current_dir))
		ft_change_env(s_shell->envp, "PWD", s_cd.new_dir);
	free((void *)current_dir);
	free((void *)s_cd.new_dir);
	return ;
}
