/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:55:05 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/12 11:17:28 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int on_destroy(t_fdf *fdf)
{
	// Petit helper pour quitter proprement via ESC ou croix
	(void)fdf;
	exit(0);
	return (0);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	check_pos_point(int x0, int x1)
{
	if (x0 < x1)
		return (1);
	else
		return (-1);
}
