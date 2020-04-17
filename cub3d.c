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
	build->img.img1 = mlx_new_image(build->img.mlx, build->data.res_x, build->data.res_y); // dit moet waarschijnlijk verplaats worden 
	build->img.addr = mlx_get_data_addr(build->img.img1, &build->img.bits_per_pixel, &build->img.line_length, &build->img.endian);
	if(build->ray.update)
	{
		printf("update\n");
		move(build);
	}
	//printf("de waarde van update: %d\n", build->ray.update);
	ray(build);
	build->ray.update = 0;
	return (0);
}

int startgame(t_build *build)
{
	build->img.mlx = mlx_init();
	build->img.win = mlx_new_window(build->img.mlx, build->data.res_x, build->data.res_y, "WOLFENSTEIN");
	mlx_hook(build->img.win, 2, 1L<<0, &presskey, build);
	mlx_loop_hook(build->img.mlx, make, build); 
	mlx_loop(build->img.mlx);
	return(0);
}






































// int main(int argc, char **argv)
// {
//     t_build	*build;
// 	//t_img	img;
// 	if(argc != 2)
// 		error("to many arguments");  
// 	build = savearray(argv[1]); 
// 	//build->img = &img; // ------------------  dit zou het kunnen zijn---------- //zou het iets te maken kunnen hebben met img1
// 	read_string(build);
//     build->img.mlx = mlx_init();
// 	build->img.win = mlx_new_window(build->img.mlx, build->data.res_x, build->data.res_y, "WOLFENSTEIN");
// 	mlx_hook(build->img.win, 2, 1L<<0, &presskey, build);
// 	mlx_loop_hook(build->img.mlx, make, build); 
// 	mlx_loop(build->img.mlx);
// 	return(0);
// }







// int				make(t_build *build)
// {

// 	build->img.img1 = mlx_new_image(build->img.mlx, build->data.res_x, build->data.res_y); // dit moet waarschijnlijk verplaats worden 
// 	build->img.addr = mlx_get_data_addr(build->img.img1, &build->img.bits_per_pixel, &build->img.line_length, &build->img.endian); // dit moet waarschijnlijk verplaats worden 

