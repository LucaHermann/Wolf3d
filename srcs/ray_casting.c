/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhermann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:11:04 by lhermann          #+#    #+#             */
/*   Updated: 2017/09/03 17:11:06 by lhermann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static	void	raycasting(t_env *e, int x)
{
	e->player.camerax = 2 * x / (double)WIN_H - 1;
	e->ray.x_pos = e->player.x_pos;
	e->ray.y_pos = e->player.y_pos;
	e->ray.x_dir = e->player.x_dir + (e->ray.x_plane * e->player.camerax);
	e->ray.y_dir = e->player.y_dir + (e->ray.y_plane * e->player.camerax);
	e->ray.x_pos_map = (int)e->ray.x_pos;
	e->ray.y_pos_map = (int)e->ray.y_pos;
	e->ray.x_delta_dist = sqrt(1 + (e->ray.y_dir * e->ray.y_dir) \
		/ (e->ray.x_dir * e->ray.x_dir));
	e->ray.y_delta_dist = sqrt(1 + (e->ray.x_dir * e->ray.x_dir) \
		/ (e->ray.y_dir * e->ray.y_dir));
}

static	void	raydirection(t_env *e)
{
	if (e->ray.x_dir < 0)
	{
		e->player.x_step = -1;
		e->ray.x_side_dist = (e->ray.x_pos - e->ray.x_pos_map)
			* e->ray.x_delta_dist;
	}
	else
	{
		e->player.x_step = 1;
		e->ray.x_side_dist = (e->ray.x_pos_map + 1.0 - e->ray.x_pos)
			* e->ray.x_delta_dist;
	}
	if (e->ray.y_dir < 0)
	{
		e->player.y_step = -1;
		e->ray.y_side_dist = (e->ray.y_pos - e->ray.y_pos_map)
			* e->ray.y_delta_dist;
	}
	else
	{
		e->player.y_step = 1;
		e->ray.y_side_dist = (e->ray.y_pos_map + 1.0 - e->ray.y_pos)
			* e->ray.y_delta_dist;
	}
}

static	void	digital_differential_analyzer(t_env *e)
{
	e->player.hit = 0;
	while (e->player.hit == 0)
	{
		if (e->ray.x_side_dist < e->ray.y_side_dist)
		{
			e->ray.x_side_dist += e->ray.x_delta_dist;
			e->ray.x_pos_map += e->player.x_step;
			e->player.side = 0;
		}
		else
		{
			e->ray.y_side_dist += e->ray.y_delta_dist;
			e->ray.y_pos_map += e->player.y_step;
			e->player.side = 1;
		}
		if (e->map.map[e->ray.x_pos_map][e->ray.y_pos_map] > 0)
			e->player.hit = 1;
	}
}

static	void	camera_dist_calculator(t_env *e)
{
	if (e->player.side == 0)
		e->perp_wall_dist = fabs((e->ray.x_pos_map - e->ray.x_pos
			+ (1 - e->player.x_step) / 2) / e->ray.x_dir);
	else
		e->perp_wall_dist = fabs((e->ray.y_pos_map - e->ray.y_pos
			+ (1 - e->player.y_step) / 2) / e->ray.y_dir);
	e->ray.line_height = abs((int)(WIN_H / e->perp_wall_dist));
	e->ray.draw_start = (-1 * (e->ray.line_height)) / 2 + WIN_H / 2;
	if (e->ray.draw_start < 0)
		e->ray.draw_start = 0;
	e->ray.draw_end = (e->ray.line_height) / 2 + (WIN_H / 2);
	if (e->ray.draw_end >= WIN_H)
		e->ray.draw_end = WIN_H - 1;
}

int				loop_hook(t_env *e)
{
	t_rgb		clr;

	if (e->img.i != NULL)
	{
		mlx_destroy_image(e->mlx, e->img.i);
		e->img.i = NULL;
	}
	e->img.i = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->map.x = -1;
	while (++e->map.x < WIN_W)
	{
		raycasting(e, e->map.x);
		raydirection(e);
		digital_differential_analyzer(e);
		camera_dist_calculator(e);
		color(e, &clr);
		draw_line(e->map.x, e, &clr);
	}
	fpscounter(e);
	player_move(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.i, 0, 0);
	mlx_string_put(e->mlx, e->win, 20, 20, RED, (e->map.free =
		ft_itoa(e->frametime)));
	free(e->map.free);
	return (0);
}
