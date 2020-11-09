/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:13:29 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 09:19:13 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_error(int err)
{
	ft_putstr_fd("Error: ", 2);
	if (err == ALLOCATION_FAILED)
	{
		/*
		** some code
		*/
		ft_putstr_fd("Allocation failed\n", 2);
	}
	exit (err);
}