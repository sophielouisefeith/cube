/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_pos.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/30 18:10:50 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		directione(int y, int x, t_build *build)
{
	if (build->map.array[y][x] == 'N')
	{
		build->data.start = 0;
		build->cor.dirx = 0;
		build->cor.diry = -1;
	}
	if (build->map.array[y][x] == 'E')
	{
		build->data.start = 1;
		build->cor.dirx = 1;
		build->cor.diry = 0;
	}
}

static void		direction(int y, int x, t_build *build)
{
	if (build->map.array[y][x] == 'N' || build->map.array[y][x] == 'E')
		directione(y, x, build);
	if (build->map.array[y][x] == 'S')
	{
		build->data.start = 2;
		build->cor.dirx = 0;
		build->cor.diry = 1;
		build->ray.x_cam = 1;
	}
	if (build->map.array[y][x] == 'W')
	{
		build->data.start = 3;
		build->cor.dirx = -1;
		build->cor.diry = 0;
		build->ray.x_cam = 1;
	}
}

static void		sprite_cor(t_build *build)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	if (!(build->sprite_s.sprite_cor = (double **)\
	malloc(sizeof(double *) * build->sprite.num)))
		error("malloc failed", 13);
	while (build->map.array[y] != NULL)
	{
		x = 0;
		while (build->map.array[y][x])
		{
			if (build->map.array[y][x] == '2')
			{
				build->sprite_s.sprite_cor[i] = malloc(sizeof(double) * 2);
				build->sprite_s.sprite_cor[i][0] = (double)x;
				build->sprite_s.sprite_cor[i][1] = (double)y;
				i++;
			}
			x++;
		}
		y++;
	}
}

static void		start_cor(int y, int x, t_build *build)
{
	x = 0;
	while (build->map.array[y][x])
	{
		if (build->map.array[y][x] == 'W' || build->map.array[y][x] == 'E' || \
		build->map.array[y][x] == 'N' || build->map.array[y][x] == 'S')
		{
			build->cor.validstartpost = 1;
			build->cor.start_pos_x = x + 0.5;
			build->cor.start_pos_y = y + 0.5;
			build->data.count++;
			direction(y, x, build);
		}
		if (build->data.count > 1)
			error("to many start positonions", 26);
		if (build->map.array[y][x] == '2')
			build->sprite.num++;
		x++;
	}
}

void			start_pos(t_build *build)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (build->map.array[y])
	{
		start_cor(y, x, build);
		y++;
	}
	sprite_cor(build);
}
