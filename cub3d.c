/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:53:05 by sfeith         #+#    #+#                */
/*   Updated: 2020/02/28 18:36:44 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_west(t_cub *cub)
{
	cub->var.x--;
	return ;
}

void	move_east(t_cub *cub)
{
	cub->var.x++;
	square(cub);
	mlx_put_image_to_window(cub->img->mlx, cub->img->win1, cub->img->img1, 0, 0);
	return ;
}

int		pressed_key(int keycode, t_cub *cub)
{

	if (keycode == 13)			//W
		move_west(cub);
	if (keycode == 14)			//E
		move_east(cub);
	// if (keycode == 1)			//S
	// if (keycode == 45)			//N
	return (0);
}

void    square(t_cub *cub)
{
	int y = cub->var.y;			
	int x = cub->var.x;			
	int width = x + 200;		
	int heigth = y + 200;		
	while (y <= heigth)
	{
		x = cub->var.x;
		while (x <= width && x < 750)
		{
			
			my_mlx_pixel_put(cub, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	return ;
}

t_cub	initialize(t_cub *cub)
{
	cub->var.x = 10000;
	cub->var.y = 10000;
	return(*cub);
}

int main()
{
    t_cub	cub;
	t_img	img;

	cub.img = &img;

	cub.var.x = 50;
	cub.var.y = 0;
    cub.img->mlx = mlx_init();
    cub.img->win1 = mlx_new_window(cub.img->mlx, 750, 750, "start");
   	cub.img->img1 = mlx_new_image(cub.img->mlx, 650, 650);
	cub.img->addr = mlx_get_data_addr(cub.img->img1, &cub.img->bits_per_pixel, &cub.img->line_length, &cub.img->endian); 
	cub = initialize(&cub);
	square(&cub);
    mlx_put_image_to_window(cub.img->mlx, cub.img->win1, cub.img->img1, 500, 500);
    mlx_hook(cub.img->win1, 2, 1L<<0, pressed_key, &cub);
	mlx_loop(cub.img->mlx);
}
