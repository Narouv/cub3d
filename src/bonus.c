/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:01:11 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/25 02:03:30 by rnauke           ###   ########.fr       */
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

	x = 0;
	while (x < (int)game->map->width)
	{
		y = 0;
		while (y < (int)game->map->height)
		{
			if (game->map->dir[x][y] == '1')
				put_square(game, y * 5, x * 5, 0xFFFFFFFF);
			else if (game->map->dir[x][y] == '0')
			{
				if (x == (int)game->player.pos.x
					&& y == (int)game->player.pos.y)
					put_square(game, y * 5, x * 5, 0x0000FFFF);
				else
					put_square(game, y * 5, x * 5, 0xCCCCCCFF);
			}
			else
				put_square(game, y * 5, x * 5, 0x0);
			y++;
		}
		x++;
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
