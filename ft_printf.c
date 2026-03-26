/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:38:30 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/26 11:39:55 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <cstdarg>

int	ft_printf(const char *str, ...)
{
	size_t	count;
	size_t	i;
	va_list	ap;

	va_start(ap, str);
	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] != '%')
			count += ft_putchar(str[i]);
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 'c')
				count += ft_putchar((char)va_arg(ap, int));
			else if (str[i] == 'd' || str[i] == 'i')
				count += ft_putnbr(va_arg(ap, int), 10, "0123456789");
			else if (str[i] == 's')
			{
				if (va_arg(ap, char *) == NULL)
					return (-1);
				count += ft_putstr(va_arg(ap, char *));
			}
			else if (str[i] == 'x')
				count += ft_putnbr(va_arg(ap, int), 16, "0123456789abcdef");
			else if (str[i] == 'X')
				count += ft_putnbr(va_arg(ap, int), 16, "0123456789ABCDEF");
			else if (str[i] == 'u')
				count += ft_putnbr(va_arg(ap, unsigned int), 10, "0123456789");
			else if (str[i] == 'p')
			{
				ft_putstr("0x");
				count += ft_putnbr((long long int)(va_arg(ap, void *)), 16,
					"0123456789abcdef") + 2;
			}
			else if (str[i] == '%')
				count += ft_putchar('%');
			else
				count += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(ap);
	return (count);
}
