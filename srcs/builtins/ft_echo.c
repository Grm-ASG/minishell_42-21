/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:39:34 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/24 00:48:32 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	const char	fl_n = !strcmp(argv[1], "-n");
	int			i;

	i = 0;
	if (fl_n)
		++i;
	while (argv[++i])
		if (!strcmp(argv[i], "$?"))
			ft_dprintf(1, "%d", errno);
		else
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1])
				ft_putchar_fd(' ', 1);
		}
	if (!fl_n)
		ft_putstr_fd("\n", 1);
}
