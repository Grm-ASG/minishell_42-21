#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

typedef struct	s_sign
{
	char			*str;
	int				type;
	struct s_sign	*prev;
	struct s_sign	*next;
}				t_sign;

typedef struct	s_cmd
{
	t_sign			*start;
	int				end;
	int				res;
	int				exit;
	int				no_exec;
	int				fl_redir;
	int				fd_stderr;
	int				fd_stdout;
	int				fd_stdin;
}				t_cmd;

typedef struct	s_signal
{
	int				sigcode;
	int				sigres;
	int				status;
	pid_t			pid;
}				t_signal;

int				ft_ignore_sep(char *line, int i);
void			read_line(t_cmd *cmd);
t_sign			*get_signs(char *line);
void			get_args(t_cmd *cmd);
int				last_valid_arg(t_sign *sign);
int				quotes(char *line, int index);
void			type_arg(t_sign *sign, int separator);
int				is_sep(char *line, int i);
int				ignore_sep(char *line, int i);
void			ft_skip_space(const char *str, int *i);
int				check_line(t_cmd *cmd, t_sign *sign);
void			free_sign(t_sign *start);
t_sign			*next_sep(t_sign *sign, int skip);
t_sign			*prev_sep(t_sign *sign, int skip);
t_sign			*next_run(t_sign *sign, int skip);
int				is_type(t_sign *sign, int type);
int				is_types(t_sign *sign, char *types);
int				has_type(t_sign *sign, int type);
int				has_pipe(t_sign *sign);
t_sign			*next_type(t_sign *sign, int type, int skip);
void			sig_code(void);
void			sig_res(void);
void			sig_start(void);

extern t_signal		gs_signal;
#endif