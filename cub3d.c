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

// void    image(t_build *build)
// {
// 	int y = build->cor.y;			
// 	int x = build->cor.x;			
// 	int width = x + 100;		
// 	int heigth = y + 100;
// 	int color;

// 	color = 0x48d1cc;		
// 	while (y <= heigth)
// 	{
// 		x = build->cor.x;
// 		while (x <= width && x < 450)
// 		{
			
// 			my_mlx_pixel_put(build, x, y, color);
// 			x++;
// 			color++;
// 		}
// 		y++;
// 		color++;
// 	}
// 	return ;
// }

// t_build	initialize(t_build *build)
// {
// 	build->cor.x = 70;
// 	build->cor.y = 70;
// 	return(*build);
// }


int				make(t_build *build)
{

	int x;
	double posx;
	double posy;
	double dirx;
	double diry;
	double planex;
	double planey;
	double camerax;
	double raydirx;
	double raydiry;
	int mapx;
	int mapy;
	double sidedistx;
    double sidedisty;
	double perpwalldist;
	int stepx;
	int stepy;
	int hit;
	int side;

	// double time;
	// double oldtime;

	x = 0;
	posx = 3;
	posy = 14;
	dirx = -1;
	diry = 0;
	planex = 0;
	planey = 0.66;
	camerax = 0;
	raydirx = 0;
	raydiry = 0;
	mapx = 0;
	mapy = 0;
	sidedistx = 0;
    sidedisty = 0;
	perpwalldist = 0;
	stepx = 0;
	stepy = 0;
	hit = 0;
	side = 0;
	
	// pos x posy   // n.s.w.e  de coordinaten aan de struct koppelen 
	while (x < build->data.res_x)
	{
		camerax = 2 * x / build->data.res_x  - 1;
		raydirx = dirx + planex * camerax;
		raydiry = diry + planey * camerax;
		// which box of the map we're in
		int mapx = (int)posx;
		int mapy = (int)posy;
		printf("mapx0 [%d], posx[%f] \n", mapx, posx);
		double sidedistx;
    	double sidedisty;
		//length of ray from current position to next x or y-side
		//length of ray from one x or y-side to next x or y-side
		double deltadistx =  fabs(1 / raydirx);
    	double deltadisty = fabs(1 / raydiry);
		printf("deltasdisty [%f]\n", deltadisty);
		double perpwalldist;
		int stepx;
		int stepy;
		int hit = 0;
		int side;
		if ( raydirx < 0)
		{

			stepx = -1;
			sidedistx = (posx - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - posx) * deltadistx;
		}
		if (raydiry < 0 )
		{
			stepy = -1;
			sidedisty = (posy - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - posy) * deltadisty;
		}
		printf("mapx1 [%d], posx[%f] \n", mapx, posx);
		printf("step1 [%d] \n", stepx);
		printf("mapx2 [%d], posx[%f], stepx [%d], raydirx[%f], raydiry[%f] \n", mapx, posx, stepx, raydirx, raydiry);
		while ( hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
				//printf("mapx2 [%d], posx[%f] \n", mapx, posx);
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
				//printf("mapx3 [%d], posx[%f] \n", mapx, posx);
			}
			if (build->map.array[mapy][mapx] == '1') 
				hit = 1;
		}
		printf("mapx2 [%d], posx[%f], stepx [%d], raydirx[%f], \n", mapx, posx, stepx, raydirx);
		if( side == 0)
			perpwalldist = (mapx - posx + (1 - stepx / 2) / raydirx);
			//printf("perpwalldist [%f] \n", perpwalldist);
		else
			perpwalldist = (mapy - posy + (1 - stepy / 2) / raydiry);
			//printf("perpwalldist [%f] \n", perpwalldist);
		
		int lineheight = (int)(build->data.res_y/ perpwalldist);
		printf("lineheight [%d] \n", lineheight);
		int drawstart = -lineheight / 2 + build->data.res_y/ 2;
		if (drawstart < 0) 
			drawstart = 0;
		int drawend = lineheight /2 + build->data.res_y / 2;
		if (drawend >= build->data.res_y )
			drawend = build->data.res_y - 1;
		int rgb;
		rgb = 0x0000FFFF;
		if (side == 1)
			rgb = rgb /2;
			printf("drawstart [%d] en draweend [%d]\n", drawstart, drawend);
		while(drawstart < drawend)
		{
			my_mlx_pixel_put(build, x, drawend, rgb);
			drawstart++;
		}
		//hier komst straks de time and speed modefiers.
		//key down and up komt ook later 
		printf("x [%d]\n", x);
		x++;
	}
	// w  mijn res_x en de h = res_y
	//x = x + 1;
	//x +=1;
	//mlx_put_image_to_window(build->img->mlx, build->img->win1, build->img->img1, 600, 600);
	return (0);
}

