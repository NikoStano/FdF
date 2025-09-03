/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nistanoj <nistanoj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 20:24:08 by nistanoj          #+#    #+#             */
/*   Updated: 2025/09/03 16:03:41 by nistanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static int	parse_token(const char *tok, int *z, int *col)
{
	char	*end;
	long	vz;
	long	vc;
	char	*q;
	int		count;

	errno = 0;
	vz = ft_strtol(tok, &end, 10);
	if (end == tok || errno == ERANGE || vz < INT_MIN || vz > INT_MAX)
		return (1);
	*z = (int)vz;
	*col = -1;
	count = 0;
	if (*end == ',')
	{
		q = end + 1;
		errno = 0;
		vc = ft_strtol(q, &end, 16);
		if (errno == ERANGE || vc < 0 || vc > WHITE)
			return (1);
		count++;
		*col = (int)vc;
	}
	return (0);
}

int	parse_line_into(int *dst_z, int *dst_c, char *line, int cols)
{
	int		i;
	int		ntok;
	char	**sp;

	sp = ft_split(line, ' ');
	if (!sp)
		return (1);
	ntok = 0;
	while (sp[ntok])
		ntok++;
	if (ntok != cols)
	{
		ft_split_free(sp);
		return (1);
	}
	i = 0;
	while (i <= cols && sp[i])
	{
		if (parse_token(sp[i], &dst_z[i], &dst_c[i]))
			return (ft_split_free(sp), 1);
		i++;
	}
	ft_split_free(sp);
	return (0);
}
