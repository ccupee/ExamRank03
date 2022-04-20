#include <unistd.h>
#include <stdarg.h>

#include <stdio.h>

int nbrlen(long nbr, int base_len)
{
    int i = 1;

    while (nbr >= base_len)
    {
        nbr /= base_len;
        i++;
    }
    return (i);
}

void putnbr(long nbr, int base_len, char *base)
{
    if (nbr >= base_len)
        putnbr(nbr/base_len, base_len, base);
    write(1, &base[nbr%base_len], 1);
}

int		ft_printf(const char *format, ...)
{
    va_list args;
    char *str;
    char *s;
    long nbr;
    int neg;
    int len;
    int length;

    va_start(args, format);
    str = (char *)format;
    length = 0;
    while (*str)
    {
        if (*str == '%')
        {
            str++;
            len = 0;
            neg = 0;
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
                    neg = 1;
                    nbr = -nbr;
                }
                len = nbrlen(nbr, 10) + neg;
                if (neg == 1)
                    write(1, "-", 1);
                putnbr(nbr, 10, "0123456789");
            }
            if (*str == 'x')
            {
                nbr = va_arg(args, unsigned);
                len = nbrlen(nbr, 16);
                putnbr(nbr, 16, "0123456789abcdef");
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
	int a = printf("bhj%s\n", "Hello world!");
	int b = ft_printf("bhj%s\n", "Hello world!");
	int c = printf("dsdh %d\n", 5734687329);
	int d = ft_printf("dsdh %d\n", 5734687329);
    printf("a: %d b: %d\n", a, b);
    printf("c: %d d: %d\n", c, d);
}