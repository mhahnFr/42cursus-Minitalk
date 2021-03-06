#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "ft_printf.h"

#include "main.h"

/*
 * The ship which contains the count of the bits that have been received since
 * the last complete byte, as well as the character itself.
 */
struct s_char_bits	g_ship = {
	.bits = 0,
	.c = 0
};

/*
 * Checks wether the caller's process identifier has changed. If that is the
 * case, a message indicating the new connection is printed.
 */
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

/*
 * The handler for SIGUSR1. Upon reception of this signal, the bits of the
 * character are shifted by one. If the signal is the eighth, the character is
 * printed and the bit count is reset to zero. Once everything is finished, a
 * SIGUSR1 is sent back to the sender.
 */
void	receive_zero(int sig, siginfo_t *info, void *context)
{
	static int	s_pid;

	if (info->si_pid != 0)
		s_pid = info->si_pid;
	check_pid(s_pid);
	(void) context;
	(void) sig;
	g_ship.c <<= 1;
	g_ship.bits++;
	if (g_ship.bits == 8)
	{
		g_ship.bits = 0;
		write(1, &g_ship.c, 1);
	}
	kill(s_pid, SIGUSR1);
}

/*
 * The handler for SIGUSR2. Upon reception of this signal, the bits of the
 * character are shifted by one and are flipped. If the signal is the eighth,
 * the character is printed and the bit count is reset to zero. Once everything
 * is finished, a SIGUSR1 is sent back to the sender.
 */
void	receive_one(int sig, siginfo_t *info, void *context)
{
	static int	s_pid;

	if (info->si_pid != 0)
		s_pid = info->si_pid;
	check_pid(s_pid);
	(void) context;
	(void) sig;
	g_ship.c <<= 1;
	g_ship.c ^= 1;
	g_ship.bits++;
	if (g_ship.bits == 8)
	{
		g_ship.bits = 0;
		write(1, &g_ship.c, 1);
	}
	kill(s_pid, SIGUSR1);
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
