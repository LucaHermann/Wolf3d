/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhermann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:09:11 by lhermann          #+#    #+#             */
/*   Updated: 2017/09/03 17:09:17 by lhermann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void		set_color(t_rgb *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

static void		mlx_image_put_pixel(void *m, t_img *i, t_coordint p, t_rgb *c)
{
	if (i->e)
	{
		i->d[p.y * i->sz + p.x *
			i->bpp / 8] = mlx_get_color_value(m, c->r);
		i->d[p.y * i->sz + p.x *
			i->bpp / 8 + 1] = mlx_get_color_value(m, c->g);
		i->d[p.y * i->sz + p.x *
			i->bpp / 8 + 2] = mlx_get_color_value(m, c->b);
	}
	else
	{
		i->d[p.y * i->sz + i->bpp / 8 * p.x] = mlx_get_color_value(m, c->b);
		i->d[p.y * i->sz + i->bpp / 8 * p.x + 1] = mlx_get_color_value(m, c->g);
		i->d[p.y * i->sz + i->bpp / 8 * p.x + 2] = mlx_get_color_value(m, c->r);
	}
}

void			draw_line(int x, t_env *e, t_rgb *color)
{
	t_coordint	pixel;
	t_rgb		sky_floor;

	pixel.x = x;
	e->img.d = mlx_get_data_addr(e->img.i, &e->img.bpp, &e->img.sz, &e->img.e);
	set_color(&sky_floor, 80, 120, 240);
	pixel.y = 0;
	while (pixel.y < e->ray.draw_start)
	{
		mlx_image_put_pixel(e, &e->img, pixel, &sky_floor);
		pixel.y++;
	}
	pixel.y = e->ray.draw_start;
	while (pixel.y < e->ray.draw_end)
	{
		mlx_image_put_pixel(e, &e->img, pixel, color);
		pixel.y++;
	}
	set_color(&sky_floor, 190, 190, 190);
	pixel.y = e->ray.draw_end;
	while (pixel.y < WIN_H)
	{
		mlx_image_put_pixel(e, &e->img, pixel, &sky_floor);
		pixel.y++;
	}
}

void			color(t_env *e, t_rgb *color)
{
	if (e->player.side == 0)
	{
		if (e->player.x_step < 0)
			set_color(color, 255, 102, 0);
		else
			set_color(color, 0, 204, 255);
	}
	else if (e->player.y_step < 0)
		set_color(color, 0, 255, 0);
	else
		set_color(color, 255, 51, 204);
}

void			fpscounter(t_env *e)
{
	struct timeval time;

	e->oldtime = e->time;
	gettimeofday(&time, 0);
	e->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	e->frametime = e->time - e->oldtime;
	mlx_string_put(e->mlx, e->win, 20, 20, RED, ft_itoa(e->frametime));
	e->player.mvspeed = e->frametime * 0.003;
	e->player.rotspd = e->frametime * 0.003;
	e->player.sprint = e->frametime * 0.05 * e->player.mvspeed;
}
