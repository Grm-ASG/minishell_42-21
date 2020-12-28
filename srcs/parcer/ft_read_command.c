/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:17:54 by imedgar           #+#    #+#             */
/*   Updated: 2020/12/28 13:05:58 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_signal		my_signal;
void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int		is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int		ft_ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
				&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

int		quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int		last_valid_arg(t_sign *sign)
{
	t_sign	*prev;

	if (!sign || is_type(sign, CMD) || is_type(sign, ARG))
	{
		prev = prev_sep(sign, NOSKIP);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

int		check_line(t_cmd *cmd, t_sign *sign)
{
	while (sign)
	{
		if (is_types(sign, "TAI")
		&& (!sign->next || is_types(sign->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected sign `", STDERR);
			sign->next ? ft_putstr_fd(sign->next->str, STDERR) : 0;
			sign->next ? 0 : ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			cmd->res = 258;
			return (0);
		}
		if (is_types(sign, "PE")
		&& (!sign->prev || !sign->next || is_types(sign->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected sign `", STDERR);
			ft_putstr_fd(sign->str, STDERR);
			ft_putendl_fd("'", STDERR);
			cmd->res = 258;
			return (0);
		}
		sign = sign->next;
	}
	return (1);
}
char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	free(line);
	return (new);
}

int		quote_check(t_cmd *cmd, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("cmdshell: syntax error with open quotes", STDERR);
		free(*line);
		cmd->res = 2;
		cmd->start = NULL;
		return (1);
	}
	return (0);
}

void	ft_read_command(t_shell *s_shell)
{
	char	*line;
	t_sign	*sign;

	//signal(SIGINT, &sig_int);
	//signal(SIGQUIT, &sig_quit);
	if (get_next_line(0, &line) == -2 && (s_shell->s_cmd.exit = 1))
		ft_putendl_fd("exit", STDERR);
	s_shell->s_cmd.res = (my_signal.sigcode == 1) ? my_signal.status : s_shell->s_cmd.res;
	if (quote_check(&s_shell->s_cmd, &line))
		return ;
	line = space_line(line);
	s_shell->s_cmd.start = get_signs(line);
	free(line);
	get_args(&s_shell->s_cmd);
	sign = s_shell->s_cmd.start;
	while (sign)
	{
		if (is_type(sign, ARG))
			type_arg(sign, 0);
		sign = sign->next;
	}
}
