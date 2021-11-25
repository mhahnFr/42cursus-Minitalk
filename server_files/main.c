#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "ft_printf.h"

#include "main.h"

struct s_char_bits	g_ship = {
	.bits = 0,
	.c = 0
};

void	check_pid(int pid)
{
	static int	s_pid = -1;

	if (s_pid != pid)
	{
		g_ship.bits = 0;
		s_pid = pid;
		ft_printf("\n\nIncoming message from %d:\n", pid);
	}
}

void	receive_zero(int sig, siginfo_t *info, void *context)
{
	check_pid(info->si_pid);
	sig = 0;
	context = NULL;
	g_ship.c <<= 1;
	g_ship.bits++;
	if (g_ship.bits == 8)
	{
		g_ship.bits = 0;
		write(1, &g_ship.c, 1);
	}
	kill(info->si_pid, SIGUSR1);
}

void	receive_one(int sig, siginfo_t *info, void *context)
{
	check_pid(info->si_pid);
	context = NULL;
	sig = 0;
	g_ship.c <<= 1;
	g_ship.c ^= 1;
	g_ship.bits++;
	if (g_ship.bits == 8)
	{
		g_ship.bits = 0;
		write(1, &g_ship.c, 1);
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
