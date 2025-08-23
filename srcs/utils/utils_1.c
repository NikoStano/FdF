/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsafe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:34:16 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/21 21:33:34 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	word_count(const char *s)
{
	int	i;
	int	in;
	int	n;

	i = 0;
	in = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != ' ' && !in)
		{
			in = 1;
			n++;
		}
		else if (s[i] == ' ')
			in = 0;
		i++;
	}
	return (n);
}

int	safe_atoi(const char *s, int *out)
{
	long	sign;
	long	n;

	sign = 1;
	n = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		if (n * sign > 2147483647 || n * sign < -2147483648)
			return (1);
		s++;
	}
	*out = (int)(n * sign);
	return (0);
}

void	ft_split_free(char **sp)
{
	int	i;

	i = 0;
	if (!sp)
		return ;
	while (sp[i])
		free(sp[i++]);
	free(sp);
}
