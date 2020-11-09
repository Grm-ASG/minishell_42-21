/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:13:29 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 21:41:08 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_error(int err)
{
	ft_putstr_fd("Error: ", 2);
	if (err == ALLOCATION_FAILED)
		ft_putstr_fd("Allocation failed\n", 2);
	else if (err == GNL_ERR_RETURN)
		ft_putstr_fd("Error while reading with GNL\n", 2);
	exit(err);
}
