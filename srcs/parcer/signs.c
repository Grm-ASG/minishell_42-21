#include "parser.h"

t_sign	*next_sep(t_sign *sign, int skip)
{
	if (sign && skip)
		sign = sign->next;
	while (sign && sign->type < TRUNC)
		sign = sign->next;
	return (sign);
}

t_sign	*prev_sep(t_sign *sign, int skip)
{
	if (sign && skip)
		sign = sign->prev;
	while (sign && sign->type < TRUNC)
		sign = sign->prev;
	return (sign);
}

t_sign	*next_run(t_sign *sign, int skip)
{
	if (sign && skip)
		sign = sign->next;
	while (sign && sign->type != CMD)
	{
		sign = sign->next;
		if (sign && sign->type == CMD && sign->prev == NULL)
			;
		else if (sign && sign->type == CMD && sign->prev->type < END)
			sign = sign->next;
	}
	return (sign);
}

int		is_type(t_sign *sign, int type)
{
	if (sign && sign->type == type)
		return (1);
	else
		return (0);
}

int		is_types(t_sign *sign, char *types)
{
	if (ft_strchr(types, ' ') && is_type(sign, EMPTY))
		return (1);
	else if (ft_strchr(types, 'X') && is_type(sign, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && is_type(sign, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && is_type(sign, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && is_type(sign, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && is_type(sign, INPUT))
		return (1);
	else if (ft_strchr(types, 'P') && is_type(sign, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && is_type(sign, END))
		return (1);
	return (0);
}

int		has_type(t_sign *sign, int type)
{
	while (sign)
	{
		if (is_type(sign, type))
			return (1);
		sign = sign->next;
	}
	return (0);
}

int		has_pipe(t_sign *sign)
{
	while (sign && is_type(sign, END) == 0)
	{
		if (is_type(sign, PIPE))
			return (1);
		sign = sign->next;
	}
	return (0);
}

t_sign	*next_type(t_sign *sign, int type, int skip)
{
	if (sign && skip)
		sign = sign->next;
	while (sign && sign->type != type)
		sign = sign->next;
	return (sign);
}

void	type_arg(t_sign *sign, int sep)
{
	if (ft_strcmp(sign->str, "") == 0)
		sign->type = EMPTY;
	else if (ft_strcmp(sign->str, ">") == 0 && sep == 0)
		sign->type = TRUNC;
	else if (ft_strcmp(sign->str, ">>") == 0 && sep == 0)
		sign->type = APPEND;
	else if (ft_strcmp(sign->str, "<") == 0 && sep == 0)
		sign->type = INPUT;
	else if (ft_strcmp(sign->str, "|") == 0 && sep == 0)
		sign->type = PIPE;
	else if (ft_strcmp(sign->str, ";") == 0 && sep == 0)
		sign->type = END;
	else if (sign->prev == NULL || sign->prev->type >= TRUNC)
		sign->type = CMD;
	else
		sign->type = ARG;
}

void	get_args(t_cmd *cmd)
{
	t_sign	*sign;
	t_sign	*prev;

	sign = cmd->start;
	while (sign)
	{
		prev = prev_sep(sign, NOSKIP);
		if (is_type(sign, ARG) && is_types(prev, "TAI"))
		{
			while (last_valid_arg(prev) == 0)
				prev = prev->prev;
			sign->prev->next = sign->next;
			if (sign->next)
				sign->next->prev = sign->prev;
			sign->prev = prev;
			sign->next = (prev) ? prev->next : cmd->start;
			prev = (prev) ? prev : sign;
			prev->next->prev = sign;
			prev->next = (cmd->start->prev) ? prev->next : sign;
			cmd->start = (cmd->start->prev) ? cmd->start->prev : cmd->start;
		}
		sign = sign->next;
	}
}

int		next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

t_sign	*next_sign(char *line, int *i)
{
	t_sign	*sign;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	if (!(sign = malloc(sizeof(t_sign)))
	|| !(sign->str = malloc(sizeof(char) * next_alloc(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			sign->str[j++] = line[(*i)++];
		else
			sign->str[j++] = line[(*i)++];
	}
	sign->str[j] = '\0';
	return (sign);
}

t_sign	*get_signs(char *line)
{
	t_sign	*prev;
	t_sign	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ft_ignore_sep(line, i);
		next = next_sign(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
