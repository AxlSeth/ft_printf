/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:38:30 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/26 22:59:44 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_putaddr(unsigned long long int address)
{
	size_t		count;
	char		to_print;
	const char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (address >= 16)
	{
		count += ft_putaddr((address / 16));
		to_print = base[address % 16];
		write(1, &to_print, 1);
		count++;
	}
	else
	{
		to_print = base[address];
		write(1, &to_print, 1);
		count++;
	}
	return (count);
}

static size_t	handle_string(char *s)
{
	size_t	count;

	count = 0;
	if (s == NULL)
		count += ft_putstr("(null)");
	else
		count += ft_putstr(s);
	return (count);
}

static size_t	handle_addr(void *p)
{
	size_t	count;

	count = 0;
	if (p == NULL)
		count += ft_putstr("(nil)");
	else
	{
		ft_putstr("0x");
		count += ft_putaddr((unsigned long long int)p) + 2;
	}
	return (count);
}

static size_t	handle_format(char c, va_list ap)
{
	size_t	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar((char)va_arg(ap, int));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(ap, int), 10, "0123456789");
	else if (c == 's')
		count += handle_string(va_arg(ap, char *));
	else if (c == 'x')
		count += ft_putnbr(va_arg(ap, unsigned int), 16, "0123456789abcdef");
	else if (c == 'X')
		count += ft_putnbr(va_arg(ap, unsigned int), 16, "0123456789ABCDEF");
	else if (c == 'u')
		count += ft_putnbr(va_arg(ap, unsigned int), 10, "0123456789");
	else if (c == 'p')
		count += handle_addr(va_arg(ap, void *));
	else if (c == '%')
		count += ft_putchar('%');
	else
		count += ft_putchar(c);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	size_t	count;
	size_t	i;
	va_list	ap;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] != '%')
			count += ft_putchar(str[i]);
		if (str[i] == '%')
		{
			i++;
			count += handle_format(str[i], ap);
		}
		i++;
	}
	va_end(ap);
	return (count);
}