// 	ray(build);
// 	move(build);
	// int x;
	// double camerax;
	// double raydirx;
	// double raydiry;

	// x = 0;
	// build->ray.planex = 0;
	// build->ray.planey = 0.66;

	
	// while (x < build->data.res_x)  
	// {
	// 	camerax = 2 * x / build->data.res_x  - 1;
	// 	raydirx = build->cor.dirx + build->ray.planex * camerax;
	// 	raydiry = build->cor.diry + build->ray.planey * camerax;
	// 	build->cor.mapx = (int)build->cor.start_pos_x;
	// 	build->cor.mapy = (int)build->cor.start_pos_y;
	// 	double sidedistx;
    // 	double sidedisty;
	// 	double deltadistx =  fabs(1 / raydirx);
    // 	double deltadisty = fabs(1 / raydiry);
	// 	double perpwalldist;
	// 	int stepx;
	// 	int stepy;
	// 	int hit = 0;
	// 	int side;
	// 	if ( raydirx < 0)
	// 	{

	// 		stepx = -1;
	// 		sidedistx = (build->cor.start_pos_x - build->cor.mapx) * deltadistx;
	// 	}
	// 	else
	// 	{
	// 		stepx = 1;
	// 		sidedistx = (build->cor.mapx + 1.0 - build->cor.start_pos_x) * deltadistx;
	// 	}
	// 	if (raydiry < 0 )
	// 	{
	// 		stepy = -1;
	// 		sidedisty = (build->cor.start_pos_y - build->cor.mapy) * deltadisty;
	// 	}
	// 	else
	// 	{
	// 		stepy = 1;
	// 		sidedisty = (build->cor.mapy + 1.0 - build->cor.start_pos_y) * deltadisty;
	// 	}
	// 	while ( hit == 0)
	// 	{
	// 		if (sidedistx < sidedisty)
	// 		{
	// 			sidedistx += deltadistx;
	// 			build->cor.mapx += stepx;
	// 			side = 0;
	// 		}
	// 		else
	// 		{
	// 			sidedisty += deltadisty;
	// 			build->cor.mapy += stepy;
	// 			side = 1;
	// 		}
	// 		if (build->map.array[build->cor.mapy][build->cor.mapx] == '1') 
	// 			hit = 1;
	// 	}
	// 	if( side == 0)
	// 		perpwalldist = (build->cor.mapx - build->cor.start_pos_x + (1 - stepx) / 2) / raydirx;
			
			
	// 	else
	// 		perpwalldist = (build->cor.mapy - build->cor.start_pos_y + (1 - stepy) / 2) / raydiry;
	// 		//printf("perpwalldist [%f] \n", perpwalldist);
	// 	//printf("perpwalldist [%f] \n", perpwalldist);
	// 	int lineheight = (int)(build->data.res_y/ perpwalldist);
	// 	//printf("lineheight [%d] \n", lineheight);
	// 	//printf("res_Y [%f]\n",build->data.res_y );
		
	// 	int drawstart = -lineheight / 2 + build->data.res_y / 2;
	// 	if (drawstart < 0) 
	// 		drawstart = 0;
	// 	int drawend = lineheight /2 + build->data.res_y / 2;
	// 	if (drawend >= build->data.res_y )
	// 		drawend = build->data.res_y - 1;
	// 	//printf("drawstart [%d] en drawend [%d]\n", drawstart, drawend);
	// 	int rgb;
	// 	rgb = 0xffe4e1;
	// 	if (side == 1)
	// 		rgb = rgb /2;
	// 	//printf("drawstart [%d] en drawend [%d]\n", drawstart, drawend);
	// 	while(drawstart < drawend)
	// 	{
	// 		my_mlx_pixel_put(build, x, drawstart, rgb);
	// 		drawstart++;
	// 	}
		//move(build);
		// build->ray.oldtime = build->ray.time;
		// build->ray.time = clock();
		// build->ray.frametime = (build->ray.time - build->ray.oldtime) / 1000.0;
		// //print(1.0 / build->ray.frametime);
		// //redraw;
		// //cls();

		// build->ray.movespeed = build->ray.frametime * 5.0;
		// build->ray.rotspeed = build->ray.frametime * 3.0;

		// //readkeys waarschijnlijk word dit dus een apparte functie

		// //moveforward 
		// if(build->ray.moveup == 1)
		// {
		// 	if(build->map.array[(int)(build->cor.start_pos_x + build->cor.dirx * build->ray.movespeed)]
		// 	[(int)(build->cor.start_pos_y)] == '0')
		// 		build->cor.start_pos_x += build->cor.dirx * build->ray.movespeed;
		// 	if(build->map.array[(int)(build->cor.start_pos_x)]
		// 	[(int)(build->cor.start_pos_y + build->cor.diry * build->ray.movespeed)] == '0')
		// 		build->cor.start_pos_y += build->cor.diry * build->ray.movespeed;
		// 	build->ray.moveup = 0;

		// }
		// if(build->ray.movedown == 1)
		// {
		// 	if(!build->map.array[(int)(build->cor.start_pos_x - build->cor.dirx * build->ray.movespeed)]
		// 	[(int)build->cor.start_pos_y])
		// 		build->cor.start_pos_x -= build->cor.dirx * build->ray.movespeed;
		// 	if(!build->map.array[(int)build->cor.start_pos_x]
		// 	[(int)(build->cor.start_pos_y - build->cor.diry * build->ray.movespeed)])
		// 		build->cor.start_pos_y -= build->cor.diry * build->ray.movespeed;
		// 	build->ray.movedown = 0;
		// }
		// if(build->ray.moveright == 1)
		// {
		// 	build->ray.oldirx = build->cor.dirx;
		// 	build->cor.dirx = build->cor.dirx * cos(-build->ray.rotspeed) - build->cor.diry * sin(-build->ray.rotspeed);
		// 	build->cor.diry = build->ray.oldirx * sin(-build->ray.rotspeed) + build->cor.diry * cos(-build->ray.rotspeed);
		// 	build->ray.oldplanex = build->ray.planex;
		// 	build->ray.planex = build->ray.planex * cos(-build->ray.rotspeed) - build->ray.planey * sin(-build->ray.rotspeed);
		// 	build->ray.planey = build->ray.oldplanex * sin(-build->ray.rotspeed) + build->ray.planey * cos(-build->ray.rotspeed);
		// }
		// if(build->ray.moveleft == 1)
		// {
		// 	build->ray.oldirx = build->cor.dirx;
		// 	build->cor.dirx = build->cor.dirx * cos(build->ray.rotspeed) - build->cor.diry * sin(build->ray.rotspeed);
		// 	build->cor.diry = build->ray.oldirx * sin(build->ray.rotspeed) + build->cor.diry * cos(build->ray.rotspeed);
		// 	build->ray.oldplanex = build->ray.planex;
		// 	build->ray.planex = build->ray.planex * cos(build->ray.rotspeed) - build->ray.planey * sin(-build->ray.rotspeed);
		// 	build->ray.planey = build->ray.oldplanex * sin(-build->ray.rotspeed) + build->ray.planey * cos(-build->ray.rotspeed);
		// }
		//mlx_put_image_to_window(build->img.mlx, build->img.win, build->img.img1, 0, 0);
		//x++;
	// }
	//return (0);
//}