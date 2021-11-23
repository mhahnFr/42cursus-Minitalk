#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "ft_printf.h"

int	pid;

void	send_message(int pid, char *mesg)
{
	ft_printf("%d %s\n", pid, mesg);
}

void	send_pid(int pid, int data)
{
	for (size_t i = 0; i < 32; i++) {
		if (((data >> i) & 0xFF) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
	}
}

void	receive_answer()
{
	kill(pid, SIGUSR2);
}

int	main(int argv, char **argc)
{
	int	i;

	if (argv <= 2)
	{
		ft_printf("Usage: %s <PID> <data...>\n", *argc);
		return (1);
	}
	pid = atoi(argc[1]);
	// send pid
	// once server got it, he will send a signal
	// send a bit, send the next bit once signal from server received.
	signal(SIGUSR1, receive_answer);
	send_pid(pid, getpid());
	i = 0;
	while (i < argv - 1)
	{
		send_message(pid, argc[i]);
		i++;
	}
	return (0);
}
