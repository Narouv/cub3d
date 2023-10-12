/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:36:02 by rnauke            #+#    #+#             */
/*   Updated: 2023/09/25 18:37:19 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// int	get_map(int fd)
// {
	
// }

int	verify_input(t_map *m)
{
	char *str;
	str = get_next_line(m->map_fd);
	if (ft_strncmp(str, "NO ", 3))
		return (0);
	m->north = mlx_load_png(str+3);
	str = get_next_line(m->map_fd);
	if (ft_strncmp(str, "SO ", 3))
		return (0);
	m->south = mlx_load_png(str+3);
	str = get_next_line(m->map_fd);
	if (ft_strncmp(str, "WE ", 3))
		return (0);
	m->west = mlx_load_png(str+3);
	str = get_next_line(m->map_fd);
	if (ft_strncmp(str, "EA ", 3))
		return (0);
	printf("%s", (str+3));
	m->east = mlx_load_png(str+3);
	get_next_line(m->map_fd);
	str = get_next_line(m->map_fd);
	if (ft_strncmp(str, "F ", 2))
		return (0);
	m->floor = ft_strdup(str+2);
	str = get_next_line(m->map_fd);
	if (ft_strncmp(str, "C ", 2))
		return (0);
	m->ceil = ft_strdup(str+2);
	if (!m->north || m->south || !m->west || !m->east)
		return (0);
	get_next_line(m->map_fd);
	// get_map();
	return (1);
}

// int main(int argc, char **argv)
// {
// 	int fd;
// 	if (argc != 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd > 0)
// 		verify_input(fd);
// }