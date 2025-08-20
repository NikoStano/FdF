/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:55:05 by nistanoj          #+#    #+#             */
/*   Updated: 2025/08/20 12:43:08 by nistanoj         ###   ########.fr       */
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

void	draw_line(t_image img)
{	
	img.dx = ft_abs(img.x1 - img.x0);
	img.sx = check_pos_point(img.x0, img.x1);
	img.dy = -ft_abs(img.y1 - img.y0);
	img.sy = check_pos_point(img.y0, img.y1);
	img.err = img.dx + img.dy;
	while (1)
	{
		draw_img(&img);
		if (img.x0 == img.x1 && img.y0 == img.y1)
			break ;
		img.e2 = 2 * img.err;
		if (img.e2 >= img.dy)
		{
			img.err += img.dy;
			img.x0 += img.sx;
		}
		if (img.e2 <= img.dx)
		{
			img.err += img.dx;
			img.y0 += img.sy;
		}
	}
}
