/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:25:46 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/18 22:48:23 by imedgar          ###   ########.fr       */
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

# include <stdarg.h>
# include <X11/keysymdef.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

/*
** Define error codes
*/
# define ALLOCATION_FAILED	1
# define GNL_ERR_RETURN		2
# define FAILED_READ		3

/*
** Color defenition
*/
# define DEFLT	"\033[0m"
# define BLACK	"\033[30m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PURPLE	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"

//DEBUG DELETE
#include <stdio.h>

/*
** For "fl_direction" flag
*/
# define LESS		1 << 0
# define GREAT		1 << 1
# define GREATGREAT	1 << 2
# define FD_STDIN	1 << 3
# define FD_STDOUT	1 << 4
# define FD_STDERR	1 << 5
# define PIPE		1 << 6

/*
** Main structures
*/
typedef struct	s_shell
{
	char		**envp;
	int			fd;
	char		*cmd_line;
	char		**argv;
}				t_shell;

typedef struct	s_cmd
{
	char			*cmd;
	char			**argv;
	unsigned char	fl_redir;
	struct s_cmd	*next;
}				t_cmd;

/*
** Function declaration
*/
void			ft_error(int err);
void			ft_echo(char *str, int fd, char fl_n);
void			ft_pwd(int fd_stdout, int fd_strerr);
void			ft_env(int fd, char *envp[]);
void			ft_read_command(t_shell *s_shell);
char			*ft_get_env_value(char *envp[], char *var);
void			ft_execute_command(t_shell *s_shell);
void			ft_cd(t_shell *s_shell);
void			ft_change_env(char *envp[], char *env_var, char *value);
void			ft_type_promt(char *envp[]);
void			ft_free_all(int num_to_del, ...);

#endif
