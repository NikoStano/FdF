/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:18:10 by nistanoj          #+#    #+#             */
/*   Updated: 2025/05/17 05:40:47 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	ret;
	int	i;

	if (!s)
		return (ft_putstr("(null)"));
	ret = 0;
	i = 0;
	while (s[i])
	{
		ret += ft_putchar(s[i]);
		i++;
	}
	return (ret);
}
