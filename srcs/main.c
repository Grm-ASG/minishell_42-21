/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:24:18 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 21:46:42 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(char *envp[], char *var)
{
	const char	*env_var = ft_strjoin(var, "=");
	const int	len = ft_strlen(var) + 1;
	char		*ret;
	int			i;

	if (!env_var)
		ft_error(ALLOCATION_FAILED);
	i = -1;
	ret = NULL;
	while (envp[++i])
		if (ft_strnstr(envp[i], env_var, len))
		{
			if (!(ret = ft_strdup(&envp[i][len])))
				ft_error(ALLOCATION_FAILED);
			break ;
		}
	free((void *)env_var);
	return (ret);
}

void	ft_type_promt(char *envp[])
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

void	ft_read_command(t_shell *s_shell)
{
	int		ret;

	ret = get_next_line(0, &s_shell->cmd_line);
	if (ret < 0)
		ft_error(GNL_ERR_RETURN);
	s_shell->fd = 1;
}

void	ft_execute_command(t_shell *s_shell)
{
	char *const	cmd = s_shell->cmd_line;
	int const	fd = s_shell->fd;

	if (ft_strnstr("pwd", cmd, 3))
		ft_pwd(fd);
	else
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd("\n", fd);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	t_shell		s_shell;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_bzero(&s_shell, sizeof(t_shell));
	while (1)
	{
		free(s_shell.cmd_line);
		ft_bzero(&s_shell, sizeof(t_shell));
		ft_type_promt(envp);
		ft_read_command(&s_shell);
		ft_execute_command(&s_shell);
	}
	return (0);
}
