/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/19 10:31:03 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/19 12:53:29 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     fill(int x, t_build *build)
{
    build->tex.texx = 0;
    build->tex.step = 0;
    build->tex.texpos = 0;
    build->tex.texy = 0;
    
	int rgb;
	rgb = 0xffe4e1;
	if (build->ray.side == 1)
		rgb = rgb /2;
    build->tex.texnum = build->map.array[(int)build->cor.start_pos_x][(int)build->cor.start_pos_y] -1;
    if (build->ray.side == 0)
       build->tex.wallx = build->cor.start_pos_y + build->ray.perpwalldist * build->ray.raydiry;
    else
        build->tex.wallx = build->cor.start_pos_x + build->ray.perpwalldist * build->ray.raydirx;
    build->tex.wallx -= floor((build->tex.wallx));
    build->tex.texx = (int)(build->tex.wallx + 64);
    if (build->ray.side == 0 && build->ray.raydirx > 0)
        build->tex.texx = 64 - build->tex.texx -1;
    if (build->ray.side == 1 && build->ray.raydiry < 0)
        build->tex.texx = 64 - build->tex.texx -1;
    
    build->tex.step = 1.0 + 64/ build->ray.lineheight;
    build->tex.texpos = (build->ray.drawstart - build->data.res_y / 2 + build->ray.lineheight / 2 * build->tex.step);
    
    int y;
    
    y = build->ray.drawstart;
   
   while( y < build->ray.drawstart)
   {
        build->tex.texy = (int)build->tex.texpos & (64 -1);
        build->tex.texpos += build->tex.step;
        y++;
   }
    
	while(build->ray.drawstart < build->ray.drawend)
	{
		my_mlx_pixel_put(build, x, build->ray.drawstart, rgb);
		build->ray.drawstart++;
	}
    return(0);    
}