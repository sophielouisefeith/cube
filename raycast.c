/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:22:37 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/30 17:45:21 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ray(t_build *build)
{
    int x;  
	double camerax;
	x = 0;
	// build->ray.planex = 0;
	// build->ray.planey = 10;

	build->ray.planex = (build->cor.diry == 0) ? 0 : 0.66;
	build->ray.planey = (build->cor.diry == 0) ? 0.66 : 0;
	
	while (x < build->data.res_x)  
	{
		camerax = 2 * x / build->data.res_x  - 1; //spiegel
		build->ray.raydirx = build->cor.dirx + build->ray.planex * camerax;
		build->ray.raydiry = build->cor.diry + build->ray.planey * camerax;
		build->cor.mapx = (int)build->cor.start_pos_x;
		build->cor.mapy = (int)build->cor.start_pos_y;
		double sidedistx;
    	double sidedisty;
		double deltadistx =  fabs(1 / build->ray.raydirx);
    	double deltadisty = fabs(1 / build->ray.raydiry);
		
		int stepx;
		int stepy;
		int hit = 0;

		if ( build->ray.raydirx < 0)
		{
			stepx = -1;
			sidedistx = (build->cor.start_pos_x - build->cor.mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (build->cor.mapx + 1.0 - build->cor.start_pos_x) * deltadistx;
		}
		if (build->ray.raydiry < 0 )
		{
			stepy = -1;
			sidedisty = (build->cor.start_pos_y - build->cor.mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (build->cor.mapy + 1.0 - build->cor.start_pos_y) * deltadisty;
		}
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				build->cor.mapx += stepx;
				build->ray.side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				build->cor.mapy += stepy;
				build->ray.side= 1;
			}
			if (build->map.array[build->cor.mapy][build->cor.mapx] == '1') 
				hit = 1;
		}
		if( build->ray.side == 0)
			build->ray.perpwalldist = (build->cor.mapx - build->cor.start_pos_x + (1 - stepx) / 2) / build->ray.raydirx;
		else
			build->ray.perpwalldist = (build->cor.mapy - build->cor.start_pos_y + (1 - stepy) / 2) / build->ray.raydiry;
		build->ray.lineheight = (int)(build->data.res_y/ build->ray.perpwalldist);
		build->ray.drawstart =- build->ray.lineheight / 2 + build->data.res_y / 2;
		if (build->ray.drawstart < 0) 
			build->ray.drawstart = 0;
		build->ray.drawend = build->ray.lineheight / 2 + build->data.res_y / 2;
		if (build->ray.drawend >= build->data.res_y )
			build->ray.drawend = build->data.res_y - 1;
		fill(x, build);
		//locate_sprites(build);
		// build->sprite.zbuffer[x] = build->ray.perpwalldist;
		//sprite(build);
        x++;
    }
   	mlx_put_image_to_window(build->img.mlx, build->img.win, build->img.img1, 0, 0);
    return(0); 
}

