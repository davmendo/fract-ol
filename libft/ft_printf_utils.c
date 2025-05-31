#include "ft_printf.h"

int	ft_putchar(int c)
{
	char	ch;

	ch = (char)c;
	return (write (1, &ch, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (ft_putstr("(null)"));
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_putptr(void *ptr)
{
	int	printed;

	if (ptr == NULL)
	{
		return (ft_putstr("(nil)"));
	}
	printed = ft_putstr("0x");
	printed += ft_puthex((unsigned long)ptr, 'x');
	return (printed);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	printed;

	printed = 0;
	if (n > 9)
		printed += ft_putnbr_unsigned(n / 10);
	printed += ft_putchar((n % 10) + '0');
	return (printed);
}

int	ft_putnbr(int n)
{
	int		printed;
	char	c;

	printed = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		printed += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		printed += ft_putnbr(n / 10);
	c = (n % 10) + '0';
	printed += ft_putchar(c);
	return (printed);
}
