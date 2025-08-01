/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:56:31 by nistanoj          #+#    #+#             */
/*   Updated: 2025/05/17 05:39:19 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_hex(unsigned int hex, char c)
{
	unsigned int	ret;

	ret = 0;
	if (hex >= 16)
	{
		ret += ft_print_hex(hex >> 4, c);
		ret += ft_print_hex(hex & 0xf, c);
	}
	else
	{
		if (c == 'x')
			ret += ft_putchar("0123456789abcdef"[hex]);
		else
			ret += ft_putchar("0123456789ABCDEF"[hex]);
	}
	return (ret);
}

int	ft_print_hex(unsigned int hex, char c)
{
	int	ret;

	ret = 0;
	if (hex < 10)
		ret += ft_putchar(hex + 48);
	else
		ret += ft_convert_hex(hex, c);
	return (ret);
}
