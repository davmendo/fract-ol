/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmendo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:01:35 by davmendo          #+#    #+#             */
/*   Updated: 2024/11/22 22:13:34 by davmendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long long n, char format)
{
	int		printed;
	char	*base;

	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	printed = 0;
	if (n >= 16)
		printed = printed + ft_puthex(n / 16, format);
	printed = printed + ft_putchar(base[n % 16]);
	return (printed);
}

static int	handle_format(char format, va_list args)
{
	int	printed;

	printed = 0;
	if (format == 'c')
		printed += ft_putchar(va_arg(args, int));
	else if (format == 's')
		printed += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		printed += ft_putptr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		printed += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		printed += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		printed += ft_puthex(va_arg(args, unsigned int), format);
	else if (format == '%')
		printed += ft_putchar('%');
	return (printed);
}

static int	is_especifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed;
	int		i;

	va_start(args, format);
	printed = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && is_especifier(format[i + 1]))
		{
			i++;
			printed += handle_format(format[i], args);
		}
		else
			printed += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (printed);
}
