/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:18:10 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/04 17:10:58 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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
