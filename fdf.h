/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:37:58 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/02 16:17:54 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#   define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "./includes/libft.h"
# include "./includes/get_next_line.h"
# include "./includes/ft_printf.h"
# include "./includes/mlx.h"

typedef struct s_map
{
    int height;
    int width;
    int ***array;
    int z_max;
    int z_min;
}           t_map;

void	ft_check_valid(char *filename, t_map *map);

#endif
