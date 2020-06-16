/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:22:37 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/06/16 17:05:15 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		start(int x, t_build *build)
{
	build->ray.camerax = 2 * x / build->data.res_x - 1;
	if (build->ray.x_cam == 1)
		build->ray.camerax *= -1;
	build->ray.raydirx = build->cor.dirx + build->ray.planex * \
	build->ray.camerax;
	build->ray.raydiry = build->cor.diry + build->ray.planey * \
	build->ray.camerax;
	build->cor.mapx = (int)build->cor.start_pos_x;
	build->cor.mapy = (int)build->cor.start_pos_y;
	build->ray.deltadistx = fabs(1 / build->ray.raydirx);
	build->ray.deltadisty = fabs(1 / build->ray.raydiry);
}

static void	side_ray(t_build *build)
{
	if (build->ray.raydirx < 0)
	{
		build->ray.stepx = -1;
		build->ray.sidedistx = (build->cor.start_pos_x - build->cor.mapx)\
		* build->ray.deltadistx;
	}
	else
	{
		build->ray.stepx = 1;
		build->ray.sidedistx = (build->cor.mapx + 1.0 - \
		build->cor.start_pos_x) * build->ray.deltadistx;
	}
	if (build->ray.raydiry < 0)
	{
		build->ray.stepy = -1;
		build->ray.sidedisty = (build->cor.start_pos_y - build->cor.mapy) \
		* build->ray.deltadisty;
	}
	else
	{
		build->ray.stepy = 1;
		build->ray.sidedisty = (build->cor.mapy + 1.0 - \
		build->cor.start_pos_y) * build->ray.deltadisty;
	}
}

static void		hit(t_build *build)
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

static void	border(t_build *build)
{
	build->ray.lineheight = abs((int)(build->data.res_y / \
	build->ray.perpwalldist));
	build->ray.drawstart = -build->ray.lineheight / \
	2 + build->data.res_y / 2;
	if (build->ray.drawstart < 0)
		build->ray.drawstart = 0;
	build->ray.drawend = build->ray.lineheight / 2 + build->data.res_y / 2;
	if (build->ray.drawend >= build->data.res_y)
		build->ray.drawend = build->data.res_y - 1;
	if (build->ray.side == 1)
	{
		build->tex.wallx = build->cor.start_pos_x + \
		((build->cor.mapy - build->cor.start_pos_y +\
		(1 - build->ray.stepy) / 2) / \
		build->ray.raydiry) * build->ray.raydirx;
	}
	else
		build->tex.wallx = build->cor.start_pos_y + \
		((build->cor.mapx - build->cor.start_pos_x +\
		(1 - build->ray.stepx) / 2)\
		/ build->ray.raydirx) * build->ray.raydiry;
	build->tex.wallx -= floor((build->tex.wallx));
	build->tex.texx = (build->tex.wallx * (double)64);
	build->tex.texx = 64 - build->tex.texx - 1;
}

int		ray(t_build *build)
{
	int x;

	x = 0;
	while (x < build->data.res_x)
	{
		start(x, build);
		side_ray(build);
		hit(build);
		border(build);
		fill(x, build);
		x++;
	}
	build->ray.oldtime = build->ray.time;
	build->ray.time = clock();
	build->ray.frametime = (build->ray.time - build->ray.oldtime)\
	/ CLOCKS_PER_SEC;
	build->ray.movespeed = build->ray.frametime * 20.0;
	build->ray.rotspeed = build->ray.frametime * 3.0;
	return (0);
}
