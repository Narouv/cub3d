/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:01:07 by rnauke            #+#    #+#             */
/*   Updated: 2023/10/25 03:35:14 by rnauke           ###   ########.fr       */
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
	double		move_speed;
	t_player	*p;
	t_map		*m;

	p = &game->player;
	m = game->map;
	move_speed = (game->time - game->old_time) * val;
	if (m->dir[(int)p->pos.y][(int)(p->pos.x + (axis.x * move_speed))] == '0')
		p->pos.x += axis.x * move_speed;
	if (m->dir[(int)(p->pos.y + (axis.y * move_speed))][(int)p->pos.x] == '0')
		p->pos.y += axis.y * move_speed;
}

void	ft_controls(void *g)
{
	t_mlxinfo	*game;

	game = g;
	game->old_time = game->time;
	game->time = mlx_get_time();
	clear_screen(game->img);
	cast_rays(game);
	minimap(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, game->player.viewdir, 3.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, game->player.viewdir, -3.0);
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
