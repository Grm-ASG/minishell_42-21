/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 01:35:40 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/24 01:35:56 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char ***array)
{
	int i;

	i = 0;
	while ((*array)[i])
		ft_free_all(1, &(*array)[i++]);
	ft_free_all(1, &(*array));
}

void		ft_dup_array(char *src[], char **dest[])
{
	int i;

	i = 0;
	while (src[i])
		i++;
	if (!((*dest) = (char **)malloc(sizeof(char *) * (i + 1))))
		ft_error(ALLOCATION_FAILED);
	ft_bzero((*dest), sizeof(char *) * (i + 1));
	i = 0;
	while (src[i])
	{
		if (!((*dest)[i] = ft_strdup(src[i])))
		{
			while (--i != 0)
				free((*dest)[i]);
			free((*dest)[i]);
			free(*dest);
			ft_error(ALLOCATION_FAILED);
		}
		++i;
	}
	dest[i] = NULL;
}
