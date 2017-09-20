/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhermann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:11:25 by lhermann          #+#    #+#             */
/*   Updated: 2017/09/03 17:28:11 by lhermann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	fill(t_env *e, int imax, int jmax)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < imax)
	{
		while (++j < jmax)
		{
			e->map.map[i][j] = e->map.tmp[i][j] - 48;
		}
		j = -1;
	}
}

void	pacman(t_env *e)
{
	ft_strcpy(e->map.tmp[0], "1111111111111111111111");
	ft_strcpy(e->map.tmp[1], "1000000000220000000001");
	ft_strcpy(e->map.tmp[2], "1002202220220222022001");
	ft_strcpy(e->map.tmp[3], "1002202220220222022001");
	ft_strcpy(e->map.tmp[4], "1000000000000000000001");
	ft_strcpy(e->map.tmp[5], "1002202022222202022001");
	ft_strcpy(e->map.tmp[6], "1000002000220002000001");
	ft_strcpy(e->map.tmp[7], "1222202220220222022221");
	ft_strcpy(e->map.tmp[8], "1222202000000002022221");
	ft_strcpy(e->map.tmp[9], "1222202022002202022221");
	ft_strcpy(e->map.tmp[10], "1000000020000200000001");
	ft_strcpy(e->map.tmp[11], "1000000022222200000001");
	ft_strcpy(e->map.tmp[12], "1222202000000002022221");
	ft_strcpy(e->map.tmp[13], "1222202022222202022221");
	ft_strcpy(e->map.tmp[14], "1222202000220002022221");
	ft_strcpy(e->map.tmp[15], "1000000000220000000001");
	ft_strcpy(e->map.tmp[16], "1022202220220222022201");
	ft_strcpy(e->map.tmp[17], "1000200000000000020001");
	ft_strcpy(e->map.tmp[18], "1200202022222202020021");
	ft_strcpy(e->map.tmp[19], "1000002000220002000001");
	ft_strcpy(e->map.tmp[20], "1022222220220022222201");
	ft_strcpy(e->map.tmp[21], "1000000000000000000001");
	ft_strcpy(e->map.tmp[22], "1111111111111111111111");
	fill(e, 23, 22);
}

void	forty_two(t_env *e)
{
	ft_strcpy(e->map.tmp[0], "111111111111111111111");
	ft_strcpy(e->map.tmp[1], "100000000000000000001");
	ft_strcpy(e->map.tmp[2], "100000000000000000001");
	ft_strcpy(e->map.tmp[3], "100220022000222220001");
	ft_strcpy(e->map.tmp[4], "100220022000000022001");
	ft_strcpy(e->map.tmp[5], "100220022000000022001");
	ft_strcpy(e->map.tmp[6], "100222222000022220001");
	ft_strcpy(e->map.tmp[7], "100022222000220000001");
	ft_strcpy(e->map.tmp[8], "100000022000220000001");
	ft_strcpy(e->map.tmp[9], "100000022000222222001");
	ft_strcpy(e->map.tmp[10], "100000000000000000001");
	ft_strcpy(e->map.tmp[11], "100000000000000000001");
	ft_strcpy(e->map.tmp[12], "111111111111111111111");
	fill(e, 13, 21);
}

void	labyasf(t_env *e)
{
	ft_strcpy(e->map.tmp[0], "11111111111111111");
	ft_strcpy(e->map.tmp[1], "10000002200020001");
	ft_strcpy(e->map.tmp[2], "10022200002220201");
	ft_strcpy(e->map.tmp[3], "10200222200000001");
	ft_strcpy(e->map.tmp[4], "10000000202222201");
	ft_strcpy(e->map.tmp[5], "10202020200000201");
	ft_strcpy(e->map.tmp[6], "10202020202220221");
	ft_strcpy(e->map.tmp[7], "12222022200020001");
	ft_strcpy(e->map.tmp[8], "10000000000022201");
	ft_strcpy(e->map.tmp[9], "10222020202000201");
	ft_strcpy(e->map.tmp[10], "10202020000020201");
	ft_strcpy(e->map.tmp[11], "10202020202002201");
	ft_strcpy(e->map.tmp[12], "10202000000200001");
	ft_strcpy(e->map.tmp[13], "10202222220000201");
	ft_strcpy(e->map.tmp[14], "10000000020200001");
	ft_strcpy(e->map.tmp[15], "10202020020222201");
	ft_strcpy(e->map.tmp[16], "10222222220200001");
	ft_strcpy(e->map.tmp[17], "11111111111111111");
	fill(e, 18, 17);
}

void	check_file(t_env *e, char *arg)
{
	if (ft_strcmp("Pacman", arg) == 0)
	{
		pacman(e);
	}
	else if (ft_strcmp("42", arg) == 0)
	{
		forty_two(e);
	}
	else if (ft_strcmp("Laby", arg) == 0)
	{
		labyasf(e);
	}
	else
	{
		ft_putendl("Map dispo : Pacman, 42, Laby.");
		exit(EXIT_FAILURE);
	}
}
