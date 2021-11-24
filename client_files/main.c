#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "ft_printf.h"

int		g_pid;
char	*g_string;

void	receive_answer(void)
{
	static size_t	i = 0;
	static int		bi = 7;

	if (bi == -1)
	{
		bi = 7;
		i++;
	}
	if (g_string[i] == '\0')
		return ;
	if (((g_string[i] >> bi--) & 1) != 1)
		kill(g_pid, SIGUSR1);
	else
		kill(g_pid, SIGUSR2);
}

void	k(void)
{
	kill(g_pid, SIGTERM);
	exit(0);
}

int	main(int argv, char **argc)
{
	if (argv <= 2)
	{
		ft_printf("Usage: %s <PID> <data...>\n", *argc);
		return (1);
	}
	g_pid = atoi(argc[1]);
	signal(SIGUSR1, receive_answer);
	signal(SIGINT, k);
	g_string = argc[2];
	kill(pid, SIGUSR1);
	while (1)
		pause();
	return (0);
}
