#include <unistd.h>
#include <signal.h>

#include "ft_printf.h"

int	other_pid;

void	receive_zero()
{
	write(1, "0", 1);

//	kill(other_pid, SIGUSR1);
}

void	receive_one()
{
	write(1, "1", 1);
//	kill(other_pid, SIGUSR1);
}

void	print_it()
{
	ft_printf("%d\n", other_pid);
}

int	main(void)
{
	other_pid = 1;
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, receive_zero);
	signal(SIGUSR2, receive_one);
	signal(SIGKILL, print_it);
	signal(SIGTERM, print_it);
	while (1);
	return (0);
}
