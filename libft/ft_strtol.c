/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:39:57 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 17:18:55 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_digit(char c, int base)
{
	int	digit;

	if (c >= '0' && c <= '9')
		digit = c - '0';
	else if (c >= 'a' && c <= 'z')
		digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		digit = c - 'A' + 10;
	else
		return (-1);
	if (digit >= base)
		return (-1);
	return (digit);
}

static const char	*skip_prefix(const char *ptr, int base, int *sign)
{
	while (ft_isspace((unsigned char)*ptr))
		ptr++;
	*sign = 1;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			*sign = -1;
		ptr++;
	}
	if (base == 16 && ptr[0] == '0' && (ptr[1] == 'x' || ptr[1] == 'X'))
		ptr += 2;
	return (ptr);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	long		result;
	int			sign;
	const char	*ptr;
	int			digit;

	ptr = skip_prefix(nptr, base, &sign);
	result = 0;
	while (*ptr)
	{
		digit = is_valid_digit(*ptr, base);
		if (digit < 0)
			break ;
		result = result * base + digit;
		ptr++;
	}
	if (endptr)
		*endptr = (char *)ptr;
	return (result * sign);
}
