/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:23 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/26 15:20:38 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	main(int ac, char **av)
{
	int		ret;
	t_app	a;

	ret = 0;
	if (ac == 2)
	{
		if (win_init(&a, av[1]))
		{
			ft_printf("Error: failed to load or init map : %s\n", av[1]);
			return (1);
		}
		ret = win_run(&a);
		win_destroy(&a);
		return (ret);
	}
	else
	{
		ft_printf("Usage: %s <mapfile>\n", av[0]);
		return (1);
	}
}
