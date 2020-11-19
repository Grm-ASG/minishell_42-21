/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:21:25 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/19 21:06:57 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_cmd(char **cmd)
{
	const char	*tmp = *cmd;
	int			i;
	
	i ^= i;
	while (!ft_isspace((*cmd)[i]) && (*cmd)[i])
		++i;
	if ((*cmd)[i])
			(*cmd)[i++] = '\0';
	*cmd = &(*cmd)[i];
	return ((char *)tmp);
}

void	ft_execute_command(t_shell *s_shell)
{
	char *const	cmd = s_shell->cmd_line;
	int const	fd = s_shell->fd;
	char		*cmd_to_exec;
	int			i;

	if (cmd[0] == '\0')
		return ;
	cmd_to_exec = ft_get_cmd((char **)&cmd);
	if (!(s_shell->argv = ft_split(cmd, ' ')))
		ft_error(ALLOCATION_FAILED);
	if (ft_strnstr(cmd_to_exec, "pwd", 3))
		ft_pwd(fd);
	else if (!ft_strcmp(cmd_to_exec, "cd"))
		ft_cd(s_shell);
	else
	{
		i = -1;
		ft_dprintf(fd, "cmd = %s: \n", cmd_to_exec);
		while (s_shell->argv[++i])
		{
			ft_dprintf(fd, "%dst argv = %s\n", i, s_shell->argv[i]);
		}
	}
	i = -1;
	while (s_shell->argv[++i])
		ft_free_all(1, &s_shell->argv[i]);
	ft_free_all(1, &s_shell->argv[i]);
	ft_free_all(1, &s_shell->cmd_line);
	ft_bzero(&s_shell->fd, sizeof(t_shell) - 8);
}
