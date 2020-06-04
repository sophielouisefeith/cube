/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 21:05:46 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/06/04 17:50:26 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void zero(int keycode, t_build *build)
{
	build->ray.moveup = 0;
	build->ray.movedown = 0;
	build->ray.moveright = 0;
	build->ray.moveleft = 0;
	build->ray.update = 0;
	if (keycode == 53)
		close_game(build);
}

int    presskey( int keycode, t_build *build)
{
	zero(keycode, build);
	build->ray.update = 1;
    if(keycode == 126)
        build->ray.moveup = 1;
    if(keycode == 125)
    	build->ray.movedown = 1;
    if(keycode == 123)
        build->ray.moveleft = 1;
    if(keycode == 124 )
        build->ray.moveright = 1;
    return(0);
}

static void movefront(t_build *build)
{
	if(build->ray.moveup == 1)
	{
		if(build->map.array[(int)build->cor.start_pos_y]\
		[(int)(build->cor.start_pos_x + build->cor.dirx * build->ray.movespeed)] == '0')
			build->cor.start_pos_x += build->cor.dirx * build->ray.movespeed;
		if(build->map.array[(int)(build->cor.start_pos_y + build->cor.diry \
		* build->ray.movespeed)][(int)build->cor.start_pos_x] == '0')
			build->cor.start_pos_y += build->cor.diry * build->ray.movespeed;
		build->ray.moveup = 0;
	}
	if(build->ray.movedown == 1)
	{
		if(build->map.array[build->cor.start_pos_y][(int)(build->cor.start_pos_x + \
		build->cor.diry * build->ray.movespeed)]== '0')
			build->cor.start_pos_y += build->cor.diry * build->ray.movespeed;
		if(build->map.array[(int)(build->cor.start_pos_y + build->cor.diry *\
		 build->ray.movespeed)][build->cor.start_pos_x] == '0')
			build->cor.start_pos_x += build->cor.dirx * build->ray.movespeed;
		build->ray.movedown = 0;
	}
}

static void moveside(t_build *build)
{
	build->ray.oldirx = build->cor.dirx;
	// build->ray.oldplanex = build->ray.planex;
	if(build->ray.moveleft == 1)	
	{
		build->cor.dirx = build->cor.dirx * cos(-build->ray.rotspeed) - build->cor.diry * sin(-build->ray.rotspeed);
		build->cor.diry = build->ray.oldirx * sin(-build->ray.rotspeed) + build->cor.diry * cos(-build->ray.rotspeed);
		build->ray.oldplanex = build->ray.planex;
		build->ray.planex = build->ray.planex * cos(-build->ray.rotspeed) - build->ray.planey * sin(-build->ray.rotspeed);
		build->ray.planey = build->ray.oldplanex * sin(-build->ray.rotspeed) + build->ray.planey * cos(-build->ray.rotspeed);
		build->ray.oldplanex = build->ray.planex;
	}
	if(build->ray.moveright == 1)
	{
		build->cor.dirx = build->cor.dirx * cos(build->ray.rotspeed) - build->cor.diry * sin(build->ray.rotspeed);
		build->cor.diry = build->ray.oldirx * sin(build->ray.rotspeed) + build->cor.diry * cos(build->ray.rotspeed);
		build->ray.oldplanex = build->ray.planex;
		build->ray.planex = build->ray.planex * cos(build->ray.rotspeed) - build->ray.planey * sin(build->ray.rotspeed);
		build->ray.planey = build->ray.oldplanex * sin(build->ray.rotspeed) + build->ray.planey * cos(build->ray.rotspeed);
		
	}	
}

void        move(t_build *build)
{
	if(build->ray.moveup == 1 || build->ray.movedown  == 1)
		movefront(build);
	moveside(build);
}