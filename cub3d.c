/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:53:05 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/30 16:43:48 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		prep_scrsht(t_build *build)
{
	move(build);
	ray(build);
	sprite(build);
}

int				make(t_build *build)
{
	printf("starten van het scherm\n");
	mlx_put_image_to_window(build->img.mlx, build->img.win, \
	build->img.img1, 0, 0);
	floor_ceiling(build);
	if (build->ray.update)
		move(build);
	ray(build);
	sprite(build);
	mlx_hook(build->img.win, 2, 1L << 0, &presskey, build);
	mlx_hook(build->img.win, 17, 1L << 17, close_game, &build);
	build->ray.update = 0;
	return (0);
}

int	startgame(t_build *build)
{
	printf("start game\n");
	if(!(build->sprite.zbuffer = (double*)malloc(sizeof(double) * build->data.res_x)))
		error_game("malloc failed", 13, build);
	build->ray.planex = (build->cor.diry == 0) ? 0 : 0.66;
	build->ray.planey = (build->cor.diry == 0) ? 0.66 : 0;
	build->ray.oldtime = 0;
	build->ray.time = 0;
	//printf("kom je voor het voorbereiden\n");
	if(!(build->img.mlx = mlx_init()))
		error_game("malloc failed", 13, build);
	if(!(build->img.win = mlx_new_window(build->img.mlx, build->data.res_x, \
	build->data.res_y, "WOLFENSTEIN")))
		error_game("malloc failed", 13, build);
	if(!(build->img.img1 = mlx_new_image(build->img.mlx, \
	build->data.res_x, build->data.res_y)))
		error_game("malloc failed", 13, build);
	if(!(build->img.addr = mlx_get_data_addr(build->img.img1, \
	&build->img.bits_per_pixel, &build->img.line_length, &build->img.endian)))
		error_game("malloc failed", 13, build);
	if (build->data.scrsht == 1)
	{
		printf("waarom kom je hier?\n");
		prep_scrsht(build);
		make_bmp("screenshot.bmp", build);
	}
	printf("kom je voor het voorbereiden\n");
	mlx_loop_hook(build->img.mlx, make, build);
	mlx_loop(build->img.mlx);
	return (0);
}
