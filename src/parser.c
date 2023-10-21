/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:15:57 by rhortens          #+#    #+#             */
/*   Updated: 2023/10/21 17:02:08 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	texture(char *tex_str, char **tex_path, char *symbol, t_map *m)
{
	char	*str;
	char	*set;

	set = ft_strjoin(symbol, " \t\n");
	str = ft_strtrim(tex_str, set);
	free(set);
	if (!read_check(str))
	{
		free(str);
		return (1);
	}
	*tex_path = ft_strdup(str);
	m->tex_count++;
	return (0);
}

int	check_struct(char *line, char *str)
{
	free(line);
	if (ft_strncmp(str, "F", 1) && ft_strncmp(str, "C", 1)
		&& ft_strncmp(str, "N", 1) && ft_strncmp(str, "S", 1)
		&& ft_strncmp(str, "E", 1) && ft_strncmp(str, "W", 1))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	color_or_texture(int fd, t_map *m)
{
	char	*line;
	char	*str;
	int		ret_val;

	ret_val = 0;
	while (!ret_val && (m->tex_count != 4 || !m->f_col || !m->c_col))
	{
		line = skip_empty_lines(fd, m);
		str = ft_strtrim(line, "\t \n");
		if (!ft_strncmp(str, "F ", 2))
			ret_val = color(str, &m->f_col);
		else if (!ft_strncmp(str, "C ", 2))
			ret_val = color(str, &m->c_col);
		else if (!ft_strncmp(str, "NO ", 3))
			ret_val = texture(str, &m->tex[0], "NO", m);
		else if (!ft_strncmp(str, "SO ", 3))
			ret_val = texture(str, &m->tex[1], "SO", m);
		else if (!ft_strncmp(str, "EA ", 3))
			ret_val = texture(str, &m->tex[2], "EA", m);
		else if (!ft_strncmp(str, "WE ", 3))
			ret_val = texture(str, &m->tex[3], "WE", m);
		if (check_struct(line, str))
			break ;
	}
	return (ret_val);
}

void	save_map(int fd, t_map *m)
{
	char	*line;
	char	*one;

	line = skip_empty_lines(fd, m);
	m->whole_map = ft_strjoin("", line);
	while (line)
	{
		one = m->whole_map;
		m->whole_map = ft_strjoin(one, line);
		free(one);
		free(line);
		line = get_next_line(fd);
	}
}

int	get_map(int fd, t_map *m)
{
	char	**s;

	save_map(fd, m);
	s = get_dimensions(m);
	fill_map(s, m);
	if (check_bounds(m->dir, m))
	{
		ft_printf("invalid map\n");
		return (1);
	}
	if (get_player_pos(m))
	{
		ft_printf("only 1 player allowed\n");
		return (1);
	}
	printf("x: %f y: %f", m->player->pos.x, m->player->pos.y);
	return (0);
}
