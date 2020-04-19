/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 21:05:46 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/19 12:42:04 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// protect go out of the game
// the errors looking around. 

int    presskey( int keycode, t_build *build)
{
    build->ray.moveup = 0;
	build->ray.movedown = 0;
	build->ray.moveright = 0;
	build->ray.moveleft = 0;
	printf("presskeyr\n");
    if(keycode == 13)
	{
		printf("w\n");
        build->ray.moveup = 1;
		build->ray.update = 1;
	}
    if(keycode == 1)
	{
        build->ray.movedown = 1;
		build->ray.update = 1;
	}
    if(keycode == 0)
	{
        build->ray.moveleft = 1;
		build->ray.update = 1;
	}
    if(keycode == 2 )
	{
        build->ray.moveright = 1;
		build->ray.update = 1;
	}
    return(0);
}

static void movefront(t_build *build)
{
	if(build->ray.moveup == 1)
	{
		printf("kom je in up and down\n");
		if(build->map.array[build->cor.start_pos_y][(int)(build->cor.start_pos_x + build->cor.dirx)]== '0')
			build->cor.start_pos_x += build->cor.dirx;
		if(build->map.array[(int)(build->cor.start_pos_y + build->cor.diry)][build->cor.start_pos_x] == '0')
			build->cor.start_pos_y += build->cor.diry;
		build->ray.moveup = 0;
	}
	if(build->ray.movedown == 1)
	{
		printf(" down\n");
		if(build->map.array[build->cor.start_pos_y][(int)(build->cor.start_pos_x + build->cor.diry)]== '0')
		{
			build->cor.start_pos_y += build->cor.diry;
			printf(" down1\n");
		}
		if(build->map.array[(int)(build->cor.start_pos_y + build->cor.diry)][build->cor.start_pos_x] == '0')
		{
			build->cor.start_pos_x += build->cor.dirx;
			printf(" down2\n");
		}
		build->ray.movedown = 0;
		
	}
}

static void moveside(t_build *build)
{
	if(build->ray.moveright == 1)	
	{
		build->ray.oldirx = build->cor.dirx;
		build->cor.dirx = build->cor.dirx * cos(-build->ray.rotspeed) - build->cor.diry * sin(-build->ray.rotspeed);
		build->cor.diry = build->ray.oldirx * sin(-build->ray.rotspeed) + build->cor.diry * cos(-build->ray.rotspeed);
		build->ray.oldplanex = build->ray.planex;
		build->ray.planex = build->ray.planex * cos(-build->ray.rotspeed) - build->ray.planey * sin(-build->ray.rotspeed);
		build->ray.planey = build->ray.oldplanex * sin(-build->ray.rotspeed) + build->ray.planey * cos(-build->ray.rotspeed);
	}
	if(build->ray.moveleft == 1)
	{
		build->ray.oldirx = build->cor.dirx;
		build->cor.dirx = build->cor.dirx * cos(build->ray.rotspeed) - build->cor.diry * sin(build->ray.rotspeed);
		build->cor.diry = build->ray.oldirx * sin(build->ray.rotspeed) + build->cor.diry * cos(build->ray.rotspeed);
		build->ray.oldplanex = build->ray.planex;
		build->ray.planex = build->ray.planex * cos(build->ray.rotspeed) - build->ray.planey * sin(-build->ray.rotspeed);
		build->ray.planey = build->ray.oldplanex * sin(-build->ray.rotspeed) + build->ray.planey * cos(-build->ray.rotspeed);
	}	
}

void        move(t_build *build)
{
	
    build->ray.oldtime = build->ray.time;
	build->ray.time = clock();
	build->ray.frametime = (build->ray.time - build->ray.oldtime) / 1000.0;
	//build->ray.movespeed = build->ray.frametime * 5.0;
	build->ray.rotspeed = build->ray.frametime * 3.0;
	
	
	movefront(build);
	moveside(build);
	//build->ray.movespeed = 0;
}