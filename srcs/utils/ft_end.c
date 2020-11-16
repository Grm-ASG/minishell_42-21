/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:52:06 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/16 21:43:30 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_all(int num_to_del, ...)
{
	va_list		factor;
	void		**ptr;

	va_start(factor, num_to_del);
	while (num_to_del-- != 0)
	{
		ptr = (void **)va_arg(factor, void **);
		free(*ptr);
		*ptr = NULL;
	}
	va_end(factor);
}
