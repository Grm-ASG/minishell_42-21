/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:20:30 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 13:20:44 by imedgar          ###   ########.fr       */
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