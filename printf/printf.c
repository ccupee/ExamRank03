#include <unistd.h>
#include <stdarg.h>

#include <stdio.h>

static int	ft_nbrlen(long n, int base_len)
{
	int	i;

	i = 1;
	while (n >= base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

static void	ft_putnbr(long nbr, int base_len, char *base)
{
	if (nbr >= base_len)
		ft_putnbr(nbr / base_len, base_len, base);
	write(1, &base[nbr % base_len], 1);
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	char	*str;
	char	*s;
	long	nbr;
	int		neg;
	int		len;
	int		length;

	va_start(args, format);
	str = (char *)format;
	length = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			neg = 0;
			len = 0;
			
			if (*str == 's')
			{
				s = va_arg(args, char *);
				if (!s)
					s = "(null)";
				while (s[len])
					len++;
                write(1, s, len);
			}

			if (*str == 'd')
			{
				nbr = va_arg(args, int);
				if (nbr < 0)
				{
					nbr = -nbr;
					neg = 1;
				}
				len = ft_nbrlen(nbr, 10) + neg;
                if (neg == 1)
				    write(1, "-", 1);
                ft_putnbr(nbr, 10, "0123456789");
			}

			if (*str == 'x')
			{
				nbr = va_arg(args, unsigned);
				len = ft_nbrlen(nbr, 16);
                ft_putnbr(nbr, 16, "0123456789abcdef");
			}

			length += len;
		}
		else
			length += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (length);
}

int main()
{
	printf("bhj%s\n", "Hello world!");
	ft_printf("bhj%s\n", "Hello world!");
	printf("bhj  %d\n", 5734687329);
	ft_printf("bhj  %d\n", 5734687329);
}