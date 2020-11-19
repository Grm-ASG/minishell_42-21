/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:28:58 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/19 21:17:59 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_tilda_change(char **home, char **str_value)
{
	int			len_home;
	char		*find;

	len_home = ft_strlen(*home);
	find = ft_strnstr(*str_value, *home, len_home);
	if (find)
	{
		(*str_value)[0] = '~';
		ft_memmove(&(*str_value)[1], &(*str_value)[len_home], \
					ft_strlen(*str_value) - len_home + 1);
	}
}

void		ft_type_promt(char *envp[])
{
	const int	fd = 1;
	char		*str_value;
	const char	*home = ft_get_env_value(envp, "HOME");

	str_value = ft_get_env_value(envp, "USERNAME");
	if (!str_value)
		str_value = ft_strdup("noname");
	if (!str_value)
		ft_error(ALLOCATION_FAILED);
	ft_dprintf(fd, "%s%s@MyOwnShell%s:", GREEN, str_value, DEFLT);
	free(str_value);
	str_value = ft_get_env_value(envp, "PWD");
	if (home)
		ft_tilda_change((char **)&home, &str_value);
	ft_dprintf(fd, "%s%s%s$ ", BLUE, str_value, DEFLT);
	ft_free_all(2, &str_value, &home);
}
