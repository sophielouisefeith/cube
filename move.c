/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/30 18:07:45 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					presskey(int keycode, t_build *build)
{
	build->ray.update = 0;
	if (keycode == 53)
		close_game(build);
	build->ray.update = 1;
	if (keycode == 126)
		build->ray.moveup = 1;
	if (keycode == 125)
		build->ray.movedown = 1;
	if (keycode == 123)
		build->ray.moveleft = 1;
	if (keycode == 124)
		build->ray.moveright = 1;
	return (0);
}

static void			movefront(t_build *build)
{
	if (build->ray.moveup == 1)
	{
		if (build->map.array[(int)build->cor.start_pos_y]\
		[(int)(build->cor.start_pos_x + build->cor.dirx * \
		build->ray.movespeed)] == '0')
			build->cor.start_pos_x += build->cor.dirx * build->ray.movespeed;
		if (build->map.array[(int)(build->cor.start_pos_y + build->cor.diry \
		* build->ray.movespeed)][(int)build->cor.start_pos_x] == '0')
			build->cor.start_pos_y += build->cor.diry * build->ray.movespeed;
		build->ray.moveup = 0;
	}
	if (build->ray.movedown == 1)
	{
		if (build->map.array[(int)build->cor.start_pos_y]
		[(int)(build->cor.start_pos_x + build->cor.dirx \
		* build->ray.movespeed)] == '0')
			build->cor.start_pos_x -= build->cor.dirx * build->ray.movespeed;
		if (build->map.array[(int)(build->cor.start_pos_y + build->cor.diry *\
		build->ray.movespeed)][build->cor.start_pos_x] == '0')
			build->cor.start_pos_y -= build->cor.diry * build->ray.movespeed;
		build->ray.movedown = 0;
	}
}

static void			moveside_2(t_build *build)
{
	build->cor.dirx = build->cor.dirx * cos(build->ray.rotspeed) \
	- build->cor.diry * sin(build->ray.rotspeed);
	build->cor.diry = build->ray.oldirx * sin(build->ray.rotspeed) \
	+ build->cor.diry * cos(build->ray.rotspeed);
	build->ray.oldplanex = build->ray.planex;
	build->ray.planex = build->ray.planex * cos(build->ray.rotspeed)\
	- build->ray.planey * sin(build->ray.rotspeed);
	build->ray.planey = build->ray.oldplanex * sin(build->ray.rotspeed) \
	+ build->ray.planey * cos(build->ray.rotspeed);
}

static void			moveside(t_build *build)
{
	build->ray.oldirx = build->cor.dirx;
	if (build->ray.moveleft == 1)
	{
		build->cor.dirx = build->cor.dirx * cos(-build->ray.rotspeed)\
		- build->cor.diry * sin(-build->ray.rotspeed);
		build->cor.diry = build->ray.oldirx * sin(-build->ray.rotspeed)\
		+ build->cor.diry * cos(-build->ray.rotspeed);
		build->ray.oldplanex = build->ray.planex;
		build->ray.planex = build->ray.planex * cos(-build->ray.rotspeed)\
		- build->ray.planey * sin(-build->ray.rotspeed);
		build->ray.planey = build->ray.oldplanex * sin(-build->ray.rotspeed)\
		+ build->ray.planey * cos(-build->ray.rotspeed);
		build->ray.oldplanex = build->ray.planex;
	}
	if (build->ray.moveright == 1)
		moveside_2(build);
}

void				move(t_build *build)
{
	if (build->ray.moveup == 1 || build->ray.movedown == 1)
		movefront(build);
	moveside(build);
}