// int		make(t_build *build)
// {
// 	printf("ja");

//   int x = 0;
//   double h = build->data.res_y;
//   double w = build->data.res_x;
//   double posX = 5, posY = 5;  //x and y start position
//   double dirX = -1, dirY = 0; //initial direction vector
//   double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

// //   double time = 0; //time of current frame
// //   double oldTime = 0; //time of previous frame

//   while (x < build->data.res_x)
//   {
//       //calculate ray position and direction
//       double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
//       double rayDirX = dirX + planeX * cameraX;
//       double rayDirY = dirY + planeY * cameraX;
//       //which box of the map we're in
//       int mapX = (int)posX;
//       int mapY = (int)posY;

//       //length of ray from current position to next x or y-side
//       double sideDistX;
//       double sideDistY;

//        //length of ray from one x or y-side to next x or y-side
//  	  double deltaDistX =  fabs(1 / rayDirX);
//       double deltaDistY = fabs(1 / rayDirY);
//       double perpWallDist;

//       //what direction to step in x or y-direction (either +1 or -1)
//       int stepX;
//       int stepY;

//       int hit = 0; //was there a wall hit?
//       int side; //was a NS or a EW wall hit?
//       //calculate step and initial sideDist
//       if(rayDirX < 0)
//       {
//         stepX = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//       }
//       else
//       {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//       }
//       if(rayDirY < 0)
//       {
//         stepY = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//       }
//       else
//       {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//       }
//       //perform DDA
//       while (hit == 0)
//       {
//         //jump to next map square, OR in x-direction, OR in y-direction
//         if(sideDistX < sideDistY)
//         {
//           sideDistX += deltaDistX;
//           mapX += stepX;
//           side = 0;
//         }
//         else
//         {
//           sideDistY += deltaDistY;
//           mapY += stepY;
//           side = 1;
//         }
//         //Check if ray has hit a wall
//         if(build->map.array[mapX][mapY] == '1') 
// 			hit = 1;
      
//       //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
//       	if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
//       	else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

//       //Calculate height of line to draw on screen
//       	int lineHeight = (int)(h / perpWallDist);

//       //calculate lowest and highest pixel to fill in current stripe
//       	int drawStart = -lineHeight / 2 + h / 2;
//       if(drawStart < 0)drawStart = 0;
//       int drawEnd = lineHeight / 2 + h / 2;
//       if(drawEnd >= h)drawEnd = h - 1;

//       //choose wall color
//     //   ColorRGB color;
//     //   switch(worldMap[mapX][mapY])
//     //   {
//     //     case 1:  color = RGB_Red;    break; //red
//     //     case 2:  color = RGB_Green;  break; //green
//     //     case 3:  color = RGB_Blue;   break; //blue
//     //     case 4:  color = RGB_White;  break; //white
//     //     default: color = RGB_Yellow; break; //yellow
//     //   }

//     //   //give x and y sides different brightness
//     //   if(side == 1) {color = color / 2;}
// 		int rgb;
// 		rgb = 0x0000FFFF;
// 		if (side == 1)
// 			rgb = rgb /2;


//       //draw the pixels of the stripe as a vertical line
//     //   verLine(x, drawStart, drawEnd, color);

// 	while(drawStart < drawEnd)
// 	{
// 		my_mlx_pixel_put(build, x, drawEnd, rgb);
// 		drawStart++;
// 	}
    
    // //timing for input and FPS counter
    // oldTime = time;
    // time = getTicks();
    // double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // print(1.0 / frameTime); //FPS counter
    // redraw();
    // cls();

    // //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    // readKeys();
    // //move forward if no wall in front of you
    // if(keyDown(SDLK_UP))
    // {
    //   if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if(keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    // }
    // //rotate to the right
    // if(keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if(keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//     }
//   }
//   x++;
// build->data.res_y = 10;
// 	return (0);
// }

int main(int argc, char **argv)
{
    t_build	*build;
	t_img	img;
	

	if(argc != 2)
		return(-1);  //ERROR nog functie voor maken
	build = savearray(argv[1]);
	build->img = &img;
	read_string(build);
	//*build = initialize(build);

	// build->cor.x = 5;
	// build->cor.y = 11;
    build->img->mlx = mlx_init();
    build->img->win1 = mlx_new_window(build->img->mlx, 1000, 1000, "start");
   	build->img->img1 = mlx_new_image(build->img->mlx, build->data.res_x, build->data.res_y);
	build->img->addr = mlx_get_data_addr(build->img->img1, &build->img->bits_per_pixel, &build->img->line_length, &build->img->endian); 
	//image(build);
	mlx_loop_hook(build->img->mlx, make, build);
	mlx_put_image_to_window(build->img->mlx, build->img->win1, build->img->img1, 400, 400);
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
