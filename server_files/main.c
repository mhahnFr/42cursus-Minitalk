#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "ft_printf.h"

size_t	g_bits;
char	g_c;

void	receive_zero(int sig, siginfo_t *info, void *context)
{
	sig = 0;
	context = NULL;
	g_c <<= 1;
	g_bits++;
	if (g_bits == 8)
	{
		g_bits = 0;
		write(1, &g_c, 1);
	}
	kill(info->si_pid, SIGUSR1);
}

void	receive_one(int sig, siginfo_t *info, void *context)
{
	context = NULL;
	sig = 0;
	g_c <<= 1;
	g_c ^= 1;
	g_bits++;
	if (g_bits == 8)
	{
		g_bits = 0;
		write(1, &g_c, 1);
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa_first;
	struct sigaction	sa_one;

	ft_printf("%d\n", getpid());
	sa_first.sa_flags = SA_SIGINFO;
	sa_first.sa_sigaction = receive_zero;
	sigaction(SIGUSR1, &sa_first, NULL);
	sa_one.sa_flags = SA_SIGINFO;
	sa_one.sa_sigaction = receive_one;
	sigaction(SIGUSR2, &sa_one, NULL);
	while (1)
		pause();
	return (0);
}
