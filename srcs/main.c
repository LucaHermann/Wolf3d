/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhermann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:10:47 by lhermann          #+#    #+#             */
/*   Updated: 2017/09/03 17:28:25 by lhermann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int			main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		e.img.i = 0;
		e.time = 0;
		e.oldtime = 0;
		e.player.x_pos = 2.5;
		e.player.y_pos = 2.5;
		e.player.x_dir = -1;
		e.player.y_dir = 0;
		e.ray.x_plane = 0;
		e.ray.y_plane = 0.66;
		check_file(&e, av[1]);
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, WIN_W, WIN_H, "Wolf3d");
		mlx_loop_hook(e.mlx, &loop_hook, &e);
		mlx_hook(e.win, 2, (1L << 1), &keypress, &e);
		mlx_hook(e.win, 3, (1L << 0), &keyrelease, &e);
		mlx_hook(e.win, 17, 0L, &quit, &e);
		mlx_loop(e.mlx);
	}
	else
		mainif();
	return (0);
}

int			mainif(void)
{
	ft_putendl("Map dispo : Pacman, 42, Laby.");
	return (0);
}
