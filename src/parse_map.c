/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:55:53 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 16:59:00 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	space_check(char **s, t_map *m, size_t i, size_t j)
{
	if (i && j && valid_char(s[i][j]))
	{
		if (j < ft_strlen(s[i]) && (s[i][j + 1] == ' '
			|| s[i][j - 1] == ' '))
			return (1);
		if (i < m->height - 1 && (s[i + 1][j] == ' ' || s[i - 1][j] == ' '))
			return (1);
	}
	return (0);
}

int	check_bounds(char **s, t_map *m)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			if (!i && (s[i][j] != '1' && s[i][j] != ' '))
				return (1);
			else if (i == m->height - 1 && (s[i][j] != '1' && s[i][j] != ' '))
				return (1);
			else if (!j && (s[i][j] != '1' && s[i][j] != ' '))
				return (1);
			else if (!s[i][j] && ft_strlen(s[i]) > j && s[i][j - 1] != '1')
				return (1);
			else if (space_check(s, m, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	**get_dimensions(t_map *m)
{
	char	**split;
	size_t	cntr;
	size_t	wide;

	cntr = 0;
	split = ft_split(m->whole_map, '\n');
	while (split[cntr])
	{
		wide = ft_strlen(split[cntr]);
		if (wide > m->width)
			m->width = wide;
		cntr++;
	}
	m->height = cntr;
	m->dir = ft_calloc(m->height, sizeof(char *));
	cntr = 0;
	while (cntr < m->height)
	{
		m->dir[cntr] = ft_calloc(m->width + 1, sizeof(char));
		cntr++;
	}
	return (split);
}

int	get_player_pos(t_map *m)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (++i < m->height)
	{
		j = -1;
		while (++j < m->width)
		{
			if (m->dir[i][j] == 'N' || m->dir[i][j] == 'E' ||
				m->dir[i][j] == 'S' || m->dir[i][j] == 'W')
			{
				m->player->stand = m->dir[i][j];
				m->player->pos.x = (double)j + 0.5;
				m->player->pos.y = (double)i + 0.5;
				m->dir[i][j] = '0';
				m->p_count++;
			}
		}
	}
	if (m->p_count > 1)
		return (1);
	return (0);
}

void	fill_map(char **s, t_map *m)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (s[i])
	{
		j = 0;
		len = ft_strlen(s[i]);
		while (j < m->width)
		{
			if (j >= len)
				m->dir[i][j] = ' ';
			else
				m->dir[i][j] = s[i][j];
			j++;
		}
		m->dir[i][j] = '\0';
		i++;
	}
}
