#include "parser.h"

t_signal	gs_signal;

void	sig_code(void)
{
	if (gs_signal.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		gs_signal.status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		gs_signal.status = 130;
	}
	gs_signal.sigcode = 1;
}

void	sig_res(void)
{
	if (gs_signal.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		gs_signal.status = 131;
		gs_signal.sigres = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}
