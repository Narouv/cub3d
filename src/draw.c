/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:45:51 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/21 16:49:49 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	return (wall);
}

void	draw_pixel_column(t_mlxinfo *game, int x, t_veci wall, t_texture t)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < wall.x)
			mlx_put_pixel(game->img, x, y, game->map->c_col);
		else if (y >= wall.x && y < wall.y)
		{
			t.color
				= t.pixels[(TEX_HEIGHT * t.x + (int)t.y)];
			mlx_put_pixel(game->img, x, y, t.color);
			t.y += t.tex_step;
		}
		else
			mlx_put_pixel(game->img, x, y, game->map->f_col);
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
	draw_pixel_column(game, x, wall, *texture);
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
