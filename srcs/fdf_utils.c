/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:55:05 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/20 11:58:31 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	return (-1);
}

int	ft_count_words(char *str)
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

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*token;

	if (str)
		next_token = str;
	if (!next_token)
		return (0);
	token = next_token;
	while (*next_token && !ft_strchr(delim, *next_token))
		next_token++;
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;
	return (token);
}

void	draw_map_ctx(t_fdf *fdf)
{
	t_image	img;

	mlx_clear_window(fdf->mlx, fdf->win);
	img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	draw_map_internal(fdf, &img);
	mlx_put_image_to_window(fdf->mlx, fdf->win, img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, img.img);
}
