/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:56:11 by nistanoj          #+#    #+#             */
/*   Updated: 2025/05/17 16:04:08 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert(size_t ptr)
{
	int	ret;

	ret = 0;
	if (ptr >= 16)
		ret += ft_convert(ptr >> 4);
	ret += ft_putchar("0123456789abcdef"[ptr & 0xf]);
	return (ret);
}

int	ft_print_ptr(void *ptr)
{
	int	ret;

	if (!ptr)
		return (ft_putstr("(nil)"));
	ret = 0;
	ret += ft_putstr("0x");
	ret += ft_convert((size_t)ptr);
	return (ret);
}
