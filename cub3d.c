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
	int x;
	double planex;
	double planey;
	double camerax;
	double raydirx;
	double raydiry;

	// double time;
	// double oldtime;

	x = 0;
	planex = 0;
	planey = 0.66;

	// pos x build->cor.start_pos_y   // n.s.w.e  de coordinaten aan de struct koppelen 
	while (x < build->data.res_x)  
	{
		camerax = 2 * x / build->data.res_x  - 1;
		raydirx = build->cor.dirx + planex * camerax;
		raydiry = build->cor.diry + planey * camerax;
		//printf("raydiry[%f]\n", raydiry);
		// which box of the map we're in
  		// printf("x[%d]\n", build->cor.start_pos_x );
   		// printf("y[%d]\n", build->cor.start_pos_y );
		build->cor.mapx = (int)build->cor.start_pos_x;
		build->cor.mapy = (int)build->cor.start_pos_y;
		//printf("build->cor.mapx0 [%d], build->cor.start_pos_x[%f] \n", build->cor.mapx, build->cor.start_pos_x);
		double sidedistx;
    	double sidedisty;
		//length of ray from current position to next x or y-side
		//length of ray from one x or y-side to next x or y-side
		double deltadistx =  fabs(1 / raydirx);
    	double deltadisty = fabs(1 / raydiry);
		//printf("deltasdisty [%f]\n", deltadisty);
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
		//printf("build->cor.mapx1 [%d], build->cor.start_pos_x[%f] \n", build->cor.mapx, build->cor.start_pos_x);
		//printf("step1 [%d] \n", stepx);
		//printf("build->cor.mapx2 [%d], build->cor.start_pos_x[%d], stepx [%d], raydirx[%f], raydiry[%f] \n", build->cor.mapx, build->cor.start_pos_x, stepx, raydirx, raydiry);
		while ( hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				//printf("kom je hier");
				sidedistx += deltadistx;
				build->cor.mapx += stepx;
				side = 0;
				//printf("build->cor.mapx2 [%d], build->cor.start_pos_x[%f] \n", build->cor.mapx, build->cor.start_pos_x);
			}
			else
			{
				sidedisty += deltadisty;
				build->cor.mapy += stepy;
				side = 1;
				//printf("build->cor.mapx3 [%d], build->cor.start_pos_x[%f] \n", build->cor.mapx, build->cor.start_pos_x);
			}
			if (build->map.array[build->cor.mapy][build->cor.mapx] == '1') 
				hit = 1;
		}
		//printf("build->cor.mapx2 [%d], build->cor.start_pos_x[%f], stepx [%d], raydirx[%f], \n", build->cor.mapx, build->cor.start_pos_x, stepx, raydirx);
		if( side == 0)
			perpwalldist = (build->cor.mapx - build->cor.start_pos_x + (1 - stepx) / 2) / raydirx;
			
			
		else
			perpwalldist = (build->cor.mapy - build->cor.start_pos_y + (1 - stepy) / 2) / raydiry;
			//printf("perpwalldist [%f] \n", perpwalldist);
		//printf("perpwalldist [%f] \n", perpwalldist);
		int lineheight = (int)(build->data.res_y/ perpwalldist);
		//printf("lineheight [%d] \n", lineheight);
		//printf("res_Y [%f]\n",build->data.res_y );
		
		int drawstart = -lineheight / 2 + build->data.res_y / 2;
		if (drawstart < 0) 
			drawstart = 0;
		int drawend = lineheight /2 + build->data.res_y / 2;
		if (drawend >= build->data.res_y )
			drawend = build->data.res_y - 1;
		//printf("drawstart [%d] en drawend [%d]\n", drawstart, drawend);
		int rgb;
		rgb = 0xffe4e1;
		if (side == 1)
			rgb = rgb /2;
		//printf("drawstart [%d] en drawend [%d]\n", drawstart, drawend);
		while(drawstart < drawend)
		{
			//printf("halo");
			my_mlx_pixel_put(build, x, drawstart, rgb);
			drawstart++;
		}
		//hier komst straks de time and speed modefiers.
		//key down and up komt ook later 
		//printf("x [%d]\n", x);
		x++;
	}
	// w  mijn res_x en de h = res_y
	//x = x + 1;
	//x +=1;
	//mlx_put_image_to_window(build->img->mlx, build->img->win1, build->img->img1, 600, 600);
	return (0);
}

int main(int argc, char **argv)
{
    t_build	*build;
	t_img	img;
	

	if(argc != 2)
		return(-1);  //ERROR nog functie voor maken
	build = savearray(argv[1]); // hierin lezen we de map 
	build->img = &img;
	read_string(build); // hierin slaan we alle data op 
	//*build = initialize(build);

    build->img->mlx = mlx_init();
    build->img->win1 = mlx_new_window(build->img->mlx, build->data.res_x, build->data.res_y, "start");
   	build->img->img1 = mlx_new_image(build->img->mlx, build->data.res_x, build->data.res_y); // dit moet waarschijnlijk verplaats worden 
	build->img->addr = mlx_get_data_addr(build->img->img1, &build->img->bits_per_pixel, &build->img->line_length, &build->img->endian); // dit moet waarschijnlijk verplaats worden 
	//image(build);
	mlx_loop_hook(build->img->mlx, &make, build); // addres misschien nodig voor make &make als we gaan wandelen 
	mlx_put_image_to_window(build->img->mlx, build->img->win1, build->img->img1, 0, 0);
	// mlx_put_image_to_window(build->img->mlx, build->img->win1, build->img->img1, 400, 400);
	mlx_loop(build->img->mlx);
}











// void	move_west(t_build *build)
// {
// 	build->cor.x--;
// 	return ;
// }

// void	move_east(t_build *build)
// {
// 	build->cor.x++;
// 	square(build);
// 	mlx_put_image_to_window(build->img->mlx, build->img->win1, build->img->img1, 0, 0);
// 	return ;
// }

// int		pressed_key(int keycode, t_build *build)
// {

// 	if (keycode == 13)			//W
// 		move_west(build);
// 	if (keycode == 14)			//E
// 		move_east(build);
// 	// if (keycode == 1)			//S
// 	// if (keycode == 45)			//N
// 	return (0);
// }

// void    square(t_build *build)
// {
// 	int y = build->cor.y;			
// 	int x = build->cor.x;			
// 	int width = x + 200;		
// 	int heigth = y + 200;		
// 	while (y <= heigth)
// 	{
// 		x = build->cor.x;
// 		while (x <= width && x < 750)
// 		{
			
// 			my_mlx_pixel_put(build, x, y, 0x000530FF);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return ;
// }

// t_build	initialize(t_build *build)
// {
// 	build->cor.x = 10000;
// 	build->cor.y = 10000;
// 	return(*build);
// }

// int main()
// {
//     t_build	build;
// 	t_img	img;

// 	build->img = &img;

// 	build->cor.x = 50;
// 	build->cor.y = 60;
//     build->img->mlx = mlx_init();
//     build->img->win1 = mlx_new_window(build->img->mlx, 750, 750, "het vierkantje");
//    	build->img->img1 = mlx_new_image(build->img->mlx, 650, 650);
// 	build->img->addr = mlx_get_data_addr(build->img->img1, &build->img->bits_per_pixel, &build->img->line_length, &build->img->endian); 
// 	build = initialize(&build);
// 	square(&build);
//     mlx_put_image_to_window(build->img->mlx, build->img->win1, build->img->img1, 500, 500);
//     mlx_hook(build->img->win1, 2, 1L<<0, pressed_key, &build);
// 	mlx_loop(build->img->mlx);
// }
