/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhermann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:10:28 by lhermann          #+#    #+#             */
/*   Updated: 2017/09/03 17:10:33 by lhermann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int				quit(void)
{
	exit(0);
}

int				keypress(int keypress, t_env *e)
{
	if (keypress == FORWARD)
		e->player.keypress.forward = 1;
	if (keypress == BACKWARD)
		e->player.keypress.backward = 1;
	if (keypress == LEFT)
		e->player.keypress.left = 1;
	if (keypress == RIGHT)
		e->player.keypress.right = 1;
	return (0);
}

int				keyrelease(int keyrelease, t_env *e)
{
	if (keyrelease == FORWARD)
		e->player.keypress.forward = 0;
	if (keyrelease == BACKWARD)
		e->player.keypress.backward = 0;
	if (keyrelease == LEFT)
		e->player.keypress.left = 0;
	if (keyrelease == RIGHT)
		e->player.keypress.right = 0;
	if (keyrelease == ESCAPE)
		quit();
	return (0);
}

static	void	player_turn(t_env *e, char determ)
{
	double	old_dir;
	double	prev_plane;
	int		pos_neg;

	old_dir = e->player.x_dir;
	pos_neg = 1;
	prev_plane = e->ray.x_plane;
	if (determ == 'R')
		pos_neg = -1;
	e->player.x_dir = e->player.x_dir * cos(pos_neg * e->player.rotspd)
		- e->player.y_dir * sin(pos_neg * e->player.rotspd);
	e->player.y_dir = old_dir * sin(pos_neg * e->player.rotspd)
		+ e->player.y_dir * cos(pos_neg * e->player.rotspd);
	e->ray.x_plane = e->ray.x_plane * cos(pos_neg * e->player.rotspd)
		- e->ray.y_plane * sin(pos_neg * e->player.rotspd);
	e->ray.y_plane = prev_plane * sin(pos_neg * e->player.rotspd)
		+ e->ray.y_plane * cos(pos_neg * e->player.rotspd);
}

void			player_move(t_env *e)
{
	if (e->player.keypress.forward)
	{
		if (!(e->map.map[(int)(e->player.x_pos + e->player.x_dir *
						e->player.mvspeed)][(int)e->player.y_pos]))
			e->player.x_pos += e->player.x_dir * e->player.mvspeed;
		if (!(e->map.map[(int)e->player.x_pos][(int)(e->player.y_pos
						+ e->player.y_dir * e->player.mvspeed)]))
			e->player.y_pos += e->player.y_dir * e->player.mvspeed;
	}
	if (e->player.keypress.backward)
	{
		if (!(e->map.map[(int)(e->player.x_pos - e->player.x_dir *
						e->player.mvspeed)][(int)e->player.y_pos]))
			e->player.x_pos -= e->player.x_dir * e->player.mvspeed;
		if (!(e->map.map[(int)e->player.x_pos][(int)(e->player.y_pos
						- e->player.y_dir * e->player.mvspeed)]))
			e->player.y_pos -= e->player.y_dir * e->player.mvspeed;
	}
	if (e->player.keypress.right)
		player_turn(e, 'R');
	if (e->player.keypress.left)
		player_turn(e, 'L');
}
