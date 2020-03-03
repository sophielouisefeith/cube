/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:53:05 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/03 18:01:06 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    square2(t_cub *cub)
{
	int y = cub->var.y;			
	int x = cub->var.x;			
	int width = x + 100;		
	int heigth = y + 100;
	int color;

	color = 0x48d1cc;		
	while (y <= heigth)
	{
		x = cub->var.x;
		while (x <= width && x < 450)
		{
			
			my_mlx_pixel_put(cub, x, y, color);
			x++;
			color++;
		}
		y++;
		color++;
	}
	return ;
}

t_cub	initialize(t_cub *cub)
{
	cub->var.x = 70;
	cub->var.y = 70;
	return(*cub);
}

int main()
{
    t_cub	cub;
	t_img	img;

	cub.img = &img;

	cub.var.x = 50;
	cub.var.y = 50;
    cub.img->mlx = mlx_init();
    cub.img->win1 = mlx_new_window(cub.img->mlx, 1000, 1000, "start");
   	cub.img->img1 = mlx_new_image(cub.img->mlx, 800, 800);
	cub.img->addr = mlx_get_data_addr(cub.img->img1, &cub.img->bits_per_pixel, &cub.img->line_length, &cub.img->endian); 
	cub = initialize(&cub);
	square2(&cub);
    mlx_put_image_to_window(cub.img->mlx, cub.img->win1, cub.img->img1, 400, 400);

	mlx_loop(cub.img->mlx);
}
