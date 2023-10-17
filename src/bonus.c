/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:01:11 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/17 16:48:01 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	put_square(mlx_image_t *img, int x, int y, int color)
{
	int scale = 10; // replace with some sort of scale in the struct
	for (int xs = 0; xs < scale; xs++)
		for (int ys = 0; ys < scale; ys++)
			if (!xs || !ys)
				mlx_put_pixel(img, x+xs, y+ys, 0x000000FF);
			else if (xs == scale -1 || ys == scale -1)
				mlx_put_pixel(img, x+xs, y+ys, 0x000000FF);
			else
				mlx_put_pixel(img, x+xs, y+ys, color);
}

void minimap(void *i/*, char **map*/)
{
	mlx_image_t *img = i;
	int scale = 10; // replace with some sort of scale in the struct
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] == '1')
				put_square(img, x*scale, y*scale, 0xFFFFFFFF);
			else if (map[y][x] == '0')
				put_square(img, x*scale, y*scale, 0xCCCCCCFF);
			else
				put_square(img, x*scale, y*scale, 0x0);
		}	
	}
}

void	check_door(t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step_dir.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step_dir.y;
			ray->side = 1;
		}
		if (map[ray->map_pos.x][ray->map_pos.y] == '2')
		{
			ray->door = 1;
			hit = 1;
		}
		else if (map[ray->map_pos.x][ray->map_pos.y] == '1')
		{
			ray->door = 0;
			hit = 1;
		}
	}
	if (!ray->side)
		ray->length = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->length = (ray->side_dist.y - ray->delta_dist.y);
}

void	mouse_rot(void *g)
{
	t_mlxinfo	*game;
	int			x;
	int			y;

	game = (t_mlxinfo *)g;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	rot_fov(game, -((((double)x - ((double)WIDTH / 2))) * 0.1));
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}

void	move_player(t_mlxinfo *game, t_vec axis, double val)
{
	double	move_speed;

	move_speed = (game->time - game->old_time) * val;
	game->player.pos.x += axis.x * move_speed;
	game->player.pos.y += axis.y * move_speed;
}

void	toggle_door(t_mlxinfo *game)
{
	double	l;
	int		x;
	double	camera;

	x = WIDTH / 2;
	camera = 2 * x / (double)WIDTH - 1;
	update_ray(&game->ray, &game->player, camera);
	ray_direction(&game->ray, &game->player);
	l = check_door(&game->ray);
	if (game->ray.door)
		map[game->ray.map_pos.x][game->ray.map_pos.y] = '1';
	else
		map[game->ray.map_pos.x][game->ray.map_pos.y] = '2';
}

int	main(void)
{
	t_mlxinfo	*game;
	mlx_t		*mlx;
	
	game = malloc(sizeof(t_mlxinfo));
	init_game(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx = game->mlx;
	game->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	init_player(&game->player);
	init_ray(&game->ray);
	init_textures(game);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(mlx, game->img, 0, 0);
	mlx_loop_hook(mlx, ft_controls_bonus, game);
	// mlx_loop_hook(mlx, mouse_rot, game);
	mlx_cursor_hook(mlx, (mlx_cursorfunc)mouse_rot, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	system("leaks cub3d");
	return (0);
}
