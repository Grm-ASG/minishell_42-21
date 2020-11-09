/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:16:40 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 15:30:18 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**			Our "pwd" takes 1 argument:
**			1) int fd = filedescriptor to write3
**
**			TODO check return value NULL, is it malloc failed?
*/

void		ft_pwd(int fd)
{
	const char	*path_name = getcwd(NULL, 0);
	
	if (!path_name)
	{
		/*
		**	Check EACCES errno flag! (man 3 getcwd)
		*/
		ft_error(ALLOCATION_FAILED);
	}
	ft_putstr_fd((char *)path_name, fd);
	ft_putstr_fd("\n", fd);
	free((char *)path_name);
}