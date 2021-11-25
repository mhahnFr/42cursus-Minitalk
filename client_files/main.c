#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "ft_printf.h"

char	*g_string;

void	receive_answer(int sig, siginfo_t *info, void *context)
{
	static size_t	i = 0;
	static int		bi = 7;
	static int		s_pid = -1;

	sig = 0;
	context = NULL;
	if (s_pid != info->si_pid && s_pid == -1)
		s_pid = info->si_pid;
	if (bi == -1)
	{
		bi = 7;
		i++;
	}
	if (g_string[i] == '\0')
		exit(0);
	if (((g_string[i] >> bi--) & 1) != 1)
		kill(s_pid, SIGUSR1);
	else
		kill(s_pid, SIGUSR2);
}

int	main(int argv, char **argc)
{
	struct sigaction	sa;
	siginfo_t			info;
	int					pid;

	if (argv != 3)
	{
		ft_printf("Usage: %s <PID> <data>\n", *argc);
		return (1);
	}
	pid = atoi(argc[1]);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = receive_answer;
	sigaction(SIGUSR1, &sa, NULL);
	g_string = argc[2];
	info.si_pid = pid;
	receive_answer(0, &info, NULL);
	while (1)
		pause();
	return (0);
}
