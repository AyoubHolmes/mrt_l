#include "miniRT.h"

void	ft_putchar_fd(char c, int fd)
{
	int b;

	b = c;
	write(fd, &b, 1);
}
