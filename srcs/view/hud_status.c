/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:00:00 by nistanoj          #+#    #+#             */
/*   Updated: 2025/10/27 08:17:30 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	draw_keys_status(t_app *a)
{
	int	start_y;

	start_y = HEIGHT - 350;
	draw_movement_keys(a, 10, start_y);
	draw_rotation_keys(a, 120, start_y);
	draw_zoom_keys(a, 250, start_y);
}
