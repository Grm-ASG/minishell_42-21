/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:24:18 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/18 20:57:32 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_save_envp(char *envp[], t_shell *s_shell)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	if (!(s_shell->envp = (char **)malloc(sizeof(char *) * (i + 1))))
		ft_error(ALLOCATION_FAILED);
	ft_bzero(s_shell->envp, sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		if (!(s_shell->envp[i] = ft_strdup(envp[i])))
		{
			while (--i != 0)
				free(s_shell->envp[i]);
			free(s_shell->envp[i]);
			free(s_shell->envp);
			ft_error(ALLOCATION_FAILED);
		}
		++i;
	}
	s_shell->envp[i] = NULL;
}

static void	ft_pre_req(int argc, char *argv[], \
						char *envp[], t_shell *s_shell)
{
	(void)argc;
	(void)argv;
	ft_bzero(s_shell, sizeof(t_shell));
	ft_save_envp(envp, s_shell);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_shell		s_shell;

	ft_pre_req(argc, argv, envp, &s_shell);
	while (1)
	{
		ft_type_promt(s_shell.envp);
		ft_read_command(&s_shell);
		ft_execute_command(&s_shell);
	}
	return (0);
}
