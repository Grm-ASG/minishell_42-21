#include "parser.h"

void	sig_code(void)
{
	if (my_signal.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		my_signal.status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		my_signal.status = 130;
	}
	my_signal.sigcode = 1;
}

void	sig_res(void)
{
	if (my_signal.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		my_signal.status = 131;
		my_signal.sigres = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}

void	sig_start(void)
{
	my_signal.sigcode = 0;
	my_signal.sigres = 0;
	my_signal.status = 0;
	my_signal.pid = 0;
}
