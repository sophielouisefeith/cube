/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:22:37 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/17 16:57:51 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ray(t_build *build)
{
    int x;  
	double camerax;
	double raydirx;
	double raydiry;

	x = 0;
	build->ray.planex = 0;
	build->ray.planey = 0.66;

	// raycast(x, build);
	while (x < build->data.res_x)  
	{
		camerax = 2 * x / build->data.res_x  - 1;
		raydirx = build->cor.dirx + build->ray.planex * camerax;
		raydiry = build->cor.diry + build->ray.planey * camerax;
		build->cor.mapx = (int)build->cor.start_pos_x;
		build->cor.mapy = (int)build->cor.start_pos_y;
		double sidedistx;
    	double sidedisty;
		double deltadistx =  fabs(1 / raydirx);
    	double deltadisty = fabs(1 / raydiry);
		double perpwalldist;
		int stepx;
		int stepy;
		int hit = 0;
		int side;
		if ( raydirx < 0)
		{

			stepx = -1;
			sidedistx = (build->cor.start_pos_x - build->cor.mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (build->cor.mapx + 1.0 - build->cor.start_pos_x) * deltadistx;
		}
		if (raydiry < 0 )
		{
			stepy = -1;
			sidedisty = (build->cor.start_pos_y - build->cor.mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (build->cor.mapy + 1.0 - build->cor.start_pos_y) * deltadisty;
		}
		while ( hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				build->cor.mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				build->cor.mapy += stepy;
				side = 1;
			}
			if (build->map.array[build->cor.mapy][build->cor.mapx] == '1') 
				hit = 1;
		}
		if( side == 0)
			perpwalldist = (build->cor.mapx - build->cor.start_pos_x + (1 - stepx) / 2) / raydirx;
			
			
		else
			perpwalldist = (build->cor.mapy - build->cor.start_pos_y + (1 - stepy) / 2) / raydiry;
		int lineheight = (int)(build->data.res_y/ perpwalldist);
		int drawstart = -lineheight / 2 + build->data.res_y / 2;
		if (drawstart < 0) 
			drawstart = 0;
		int drawend = lineheight /2 + build->data.res_y / 2;
		if (drawend >= build->data.res_y )
			drawend = build->data.res_y - 1;
		int rgb;
		rgb = 0xffe4e1;
		if (side == 1)
			rgb = rgb /2;
		while(drawstart < drawend)
		{
			my_mlx_pixel_put(build, x, drawstart, rgb);
			drawstart++;
		}
        x++;
    }
   	mlx_put_image_to_window(build->img.mlx, build->img.win, build->img.img1, 0, 0);
    return(0); 
}

