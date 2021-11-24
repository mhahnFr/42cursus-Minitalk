#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "ft_printf.h"

int				g_other_pid;
size_t			g_bits = 0;
unsigned char	g_c;

void	receive_zero(void)
{
	g_c <<= 1;
	g_bits++;
	if (g_bits == 8)
	{
		g_bits = 0;
		write(1, &g_c, 1);
	}
	kill(g_other_pid, SIGUSR1);
}

void	receive_one(void)
{
	g_c <<= 1;
	g_c ^= 1;
	g_bits++;
	if (g_bits == 8)
	{
		g_bits = 0;
		write(1, &g_c, 1);
	}
	kill(g_other_pid, SIGUSR1);
}

void	first_responder(int sig, siginfo_t *i, void *context)
{
	g_other_pid = i->si_pid;
	signal(SIGUSR1, receive_zero);
	sig = 0;
	context = NULL;
	kill(g_other_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = first_responder;
	sigaction(SIGUSR1, &sa, NULL);
	signal(SIGUSR2, receive_one);
	while (1)
		pause();
	return (0);
}
