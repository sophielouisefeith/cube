/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/19 10:31:03 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/28 13:40:01 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int      put(int x, t_build *build)
{
    int y;
    int color;
    y = build->ray.drawstart;
    while(y < build->ray.drawend)
    {
        build->tex.texy = (int)build->tex.texpos & (63);
        build->tex.texpos += build->tex.step;
        color = *(unsigned int*)(build->tex.dataadres + (build->tex.texy * build->tex.line_length + build->tex.texx * (build->tex.bpp / 8)));
        if(build->ray.side == 1)
            color = (color >> 1) & 8355711;
     my_mlx_pixel_put(build, x, y, color);
     y++;
    }
    
    return(0);
    
}
static int      calc(t_build *build)
{
     // build->tex.texx = 0;
    // build->tex.step = 0;
    // build->tex.texpos = 0;
    // build->tex.texy = 0;
    build->tex.texnum = build->map.array[(int)build->cor.start_pos_x][(int)build->cor.start_pos_y] -1;
    if (build->ray.side == 0)// 
       build->tex.wallx = build->cor.start_pos_y + build->ray.perpwalldist * build->ray.raydiry;
    else
        build->tex.wallx = build->cor.start_pos_x + build->ray.perpwalldist * build->ray.raydirx;
    build->tex.wallx -= floor((build->tex.wallx));
    build->tex.texx = (build->tex.wallx * (double)64);
    if (build->ray.side == 0 && build->ray.raydirx > 0)
        build->tex.texx = 64 - build->tex.texx -1;
    if (build->ray.side == 1 && build->ray.raydiry < 0)
        build->tex.texx = 64 - build->tex.texx -1;
    build->tex.step = 1.0 * 64 / build->ray.lineheight;
    build->tex.texpos = (build->ray.drawstart - build->data.res_y / 2 + build->ray.lineheight / 2 * build->tex.step);
    return(0);
}

char    *wall_direction(t_build *build)
{
  if (build->ray.side == 1)
  {
    if (build->ray.raydiry < 0)
      return (build->data.north);
    else
      return (build->data.south);
  }
  if (build->ray.side == 0)
  {
    if (build->ray.raydirx < 0)
      return (build->data.west);
    else
        return (build->data.east);
  }
  return(NULL);
}
static int      make_tex(char *path, t_build *build)
{
  //  if(path == build->data.north)
        build->tex.texture = mlx_xpm_file_to_image(build->img.mlx, path, &build->tex.width, &build->tex.height);
        build->tex.dataadres = mlx_get_data_addr(build->tex.texture, &build->tex.bpp, &build->tex.line_length, &build->tex.endian);
    // if(path == build->data.west)
    //     build->tex.texture_w = mlx_xpm_file_to_image(build->img.mlx, path, &build->tex.width, &build->tex.height);
    //     build->tex.dataadres = mlx_get_data_addr(build->tex.texture_w, &build->tex.bpp, &build->tex.line_length, &build->tex.endian);
    return(0);
}

int     fill(int x, t_build *build)
{
	// int rgb;
	// rgb = 0xffe4e1;
	// if (build->ray.side == 1)
	// 	rgb = rgb /2;
    calc(build);
    // int y;
    // int color;
    // y = build->ray.drawstart; 
    char *path;
    path = wall_direction(build);
    make_tex(path, build);
   // make_tex(build->data.north, build);
    put(x, build);
    // make_tex(build->data.west, build);
    // put(x, build);
   // make_tex(build->data.east, build);
    //put(x, build);
   // make_tex(build->data.south, build);
    //put(x, build);
//    while(y < build->ray.drawend)
//    {
//         build->tex.texy = (int)build->tex.texpos & (63);
//         build->tex.texpos += build->tex.step;
//         color = *(unsigned int*)(build->tex.dataadres + (build->tex.texy * build->tex.line_length + build->tex.texx * (build->tex.bpp / 8)));
//         if(build->ray.side == 1)
//             color = (color >> 1) & 8355711;
//      my_mlx_pixel_put(build, x, y, color);
//      y++;
//     }
    return(0);    
}




   // while (y < build->data.res_y)
    //     y++;
    // while ( x < build->data.res_x)
    //     x++;

    //printf("drawstart: %d\n", build->ray.drawstart);
	// while(build->ray.drawstart < build->ray.drawend)
	// {
       
	// 	my_mlx_pixel_put(build, x, build->ray.drawstart, rgb);
	// 	build->ray.drawstart++;
	// }
// int             floor_ceiling(t_build *build)
// {

//     int y;

//     y = 0;
//     int x;
    
//     x = 0;
//     int color;
//     // build->img.floor = mlx_new_image(build->img.mlx, build->data.res_x, build->data.res_y); // dit moet waarschijnlijk verplaats worden 
// 	// build->img.fill = mlx_get_data_addr(build->img.floor, &build->img.bits_per_pixel, &build->img.line_length, &build->img.endian);
//     while( y < build->data.res_y)
//     {
//         float raydirx0 = build->cor.dirx - build->ray.planex;
//         float raydiry0 = build->cor.diry - build->ray.planey;
//         float raydirx1 = build->cor.dirx - build->ray.planex;
//         float raydiry1 = build->cor.diry - build->ray.planey;
    
//         int p = y - build->data.res_y  / 2 ; //let even op deze screenheight.
//         float posz = 0.5 * build->data.res_y;
//         float rowdistance = posz / p;
//         float floorstepx = rowdistance * ( raydirx1 - raydirx0) / build->data.res_x; // screenwidth
//         float floorstepy = rowdistance * (raydiry1 - raydiry0) / build->data.res_y;
    
//         float floorx  = build->cor.start_pos_x + rowdistance * raydirx0;
//         float floory  = build->cor.start_pos_y + rowdistance * raydiry0;
//        //y++;
    
       
//         while ( x < build->data.res_x)
//         {
//         //    int cellx = (int)(floorx);
//         //     int celly = (int)(floory);
//         //     int px  = (int)(64 * (floorx - cellx ));
//         //    int py  = (int)(64 * (floory - celly ));
//             floorx += floorstepx;
//             floory += floorstepy;

//             color = build->data.ceiling;
//             color = build->data.floor;
//         // printf("color: %d", build->data.ceiling);
//         // printf("kom je hier");
            
//         }
//         my_mlx_pixel_put(build, x, y, color);
//         y++;
//         x++;
    
//     }
//     return(0);
// }

// res /2 pixep put en kleurtje. dat word groote. 