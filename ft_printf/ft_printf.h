/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:07:07 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/09 22:36:41 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
size_t	ft_putstr(char *str);
size_t	ft_putnbr(long long int n, long long int base, char *bbbase);
int		ft_putchar(char c);
#endif
