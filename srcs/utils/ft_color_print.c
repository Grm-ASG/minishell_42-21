/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:28:58 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/20 19:59:33 by imedgar          ###   ########.fr       */
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
	const int	fd_stdout = 1;
	const char	*promt_line = "@MyOwnShell";
	const char	*username = ft_get_env_value(envp, "USER");
	const char	*pwd_val = getcwd(NULL, 0);
	const char	*home_dir = ft_get_env_value(envp, "HOME");

	if (!username && !(username = ft_strdup("noname")))
		ft_error(ALLOCATION_FAILED);
	ft_dprintf(fd_stdout, "%s%s%s%s:", GREEN, username, promt_line, DEFLT);
	if (pwd_val && home_dir)
	{
		ft_tilda_change((char **)&home_dir, (char **)&pwd_val);
		ft_dprintf(fd_stdout, "%s%s%s$ ", BLUE, pwd_val, DEFLT);
	}
	else
		ft_dprintf(fd_stdout, "%s.%s$ ", BLUE, DEFLT);
	ft_free_all(3, &username, &home_dir, &pwd_val);
}
