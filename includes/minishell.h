/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:25:46 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/08 20:09:48 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** "malloc"/"free"/"exit"
*/
# include <stdlib.h>

/*
** "write"/"read"/"close"/"fork"/"exit"/"getcwd"/"chdir"/
** "stat"/"lstat"/"fstat"/"execve"/"dup"/"dup2"/"pipe"/
*/
# include <unistd.h>

/*
** "open"/"fork"/"wait"/"waitpid"/"wait3"/"wait4"/"kill"/
** "stat"/"lstat"/"fstat"/"opendir"/"closedir"
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** "wait"/"waitpid"/"wait3"/"wait4"
*/
# include <sys/wait.h>

/*
** "wait3"/"wait4"
*/
# include <sys/time.h>
# include <sys/resource.h>

/*
** "signal"/"kill"
*/
# include <signal.h>

/*
** "opendir"/"closedir"
*/
# include <dirent.h>

/*
** "strerror"
*/
# include <string.h>

/*
** "errno"
*/
# include <errno.h>

/*
** "readdir" has no include lib, need to read "man 2 readdir"
*/

#endif
