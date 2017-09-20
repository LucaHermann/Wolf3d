/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhermann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:08:40 by lhermann          #+#    #+#             */
/*   Updated: 2017/09/03 17:08:47 by lhermann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>

# define WIN_W	950
# define WIN_H	750
# define RED	0xFF0000

# define ESCAPE		53
# define FORWARD	13
# define BACKWARD	1
# define LEFT		0
# define RIGHT		2

typedef struct		s_img
{
	void			*i;
	char			*d;
	int				bpp;
	int				sz;
	int				e;
}					t_img;

typedef struct		s_keys
{
	int				forward;
	int				backward;
	int				left;
	int				right;
}					t_keys;

typedef struct		s_player
{
	double			x_pos;
	double			y_pos;
	double			x_dir;
	double			y_dir;
	double			old_dir;
	double			rotspd;
	double			mvspeed;
	double			camerax;
	int				x_step;
	int				y_step;
	int				hit;
	int				side;
	int				sprint;
	t_keys			keypress;
}					t_player;

typedef struct		s_ray
{
	double			x_pos;
	double			y_pos;
	double			x_dir;
	double			y_dir;
	double			x_plane;
	double			y_plane;
	double			prev_plane;
	double			x_side_dist;
	double			y_side_dist;
	double			x_delta_dist;
	double			y_delta_dist;
	int				pos_neg;
	int				x_pos_map;
	int				y_pos_map;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct		s_map
{
	int				map[24][24];
	char			tmp[24][24];
	char			*free;
	int				x;
	int				display;
	int				x_size;
	int				y_size;
}					t_map;

typedef struct		s_env
{
	double			*mlx;
	double			*win;
	t_img			img;
	t_player		player;
	t_map			map;
	t_ray			ray;
	double			perp_wall_dist;
	double			time;
	double			oldtime;
	long int		frametime;
}					t_env;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_coordint
{
	int				x;
	int				y;
}					t_coordint;

/*
** CHECKER
*/

int					mainif(void);
void				fill(t_env *e, int imax, int jmax);
void				pacman(t_env *e);
void				check_file(t_env *e, char *arg);
void				labyasf(t_env *e);
void				forty_two(t_env *e);

/*
** RAYCASTING
*/

int					loop_hook(t_env *e);

/*
** DRAW
*/

void				draw_line(int x, t_env *e, t_rgb *color);
void				color(t_env *e, t_rgb *color);
void				fpscounter(t_env *e);

/*
** KEYHOOK
*/

int					quit(void);
int					keypress(int keypress, t_env *e);
int					keyrelease(int keyrelease, t_env *e);
void				player_move(t_env *e);

#endif
