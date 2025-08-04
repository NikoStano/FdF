/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:54:24 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/04 17:05:16 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_count_words(char *str)
{
	int	count;
	int	check;

	count = 0;
	check = 0;
	while (*str)
	{
		if (*str != ' ' && check == 0)
		{
			count++;
			check = 1;
		}
		else if (*str == ' ')
			check = 0;
		str++;
	}
	return (count);
}
