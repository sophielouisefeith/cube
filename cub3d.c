/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:53:05 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/04 14:59:00 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    image(t_build *build)
{
	int y = build->cor.y;			
	int x = build->cor.x;			
	int width = x + 100;		
	int heigth = y + 100;
	int color;

	color = 0x48d1cc;		
	while (y <= heigth)
	{
		x = build->cor.x;
		while (x <= width && x < 450)
		{
			
			my_mlx_pixel_put(build, x, y, color);
			x++;
			color++;
		}
		y++;
		color++;
	}
	return ;
}

t_build	initialize(t_build *build)
{
	build->cor.x = 70;
	build->cor.y = 70;
	return(*build);
}

int main()
{
    t_build	build;
	t_img	img;

	build.img = &img;

	build.cor.x = 50;
	build.cor.y = 50;
    build.img->mlx = mlx_init();
    build.img->win1 = mlx_new_window(build.img->mlx, 1000, 1000, "start");
   	build.img->img1 = mlx_new_image(build.img->mlx, 800, 800);
	build.img->addr = mlx_get_data_addr(build.img->img1, &build.img->bits_per_pixel, &build.img->line_length, &build.img->endian); 
	build = initialize(&build);
	image(&build);
    mlx_put_image_to_window(build.img->mlx, build.img->win1, build.img->img1, 400, 400);

	mlx_loop(build.img->mlx);
}
