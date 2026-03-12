/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:17:01 by seramaro          #+#    #+#             */
/*   Updated: 2026/02/16 20:02:23 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr(long long int n, long long int base, char *bbbase)
{
	long long int	nbr;
	long long int	count;

	nbr = n;
	count = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = nbr * (-1);
		count++;
	}
	if (nbr >= base)
	{
		count += ft_putnbr(nbr / base, base, bbbase);
		write(1, &(bbbase[nbr % base]), 1);
		count++;
	}
	if (nbr < base)
	{
		write(1, &(bbbase[nbr]), 1);
		count++;
	}
	return (count);
}
