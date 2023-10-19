/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:58:05 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/19 21:43:43 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_player *player)
{
	if (player->stand == 'N')
	{
		player->viewdir.x = -1;
		player->viewdir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else if (player->stand == 'W')
	{
		player->viewdir.x = 0;
		player->viewdir.y = 1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else if (player->stand == 'S')
	{
		player->viewdir.x = 1;
		player->viewdir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	else
	{
		player->viewdir.x = 0;
		player->viewdir.y = -1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
}

void	init_ray(t_ray *ray)
{
	ray->angle.x = 0;
	ray->angle.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->map_pos.x = 0;
	ray->map_pos.y = 0;
	ray->side = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
}

void	init_game(t_mlxinfo *game)
{
	game->time = 0;
	game->str_update_time = 0;
	game->old_time = 0;
	game->map = ft_calloc(1, sizeof(t_map));
}

// only works for square textures (same width and height)
int	*get_pixel_data(char *img_path)
{
	int				*txt_arr;
	uint8_t			p;
	size_t			tx;
	size_t			ty;
	mlx_texture_t	*t;

	t = mlx_load_png(img_path);
	p = t->bytes_per_pixel;
	ty = 0;
	txt_arr = malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
	while (ty < TEX_WIDTH)
	{
		tx = 0;
		while (tx < TEX_WIDTH)
		{
			txt_arr[TEX_WIDTH * ty + tx]
				= t->pixels[TEX_WIDTH * tx * p + ty * p] << 24
				| t->pixels[TEX_WIDTH * tx * p + ty * p + 1] << 16
				| t->pixels[TEX_WIDTH * tx * p + ty * p + 2] << 8
				| t->pixels[TEX_WIDTH * tx * p + ty * p + 3];
			tx++;
		}
		ty++;
	}
	return (txt_arr);
}

// t_veci	wall = x -> wall start, y -> wall end
t_veci	calc_wall_height(int *wall_height, double ray_len)
{
	t_veci	wall;

	*wall_height = (int)(HEIGHT / ray_len);
	wall.x = (-*wall_height / 2) + (HEIGHT / 2);
	if (wall.x < 0)
		wall.x = 0;
	wall.y = (*wall_height / 2) + (HEIGHT / 2);
	if (wall.y >= HEIGHT)
		wall.y = HEIGHT - 1;
	return wall;
}

void	draw_pixel_column(mlx_image_t *img, int x, t_veci wall, t_texture texture)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < wall.x)
			mlx_put_pixel(img, x, y, 0x520575FF);
		else if (y >= wall.x && y < wall.y)
		{
			texture.color
				= texture.pixels[(TEX_HEIGHT * texture.x + (int)texture.y)];
			mlx_put_pixel(img, x, y, texture.color);
			texture.y += texture.tex_step;
		}
		else
			mlx_put_pixel(img, x, y, 0x32a852FF);
		y++;
	}
}

// t_veci	wall = x -> wall start, y -> wall end
void	calc_pixel_column(t_mlxinfo *game, int x, t_texture *texture)
{
	double		wall_hit;
	t_veci		wall;
	t_ray		ray;
	t_player	player;

	ray = game->ray;
	player = game->player;
	wall = calc_wall_height(&texture->wall_height, game->ray.length);
	if (ray.side == 0)
		wall_hit = player.pos.y + game->ray.length * ray.angle.y;
	else
		wall_hit = player.pos.x + game->ray.length * ray.angle.x;
	wall_hit -= floor((wall_hit));
	texture->x = wall_hit * (double)TEX_WIDTH;
	if (ray.side == 0 && ray.angle.x > 0)
		texture->x = TEX_WIDTH - texture->x - 1;
	if (ray.side == 1 && ray.angle.y < 0)
		texture->x = TEX_WIDTH - texture->x - 1;
	texture->tex_step = 1.0 * (double)TEX_HEIGHT / texture->wall_height;
	texture->y
		= ((double)wall.x - (double)HEIGHT
			/ 2 + (double)texture->wall_height / 2)
		* texture->tex_step;
	draw_pixel_column(game->img, x, wall, *texture);
}

int	get_texture_side(t_ray *ray)
{
	if (ray->side == 0 && ray->step_dir.x < 0)
		return (0);
	if (ray->side == 0 && ray->step_dir.x > 0)
		return (1);
	if (ray->side == 1 && ray->step_dir.y < 0)
		return (2);
	if (ray->side == 1 && ray->step_dir.y > 0)
		return (3);
	return (0);
}

void	cast_rays(t_mlxinfo *game)
{
	size_t		x;
	double		camera;
	t_player	*player;
	t_ray		*ray;

	x = 0;
	player = &game->player;
	ray = &game->ray;
	while (x < WIDTH)
	{
		camera = 2 * x / (double)WIDTH - 1;
		update_ray(ray, player, camera);
		ray_direction(ray, player);
		ray_length(ray, game->map);
		calc_pixel_column(game, x, &game->texture[get_texture_side(ray)]);
		x++;
	}
}

void	clear_screen(void *param)
{
	mlx_image_t	*image;
	uint32_t	i;
	uint32_t	y;

	image = param;
	i = 0;
	while (i < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			mlx_put_pixel(image, i, y, 0x000000FF);
			y++;
		}
		i++;
	}
}

void	init_textures(t_mlxinfo *game)
{
	game->texture = malloc(4 * sizeof(t_texture));
	game->texture[0].pixels = get_pixel_data(game->map->tex[0]);
	game->texture[1].pixels = get_pixel_data(game->map->tex[1]);
	game->texture[2].pixels = get_pixel_data(game->map->tex[2]);
	game->texture[3].pixels = get_pixel_data(game->map->tex[3]);
}

// void	cleanup(t_mlxinfo *game)
// {
// 	free(&game);
// }

void	init_map(t_map *map, t_player *player)
{
	map->player = player;
}

int	main(int argc, char **argv)
{
	t_mlxinfo	*game;
	mlx_t		*mlx;
	char *map_file;

	if (argc != 2) {
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	map_file = argv[1];
	game = malloc(sizeof(t_mlxinfo));
	init_game(game);
	init_map(game->map, &game->player);
	init_player(&game->player);
	init_ray(&game->ray);
	if (parser(game->map, map_file) == 0) {
		printf("Map parsing successful!\n");
	} else {
		printf("Map parsing failed!\n");
	}
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx = game->mlx;
	game->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	init_textures(game);
	mlx_image_to_window(mlx, game->img, 0, 0);
	mlx_loop_hook(mlx, ft_controls, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	// cleanup(game);
	system("leaks cub3d");
	return (0);
}
