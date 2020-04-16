/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 21:05:46 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/16 13:20:45 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



// int    presskey( int keycode, t_build *build)
// {
//     //printf("hallo");
//     if(keycode == 13)
//         build->ray.moveup = 1;
//     if(keycode == 1)
//         build->ray.movedown = 1 ;
//     if(keycode == 0)
//         build->ray.moveleft = 1 ;
//     if(keycode == 2 )
//         build->ray.moveright = 1;
    
//     return(0);
// }

void        move(t_build *build)
{
      //  printf("hallo");
        build->ray.oldtime = build->ray.time;
		build->ray.time = clock();
		build->ray.frametime = (build->ray.time - build->ray.oldtime) / 1000.0;
		//print(1.0 / build->ray.frametime);
		//redraw;
		//cls();

		build->ray.movespeed = build->ray.frametime * 5.0;
		build->ray.rotspeed = build->ray.frametime * 3.0;

		//readkeys waarschijnlijk word dit dus een apparte functie

		//moveforward 
		if(build->ray.moveup == 1)
		{
			if(build->map.array[(int)(build->cor.start_pos_x + build->cor.dirx * build->ray.movespeed)]
			[(int)(build->cor.start_pos_y)] == '0')
				build->cor.start_pos_x += build->cor.dirx * build->ray.movespeed;
			if(build->map.array[(int)(build->cor.start_pos_x)]
			[(int)(build->cor.start_pos_y + build->cor.diry * build->ray.movespeed)] == '0')
				build->cor.start_pos_y += build->cor.diry * build->ray.movespeed;
			build->ray.moveup = 0;

		}
		if(build->ray.movedown == 1)
		{
			if(!build->map.array[(int)(build->cor.start_pos_x - build->cor.dirx * build->ray.movespeed)]
			[(int)build->cor.start_pos_y])
				build->cor.start_pos_x -= build->cor.dirx * build->ray.movespeed;
			if(!build->map.array[(int)build->cor.start_pos_x]
			[(int)(build->cor.start_pos_y - build->cor.diry * build->ray.movespeed)])
				build->cor.start_pos_y -= build->cor.diry * build->ray.movespeed;
			build->ray.movedown = 0;
		}
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