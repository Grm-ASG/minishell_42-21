/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:17:54 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 13:19:46 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_command(t_shell *s_shell)
{
	int		ret;

	ret = get_next_line(0, &s_shell->cmd_line);
	if (ret < 0)
		ft_error(GNL_ERR_RETURN);
	s_shell->fd = 1;
}