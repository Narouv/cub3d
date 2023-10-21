/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:55:53 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 19:31:12 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_con(char *r, char *g, char *b)
{
	int	red;
	int	gre;
	int	blu;
	int	hex;

	red = ft_atoi(r);
	gre = ft_atoi(g);
	blu = ft_atoi(b);
	if (red > 255 || gre > 255 || blu > 255)
		return (1);
	hex = (red << 24) | (gre << 16) | (blu << 8) | 0xff;
	return (hex);
}

int	check_split(char **split)
{
	int	cntr;
	int	cntr2;

	cntr = 0;
	while (split[cntr])
	{
		cntr2 = 0;
		while (split[cntr][cntr2])
		{
			if (!ft_isdigit(split[cntr][cntr2]))
				return (1);
			cntr2++;
		}
		cntr++;
	}
	if (cntr > 3)
		return (1);
	return (0);
}

int	color(char *color_str, int *color, t_map *m)
{
	char	*str;
	char	**split;

	str = ft_strtrim(color_str, "FC \t\n");
	split = ft_split(str, ',');
	if (check_split(split) || !split[0] || !split[1] || !split[2])
	{
		free(str);
		free_string(split);
		ft_printf("invalid color\n");
		return (1);
	}
	*color = rgb_con(split[0], split[1], split[2]);
	free(str);
	free_string(split);
	if (*color == 1)
		return (1);
	m->col_count++;
	return (0);
}

// map util
int	valid_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' )
	{
		return (1);
	}
	return (0);
}

// map util
int	check_map(char *m)
{
	size_t	cntr;

	cntr = 0;
	while (m[cntr])
	{
		if (m[cntr] != ' ' && m[cntr] != '0' && m[cntr] != '1'
			&& m[cntr] != 'N' && m[cntr] != 'S' && m[cntr] != 'W'
			&& m[cntr] != 'E' && m[cntr] != '\n')
			return (1);
		cntr++;
	}
	return (0);
}
