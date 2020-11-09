/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:24:18 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 20:08:15 by imedgar          ###   ########.fr       */
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

void	ft_read_command(void)
{
	char	buf[2];
	int		ret;

	while (1)
	{
		if ((ret = read(0, buf, 1)) < 0)
			break ;
		buf[1] = '\0';
		if (buf[0] == 10)
			break ;
		ft_putstr_fd(buf, 1);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	if (argc || argv || envp)
	{
		ft_pwd(1);
		ft_env(1, envp);
	}
	while (1)
	{
		ft_type_promt(envp);
		ft_read_command();
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
