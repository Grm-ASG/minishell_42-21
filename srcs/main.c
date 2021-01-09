/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:24:18 by imedgar           #+#    #+#             */
/*   Updated: 2020/12/28 11:23:10 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void		ft_start_end(t_shell *s_shell, char *envp[], int start)
{
	if (start)
	{
		ft_dup_array(envp, &s_shell->envp);
		s_shell->home_dir_init = ft_get_env_value(s_shell->envp, "HOME");
		/*
		s_shell->do_not_clear = sizeof(s_shell->do_not_clear) + \
								sizeof(s_shell->exit_status) + sizeof(s_shell->envp) + \
								sizeof(s_shell->s_cd.home_dir_init);
		*/
	}
	else
	{
		//TODO clean up all allocated memory
		ft_free_array(&s_shell->envp);
		free(s_shell->home_dir_init);
	}
}

int			main(int argc, char *argv[], char *envp[])
{
	t_shell		s_shell;

	(void)argc;
	(void)argv;
	ft_start_end(&s_shell, envp, 1);
	while (!s_shell.s_cmd.exit)
	{
		ft_bzero(&s_shell, sizeof(t_shell) - 24);
		ft_bzero(&gs_signal, sizeof(t_signal));
		ft_type_promt(s_shell.envp);
		ft_read_command(&s_shell); 
		if (!s_shell.s_cmd.res)
			ft_execute_command(&s_shell);
	}
	ft_start_end(&s_shell, envp, 0);
	return (s_shell.exit_status);
}
