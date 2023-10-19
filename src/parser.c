/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:15:57 by rhortens          #+#    #+#             */
/*   Updated: 2023/10/19 19:10:13 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	color_check(t_map *m, int fd);

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

void	free_string(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	filename_error(char *file, char *c)
{
	int	i;
	int	j;
	int	n;

	i = ft_strlen(file) - 4;
	j = 0;
	n = 1;
	if (ft_strlen(file) < 5 || i < 0)
		n = -1;
	while (file[i])
	{
		if (file[i++] != c[j++])
			n = -1;
	}
	if (n < 0)
		printf("Error: Invalid file name.\n");
	return (n);
}

int	read_check(char *file)
{
	int	fd;

	if (file[ft_strlen(file) - 1] == '\n')
		file = ft_substr(file, 0, ft_strlen(file) - 1);//maybe leaks wegen ft_substr
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		printf("Error: File can't be read.\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	file_check(char *file)
{
	if (filename_error(file, ".cub") < 0)
		return (1);
	if (!read_check(file))
		return (1);
	return (0);
}

static void	map_dir(t_map *m, int fd)
{
	int		i;
	char	*line;

	i = 0;
	m->height = m->line_count + 2;
	m->width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > (size_t)m->width)
			m->width = ft_strlen(line);
		free(line);
		m->height++;
	}
	m->width += 2;
	m->dir = ft_calloc(m->height, sizeof(char *));
	while (i < m->height)
	{
		m->dir[i] = ft_calloc(m->width + 1, sizeof(char));
		m->dir[i++][m->width] = '\0';
	}
}

int	no_content(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	if (i == j)
		return (1);
	return (0);
}

// static void	space_add(t_map *map, char **line, int i, int end)
// {
// 	int	len;
// 	int	j;
	
// 	len = ft_strlen(*line);
// 	j = 0;
// 	map->dir[i][j++] = ' ';
// 	while (*line[j - 1] != '\n')
// 	{
// 		map->dir[i][j] = *line[j - 1];
// 		j++;
// 	}
// 	// add missing spaces
// 	while (len < end)
// 		map->dir[i][len++] = ' ';
// 	// add new line at end
// 	map->dir[i][j] = '\n';
// }

static void	map_fill(t_map *m, int fd)
{
	int		i;
	int		j;
	char	*line;
	
	int len;

	i = 0;
	j = 0;
	while (j++ < m->line_count + 1)
		line = get_next_line(fd);
	while (line)
	{
		if (!no_content(line))
		{
			len = ft_strlen(line);
			j = 0;
			m->dir[i][j++] = ' ';
			while (j < len + 1)
			{
				m->dir[i][j] = line[j - 1];
				printf("%c", m->dir[i][j]);
				j++;
			}
			// add missing spaces
			while (len < m->width)
			{
				m->dir[i][len++] = ' ';
				printf("%c", m->dir[i][len]);
			}
			// add new line at end
			m->dir[i][len - 1] = '\n';
			m->dir[i][len] = '\0';
		}
		else
			while (j < m->width)
			{
				m->dir[i][j++] = ' ';
				printf("%c", m->dir[i][j]);
			}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
}

int	map_check(t_map *m)
{
	int	i;
	int	j;

	i = 1;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			if (m->dir[i][j] != 'N' && m->dir[i][j] != 'E' &&
				m->dir[i][j] != 'S' && m->dir[i][j] != 'W' &&
				m->dir[i][j] != '0' && m->dir[i][j] != '1' &&
				m->dir[i][j] != ' ' && m->dir[i][j] != '\n' && m->dir[i][j] != '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	dir_check(t_map *m)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (++i < m->height)
	{
		j = -1;
		while (++j < m->width)
		{
			if (m->dir[i][j] == 'N' || m->dir[i][j] == 'E' ||
				m->dir[i][j] == 'S' || m->dir[i][j] == 'W')
			{
				m->player.stand = m->dir[i][j];
				m->player.pos.x = j;
				m->player.pos.y = i;
				n++;
			}
		}
	}
	if (n != 1)
	{
		printf ("Error: Please use exactly one spawn point.\n");
		return (1);
	}
	printf("player x: %f\n", m->player.pos.x);
	printf("player y: %f\n", m->player.pos.y);
	printf("player stand: %c\n", m->player.stand);
	return (0);
}

int	space_check(t_map *m) //0 in line
{
	int	i;
	int	j;

	i = 1;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			// printf("dir i: %d, j: %d\n", i, j);
			if (m->dir[i][j] == '0' || m->dir[i][j] == 'N' ||
				m->dir[i][j] == 'E' || m->dir[i][j] == 'S' ||
				m->dir[i][j] == 'W')
			{
				if (m->dir[i + 1][j] == ' ' || m->dir[i - 1][j] == ' ' ||
					m->dir[i][j + 1] == ' ' || m->dir[i][j - 1] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_validation(t_map *m, int fd, char *file)
{
	int	tmp;

	tmp = open(file, O_RDONLY);
	map_dir(m, fd);
	// space_add(m, &(m->dir[0]), 0, m->width);
	map_fill(m, tmp);
	// space_add(m, &(m->dir[m->height - 1]), 0, m->width);
	close(tmp);
	if (map_check(m) || dir_check(m) || space_check(m))
	{
		printf("Error: Map not valid.\n");
		return (1);
	}
	//initialize stuff
	return (0);
}

int	cond_check(int i, int n)
{
	if (i < 4 || !n)
	{
		printf("Error: Wrong texture input.\n");
		return (0);
	}
	return (1);
}

static int	dirtex_check(char *line, int i)
{
	if (i == 0 && ft_strcmp(line, "NO"))
		return (1);
	else if (i == 1 && ft_strcmp(line, "SO"))
		return (1);
	else if (i == 2 && ft_strcmp(line, "WE"))
		return (1);
	else if (i == 3 && ft_strcmp(line, "EA"))
		return (1);
	else
		printf("Error: Texture not correct.\n");
	return (0);
}

static int	srctex_check(char *src)
{
	if (!read_check(src))
		return (0);
	return (1);
}

static int	line_check(char **split, int i)
{
	if (!dirtex_check(split[0], i))
		return (0);
	if (!srctex_check(split[1]))
		return (0);
	return (1);
}

static int	format_check(char *line, int i)
{
	int		j;
	int		n;
	char	**split;

	j = 0;
	n = 0;
	split = ft_split(line, ' ');
	while (split[j])
		j++;
	if (j != 2)
	{
		if (j != 0)
			free_string(split);
		return (0);
	}
	n = line_check(split, i);
	free_string(split);
	if (!n)
		return (0);
	return (1);
}

int	wrong_texture(t_map *m, int fd)
{
	int		i;
	int		n;
	char	*line;

	i = -1;
	n = 1;
	m->line_count = 0;
	while (++i <= 3 && n)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		m->line_count++;
		if (!no_content(line))
			n = format_check(line, i);
			m->tex_count++; 
		free(line);
	}
	return (cond_check(i, n));
}

// static int	texture_check(t_map *m, char *file)
// {
// 	int	i;
// 	int	tmp;

// 	i = -1;
// 	m->tex_count = 0;
// 	tmp = open(file, O_RDONLY);
// 	while (wrong_texture(m, tmp))
// 		m->tex_count++;
// 	close(tmp);
// 	return (0);
// }

int	col_comma_check(char *line)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == ',')
			n++;
		i++;
	}
	if (n == 2)
		return (1);
	return (0);
}

static int	cf_check(char **col, int i)
{
	if (i == 0)
	{
		if (ft_strcmp(col[0], "F"))
			return (1);
	}
	else if (i == 1)
	{
		if (ft_strcmp(col[0], "C"))
			return (1);
	}
	printf("Error: Ceiling/Floor color not correct.\n");
	free_string(col);
	return (0);
}

int	cub_digit(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	rgb_check(char **num, int n)
{
	int	i;
	int	tmp;
	int	count;

	i = 0;
	tmp = 0;
	count = 0;
	if (cub_digit(num[1]) && cub_digit(num[3]) && cub_digit(num[5]))
	{
		while (i < n)
		{
			if (i % 2 == 1)
			{
				tmp = ft_atoi(num[i]);
				if (tmp > -1 && tmp < 256)
					count++;
			}
			i++;
		}
		if (count == 3)
			return (1);
	}
	free_string(num);
	return (printf("Error: RGB colors wrong.\n"), 0);
}

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != 6)
		return (free_string(split), 0);
	return (i);
}

static int	cosp_check(char cosp, int *len, int *n, int j)
{
	if (cosp == ',')
	{
		if (*len > 0)
			*n += 1;
		*n += 1;
		if (j == 1 && *len > 0)
			return (*len);
		if (j == 1 && *len == 0)
			return (1);
		*len = 0;
	}
	else
	{
		if (*len > 0)
			*n += 1;
		if (j == 1 && *len > 0)
			return (*len);
		*len = 0;
	}
	return (0);
}

int	get_size(char *line, int i, int j)
{
	int	n;
	int	len;
	int	tmp;

	n = 0;
	len = 0;
	tmp = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != ',')
			len ++;
		else
			tmp = cosp_check(line[i], &len, &n, j);
		if (tmp > 0)
			return (tmp);
		i++;
	}
	if (len > 0)
		n++;
	if (j == 1 && len > 0)
		return (len);
	if (j == 1 && len == 0 && line[i - 1] == ',')
		return (1);
	return (n);
}

char	**cub_split(char *line)
{
	int		i;
	int		j;
	int		n;
	int		len;
	char	**split;

	i = 0;
	j = 0;
	split = malloc(sizeof(char *) * get_size(line, 0, 2) + 8);
	while (i < get_size(line, 0, 2))
	{
		n = 0;
		len = get_size(line, j, 1);
		while (line[j] == ' ')
			j++;
		split[i] = malloc(sizeof(char) * len + 1);
		while (n < len)
		{
			if (line[j] == '\n')
				break ;
			split[i][n++] = line[j++];
		}
		split[i][n] = '\0';
		i++;
	}
	split[i] = NULL;
	i = 0;
	return (split);
}

static int	col_format_check(char *line, int i)
{
	int		n;
	char	**split;

	if (!col_comma_check(line))
		return (0);
	split = cub_split(line);
	n = split_count(split);
	if (n == 0)
		return (0);
	if (!cf_check(split, i))
		return (0);
	if (!rgb_check(split, n))
		return (0);
	free_string(split);
	return (1);
}

int	color_check(t_map *m, int fd)
{
	int		i;
	int		n;
	char	*line;

	i = 0;
	n = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		m->line_count++;
		if (!no_content(line))
			n = col_format_check(line, i++);
		free(line);
		if (i > 1 || !n)
			break ;
	}
	if (i < 2 || !n)
	{
		printf("Error: Color input wrong.\n");
		return (1);
	}
	return (0);
}

static void	tex_store(t_map *m, int fd)
{
	int		i;
	char	**tmp;
	char	*line;

	i = 0;
	m->tex = malloc((m->tex_count) * sizeof(char *));
	while (i < m->tex_count - 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_split(line, ' ');
		if (!no_content(line))
			m->tex[i++] = ft_strdup(tmp[1]);
		free_string(tmp);
		free(line);
	}
}

int	rgb_con(char *r, char *g, char *b)
{
	int	red;
	int	green;
	int	blue;
	int	hex;

	red = ft_atoi(r);
	green = ft_atoi(g);
	blue = ft_atoi(b);
	hex = (red << 24) | (green << 16) | (blue << 8) | 0xff;
	return (hex);
}

static void	col_store(t_map *m, int fd)
{
	int		i;
	int		c;
	char	**tmp;
	char	*line;

	i = 0;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = cub_split(line);
		if (!no_content(line))
		{
			c = rgb_con(tmp[1], tmp[3], tmp[5]);
			if (i == 0)
				m->f_col = c;
			else
				m->c_col = c;
			i++;
		}
		free_string(tmp);
		free(line);
	}
}

int	parser(t_map *m, char *file)
{
	int	fd;

	if (file_check(file))
		return (1);
	fd = open(file, O_RDONLY);
 	if (fd == -1)
		return (printf("Error: Opening file.\n"), 1);
	if (!wrong_texture(m, fd) || color_check(m, fd))
	{
		close(fd);
		return (1);
	}
	if (map_validation(m, fd, file))
	{
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	tex_store(m, fd);
	col_store(m, fd);
	close(fd);
	return (0);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	char *map_file = argv[1];
	t_map	map;
	if (parser(&map, map_file) == 0) {
		printf("Map parsing successful!\n");
	} else {
		printf("Map parsing failed!\n");
	}
	return (0);
}

