/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:22:37 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/05/13 08:53:33 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void start(int x, t_build *build)
{
	build->ray.camerax = 2 * x / build->data.res_x  - 1;
	build->ray.raydirx = build->cor.dirx + build->ray.planex * build->ray.camerax;
	build->ray.raydiry = build->cor.diry + build->ray.planey * build->ray.camerax;
	build->cor.mapx = (int)build->cor.start_pos_x;
	build->cor.mapy = (int)build->cor.start_pos_y;
	build->ray.deltadistx =  fabs(1 / build->ray.raydirx);
    build->ray.deltadisty = fabs(1 / build->ray.raydiry);
}

static  void side_ray(t_build *build)
{
	if ( build->ray.raydirx < 0)
	{
		build->ray.stepx = -1;
		build->ray.sidedistx = (build->cor.start_pos_x - build->cor.mapx) * build->ray.deltadistx;
	}
	else
	{
		build->ray.stepx = 1;
		build->ray.sidedistx = (build->cor.mapx + 1.0 - build->cor.start_pos_x) * build->ray.deltadistx;
	}
	if (build->ray.raydiry < 0 )
	{
		build->ray.stepy = -1;
		build->ray.sidedisty = (build->cor.start_pos_y - build->cor.mapy) * build->ray.deltadisty;
	}
	else
	{
		build->ray.stepy = 1;
		build->ray.sidedisty = (build->cor.mapy + 1.0 - build->cor.start_pos_y) * build->ray.deltadisty;
	}
	
}

static void hit(t_build *build)
{
	int hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (build->ray.sidedistx < build->ray.sidedisty)
		{
			build->ray.sidedistx += build->ray.deltadistx;
			build->cor.mapx += build->ray.stepx;
			build->ray.side = 0;
		}
		else
		{
			build->ray.sidedisty += build->ray.deltadisty;
			build->cor.mapy += build->ray.stepy;
			build->ray.side = 1;
		}
		if (build->map.array[build->cor.mapy][build->cor.mapx] == '1') 
			hit = 1;
	}
}

static void border(t_build *build)
{
	//build->ray.perpwalldist = (build->cor.mapy - build->cor.start_pos_y + (1 - build->ray.stepy) / 2) / build->ray.raydiry;
	printf("perpwalldist [%f] \n", build->ray.perpwalldist);
	build->ray.lineheight = (int)(build->data.res_y/ build->ray.perpwalldist);
	build->ray.drawstart = -build->ray.lineheight / 2 + build->data.res_y / 2;
	if (build->ray.drawstart < 0) 
		build->ray.drawstart = 0;
	build->ray.drawend = build->ray.lineheight / 2 + build->data.res_y / 2;
	if (build->ray.drawend >= build->data.res_y )
		build->ray.drawend = build->data.res_y - 1;
	build->tex.wallx -= floor((build->tex.wallx));
}

