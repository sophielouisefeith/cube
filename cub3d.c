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

int				make(t_build *build)
{
	mlx_put_image_to_window(build->img.mlx, build->img.win, \
	build->img.img1, 0, 0);
	floor_ceiling(build);
	if (build->ray.update)
		move(build);
	ray(build);
	sprite(build);
	mlx_hook(build->img.win, 2, 1L << 0, &presskey, build);
	mlx_hook(build->img.win, 3, 1L << 0, &releasekey, build);
	mlx_hook(build->img.win, 17, 1L << 17, &close_game, build);
	build->ray.update = 0;
	return (0);
}

int	startgame(t_build *build)
{
	build->ray.planex = (build->cor.diry == 0) ? 0 : 0.66;
	build->ray.planey = (build->cor.diry == 0) ? 0.66 : 0;
	build->ray.oldtime = 0;
	build->ray.time = 0;
	if (!(build->img.mlx = mlx_init()))
		error_total("malloc failed2", 15, build);
	if (!(build->img.win = mlx_new_window(build->img.mlx, build->data.res_x, \
	build->data.res_y, "WOLFENSTEIN")))
		error_total("malloc failed3", 16, build);
	if (!(build->img.img1 = mlx_new_image(build->img.mlx, \
	build->data.res_x, build->data.res_y)))
		error_total("malloc failed4", 17, build);
	if (!(build->img.addr = mlx_get_data_addr(build->img.img1, \
	&build->img.bits_per_pixel, &build->img.line_length, &build->img.endian)))
		error_total("malloc failed5", 18, build);
	if (build->data.scrsht == 1)
	{
		make(build);
		make_bmp("screenshot.bmp", build);
		return (0);
	}
	mlx_loop_hook(build->img.mlx, make, build);
	mlx_loop(build->img.mlx);
	return (0);
}
