/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:24:18 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/08 20:13:56 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	TODO Delete stdio.h
*/
#include <stdio.h>

int		main(int argc, char *argv[], char *env[])
{
	int i;

	i = -1;
	if (argc || argv || env)
	{
		while (env[++i])
			printf("%s\n", env[i]);
	}
	return (0);
}
