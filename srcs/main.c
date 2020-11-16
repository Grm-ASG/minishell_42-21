/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:24:18 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 15:36:34 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_type_promt(char *envp[])
{
	char	*user;

	user = ft_get_env_value(envp, "USERNAME");
	if (!user)
		user = ft_strdup("user");
	if (!user)
		ft_error(ALLOCATION_FAILED);
	ft_putstr_fd(user, 1);
	ft_putstr_fd("@MyOwnShell$ ", 1);
	free(user);
}

static void	ft_pre_req(int ac, char *gv[], t_shell *s_shell)
{
	(void)ac;
	(void)gv;
	ft_bzero(s_shell, sizeof(t_shell));
}

int			main(int argc, char *argv[], char *envp[])
{
	t_shell		s_shell;

	ft_pre_req(argc, argv, &s_shell);
	while (1)
	{
		ft_type_promt(envp);
		ft_read_command(&s_shell);
		ft_execute_command(&s_shell);
	}
	return (0);
}
