#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "ft_printf.h"

int	main(int argv, char **argc)
{
	int	pid;

	if (argv <= 2)
	{
		ft_printf("Usage: %s <PID> <data...>\n", *argc);
		return (1);
	}
	pid = atoi(argc[1]);
	kill(pid, SIGUSR1);
	kill(getpid(), SIGKILL);
	return (0);
}
