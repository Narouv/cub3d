/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:58:05 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 17:14:14 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parser(t_map *m, char *file)
{
	int		fd;

	if (file_check(file))
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Opening file.\n"), 1);
	if (color_or_texture(fd, m) || diagnose(m))
	{
		close(fd);
		return (1);
	}
	if (get_map(fd, m))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static void	init_all(t_mlxinfo *game)
{
	init_game(game);
	init_map(game->map, &game->player);
	init_player(&game->player);
	init_ray(&game->ray);
}

int	main(int argc, char **argv)
{
	t_mlxinfo	*game;
	mlx_t		*mlx;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	game = malloc(sizeof(t_mlxinfo));
	init_all(game);
	if (parser(game->map, argv[1]))
		return (1);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx = game->mlx;
	game->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	init_textures(game);
	mlx_image_to_window(mlx, game->img, 0, 0);
	mlx_loop_hook(mlx, ft_controls, game);
	mlx_cursor_hook(mlx, (mlx_cursorfunc)mouse_rot, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	// cleanup(game);
	// system("leaks cub3d");
	return (0);
}
