/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:27:16 by nistanoj          #+#    #+#             */
/*   Updated: 2025/04/28 17:29:01 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	nb;

	nb = 0;
	if (n == INT_MIN)
	{
		nb += ft_putstr("-2147483648");
		return (nb);
	}
	if (n < 0)
	{
		nb += ft_putchar('-');
		n = -n;
	}
	if (n / 10)
	{
		nb += ft_putnbr(n / 10);
		nb += ft_putchar((n % 10) + 48);
	}
	else
		nb += ft_putchar(n + 48);
	return (nb);
}

int	ft_putnbr_u(unsigned int n)
{
	int	nb;

	nb = 0;
	if (n / 10)
	{
		nb += ft_putnbr(n / 10);
		nb += ft_putchar((n % 10) + 48);
	}
	else
		nb += ft_putchar(n + 48);
	return (nb);
}
