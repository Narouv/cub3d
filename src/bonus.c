/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:01:11 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 17:38:13 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_square(t_mlxinfo *game, int x, int y, int color)
{
	int	xs;
	int	ys;
	int	scale;

	scale = 5;
	xs = 0;
	while (xs < scale)
	{
		ys = 0;
		while (ys < scale)
		{
			if (!xs || !ys)
				mlx_put_pixel(game->img, x + xs, y + ys, 0x000000FF);
			else if (xs == scale -1 || ys == scale -1)
				mlx_put_pixel(game->img, x + xs, y + ys, 0x000000FF);
			else
				mlx_put_pixel(game->img, x + xs, y + ys, color);
			ys++;
		}
		xs++;
	}
}

void	minimap(t_mlxinfo *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)game->map->height)
	{
		x = 0;
		while (x < (int)game->map->width)
		{
			if (game->map->dir[y][x] == '1')
				put_square(game, x * 5, y * 5, 0xFFFFFFFF);
			else if (game->map->dir[y][x] == '0')
			{
				if (x == (int)game->player.pos.x
					&& y == (int)game->player.pos.y)
					put_square(game, x * 5, y * 5, 0x0000FFFF);
				else
					put_square(game, x * 5, y * 5, 0xCCCCCCFF);
			}
			else
				put_square(game, x * 5, y * 5, 0x0);
			x++;
		}
		y++;
	}
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
