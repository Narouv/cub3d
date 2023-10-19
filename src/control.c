/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:01:07 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/19 21:24:01 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	rot_fov(t_mlxinfo *game, double rot_val)
{
	double		odx;
	double		ody;
	double		rs;
	t_player	*p;

	p = &game->player;
	rs = (game->time - game->old_time) * rot_val;
	odx = p->viewdir.x;
	p->viewdir.x = p->viewdir.x * cos(rs) - p->viewdir.y * sin(rs);
	p->viewdir.y = odx * sin(rs) + p->viewdir.y * cos(rs);
	ody = p->plane.x;
	p->plane.x = p->plane.x * cos(rs) - p->plane.y * sin(rs);
	p->plane.y = ody * sin(rs) + p->plane.y * cos(rs);
}

void	move_player(t_mlxinfo *game, t_vec axis, double val)
{
	double	move_speed;

	move_speed = (game->time - game->old_time) * val;
	game->player.pos.x += axis.x * move_speed;
	game->player.pos.y += axis.y * move_speed;
}

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

void minimap(void *i, char **map)
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

void	ft_controls(void *g)
{
	t_mlxinfo	*game;

	game = g;
	game->old_time = game->time;
	game->time = mlx_get_time();
	clear_screen(game->img);
	cast_rays(game);
	minimap(game->img, game->map->dir);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, game->player.viewdir, 5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, game->player.viewdir, -5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, game->player.plane, 5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, game->player.plane, -5.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rot_fov(game, -3.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rot_fov(game, 3.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