int     ray(t_build *build)
{
    int x;  
	x = 0;
	build->ray.camerax = 2 * x / build->data.res_x -1 ; //spiegel
	// build->ray.planex = 0;
	// build->ray.planey = 10;
	while (x < build->data.res_x)  
	{

		start(x, build);
		side_ray(build);
		hit(build);
		border(build);
		fill(x, build);
		build->ray.oldtime = build->ray.time;
		build->ray.time = clock();
		build->ray.frametime = (build->ray.time - build->ray.oldtime) / 500.0;
		build->ray.movespeed = build->ray.frametime * 1.0;
		build->ray.rotspeed = build->ray.frametime * 1.0;
		x++;
	}
	return(0);
}



























		// build->ray.camerax = 2 * x / build->data.res_x  - 1; //spiegel
		// build->ray.raydirx = build->cor.dirx + build->ray.planex * build->ray.camerax;
		// build->ray.raydiry = build->cor.diry + build->ray.planey * build->ray.camerax;
		// build->cor.mapx = (int)build->cor.start_pos_x;
		// build->cor.mapy = (int)build->cor.start_pos_y;
		// double build->ray.sidedistx; //sidedist
    	// double build->ray.sidedisty;
		// double build->ray.deltadistx =  fabs(1 / build->ray.raydirx);
    	// double build->ray.deltadisty = fabs(1 / build->ray.raydiry);
		
		//build->ray.stepx;
		//build->ray.stepy;
		//int hit = 0;

		// if ( build->ray.raydirx < 0)
		// {
		// 	build->ray.stepx = -1;
		// 	build->ray.sidedistx = (build->cor.start_pos_x - build->cor.mapx) * build->ray.deltadistx;
		// }
		// else
		// {
		// 	build->ray.stepx = 1;
		// 	build->ray.sidedistx = (build->cor.mapx + 1.0 - build->cor.start_pos_x) * build->ray.deltadistx;
		// }
		// if (build->ray.raydiry < 0 )
		// {
		// 	build->ray.stepy = -1;
		// 	build->ray.sidedisty = (build->cor.start_pos_y - build->cor.mapy) * build->ray.deltadisty;
		// }
		// else
		// {
		// 	build->ray.stepy = 1;
		// 	build->ray.sidedisty = (build->cor.mapy + 1.0 - build->cor.start_pos_y) * build->ray.deltadisty;
		// }
		// while (hit == 0)
		// {
		// 	if (build->ray.sidedistx < build->ray.sidedisty)
		// 	{
		// 		build->ray.sidedistx += build->ray.deltadistx;
		// 		build->cor.mapx += build->ray.stepx;
		// 		build->ray.side = 0;
		// 	}
		// 	else
		// 	{
		// 		build->ray.sidedisty += build->ray.deltadisty;
		// 		build->cor.mapy += build->ray.stepy;
		// 		build->ray.side = 1;
		// 	}
		// 	if (build->map.array[build->cor.mapy][build->cor.mapx] == '1') 
		// 		hit = 1;
		// }
		//if( build->ray.side == 0)
			// build->ray.perpwalldist = (build->cor.mapx - build->cor.start_pos_x + (1 - build->ray.stepx) / 2) / build->ray.raydirx;
		//else
			// build->ray.perpwalldist = (build->cor.mapy - build->cor.start_pos_y + (1 - build->ray.stepy) / 2) / build->ray.raydiry;
		// build->ray.lineheight = (int)(build->data.res_y/ build->ray.perpwalldist);
		// build->ray.drawstart =- build->ray.lineheight / 2 + build->data.res_y / 2;
		// if (build->ray.drawstart < 0) 
		// 	build->ray.drawstart = 0;
		// build->ray.drawend = build->ray.lineheight / 2 + build->data.res_y / 2;
		// if (build->ray.drawend >= build->data.res_y )
		// 	build->ray.drawend = build->data.res_y - 1;
		// build->tex.wallx -= floor((build->tex.wallx));
		// if (build->ray.side == 1)
        // build->tex.wallx = build->cor.start_pos_x + ((build->cor.mapy - build->cor.start_pos_y +\
        // (1 - build->ray.stepy) / 2) / build->ray.raydiry) * build->ray.raydirx;
    	// else if (build->ray.side == 0)
        // build->tex.wallx = build->cor.start_pos_y + ((build->cor.mapx - build->cor.start_pos_x +\
        // (1 - build->ray.stepx) / 2) / build->ray.raydirx) * build->ray.raydiry;
   		//build->tex.wallx -= floor((build->tex.wallx));
		//fill(x, build);
		// build->ray.oldtime = build->ray.time;
		// build->ray.time = clock();
		// build->ray.frametime = (build->ray.time - build->ray.oldtime) / 500.0;
		// build->ray.movespeed = build->ray.frametime * 1.0;
		// build->ray.rotspeed = build->ray.frametime * 1.0;

		//locate_sprites(build);
		// build->sprite.zbuffer[x] = build->ray.perpwalldist;
		//sprite(build);
      //  x++;
   // }
   	// mlx_put_image_to_window(build->img.mlx, build->img.win, build->img.img1, 0, 0);

