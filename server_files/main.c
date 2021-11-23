#include <unistd.h>

#include "ft_printf.h"

int	main(void)
{
	ft_printf("%d\n", getpid());
	while (1);
	return (0);
}
