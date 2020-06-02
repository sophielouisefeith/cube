/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainread.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:55:17 by sfeith         #+#    #+#                */
/*   Updated: 2020/06/02 15:51:15 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int main(int argc, char **argv)
// {
//---------------------------------step1----------------------------------------------
//first we will call the function savearray to open the map.cub this function reads the map----------------------------------------------
//and to return the map as an 3darray
	
int main(int argc, char **argv)
{
    t_build	*build;
	//t_img	img;
	if(argc != 2)
		error("to many arguments"); 
	build = savearray(argv[1]);
	//build->img = &img; // ------------------  dit zou het kunnen zijn---------- //zou het iets te maken kunnen hebben met img1
	read_string(build);
	startgame(build);
	return(0);
}






// int main(int argc, char **argv)
// {
    // t_build	*build;
	// t_img	img;
	

	// if(argc != 2)
	// 	error("to many arguments");  
	// build = savearray(argv[1]); 
	// build->img = &img;
	// read_string(build); 

    // build->img->mlx = mlx_init();
    // build->img->win = mlx_new_window(build->img->mlx, build->data.res_x, build->data.res_y, "start");
   	// // build->img->img1 = mlx_new_image(build->img->mlx, build->data.res_x, build->data.res_y); // dit moet waarschijnlijk verplaats worden 
	// // build->img->addr = mlx_get_data_addr(build->img->img1, &build->img->bits_per_pixel, &build->img->line_length, &build->img->endian); // dit moet waarschijnlijk verplaats worden 
	// mlx_hook(build->img->win, 2, 1L<<0, &presskey, build);
	// mlx_loop_hook(build->img->mlx, &make, build); 
	// // mlx_put_image_to_window(build->img->mlx, build->img->win, build->img->img1, 0, 0);
	// mlx_loop(build->img->mlx);





	
	// t_build *build;
	// // t_data 	*data;
	
	// if(argc != 2)
	// 	return(-1);  //ERROR nog functie voor maken
	// build = savearray(argv[1]);
	// int y;

	// y = 0;
	// while (build->map.array[y] != NULL)
	// {
	// 	printf("3darray[%s]\n", build->map.array[y]);
	// 	y++;
	// }
//	return(build->map.array);
	// while (1){}  
//---------------------------------step2----------------------------------------------
//now we have to safe the data of the array and check on cases. 

	//read_string(build);
	//printf("resolution:		res_x[%d]res_y[%d]\n", build->data.res_x, build->data.res_y);
	//printf("floor color:		[%d]\n", build->data.floor);
	//printf("check:	[%d]\n", build->data.check_color);
	// printf("r[%d]\n", build->data.color_r);
	// printf("g[%d]\n", build->data.color_g);
	// printf("b[%d]\n", build->data.color_b);
	//printf("floor color[%d]\n", build->data.floor);
	//printf("check:	[%d]\n", build->data.check_color);
	//printf("ceiling color:		[%d]\n", build->data.ceiling);
	//printf("r[%d]\n", build->data.color_r);
	//printf("g[%d]\n", build->data.color_g);
	//printf("b[%d]\n", build->data.color_b);
	//printf("ceiling color[%d]\n", build->data.ceiling);
	// printf("sprite:		[%s]\n", build->data.sprite);
	// printf("north:		[%s]\n", build->data.north);
	// printf("south:		[%s]\n", build->data.south);
	// printf("west:		[%s]\n", build->data.west);
	// printf("east:		[%s]\n", build->data.east);

// 	return (0);
// }
//---------------------------------step3----------------------------------------------
//we are going to ray cast

