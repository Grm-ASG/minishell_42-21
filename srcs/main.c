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
	s_shell->do_not_clear = sizeof(s_shell->do_not_clear) + sizeof(s_shell->fl_work) + \
							sizeof(s_shell->exit_status) + sizeof(s_shell->envp) + \
							sizeof(s_shell->s_cd.home_dir_init);
	s_shell->s_cd.home_dir_init = ft_get_env_value(s_shell->envp, "HOME");
	
}

int			main(int argc, char *argv[], char *envp[])
{
	t_shell		s_shell;


	//заготовка для моей структуры
	t_cmd	cmd;
	cmd.exit = 0;
	cmd.res = 0;
	//

	ft_pre_req(argc, argv, envp, &s_shell);
	while (!s_shell.fl_work)
	{
		ft_type_promt(s_shell.envp);

		//по задумке тут должен был быть цикл, но т.к. вложен - то пусть ветвление будет
		if (cmd.exit == 0)
		{
			//попробовал начать обрабатывать сигналы
			sig_start();
			//используя твою структуру должно быть так - ft_read_command(&s_shell); но я делал через свою
			//ft_read_command(&cmd);
			ft_read_command(&s_shell); 
		}
		//извини, но дальше ничего не менял

		ft_execute_command(&s_shell);
		ft_bzero(&s_shell.fd, sizeof(t_shell) - s_shell.do_not_clear);
	}
	return (s_shell.exit_status);
}
