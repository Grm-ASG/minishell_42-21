/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:20:30 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 21:43:10 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_env(char *envp[], char *var, char *value)
{
	const int	len = ft_strlen(var) + 1;
	const char	*env_var = ft_strjoin(var, "=");
	int			i;

	if (!env_var)
		ft_error(ALLOCATION_FAILED);
	i = 0;
	while (envp[++i])
		if (ft_strnstr(envp[i], env_var, len))
		{
			ft_free_all(1, &envp[i]);
			if (!(envp[i] = ft_strjoin(env_var, value)))
				ft_error(ALLOCATION_FAILED);
			ft_free_all(1, &env_var);
			break ;
		}
}

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
	ft_free_all(1, &env_var);
	return (ret);
}
