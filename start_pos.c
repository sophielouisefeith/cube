/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_pos.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 12:34:46 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/16 20:50:37 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void  direction(int y, int x, t_build *build)
{
    if(build->map.array[y][x] == 'N')
        build->cor.dirx = 0;
        build->cor.diry = -1;
    if(build->map.array[y][x] == 'E')
        build->cor.dirx = 1;
        build->cor.diry = 0;
    if(build->map.array[y][x] == 'Z')
        build->cor.dirx = 0;
        build->cor.diry = 1;
    if(build->map.array[y][x] == 'W')
        build->cor.dirx = -1;
        build->cor.diry = 0;
  
}

void    start_pos(int y, t_build *build)
{
    int x;

    x = 0;
    while( build->map.array[y][x])
    {
        if(build->map.array[y][x] == 'N' || build->map.array[y][x] == 'E' ||
        build->map.array[y][x] == 'Z' || build->map.array[y][x] == 'W')
        {
            build->cor.start_pos_x = x;
            build->cor.start_pos_y = y;
            build->data.count++;
            direction(y, x, build);
        }
        if(build->data.count > 1)
            error("to many start positonions \n");
        x++; 
    }
}

// int    presskey(int keycode, t_build *build)
// {

//     build->ray.moveup = 0;
// 	build->ray.movedown = 0;
// 	build->ray.moveright = 0;
// 	build->ray.moveleft = 0;
//     build->ray.update = 0;
//     printf("presskey");
    
//     if(keycode == 13)
//     {
//         printf("W");
//         build->ray.moveup = 1;
//         // build->ray.update = 1;
//     }
//     if(keycode == 1)
//         build->ray.movedown = 1 ;
//     if(keycode == 0)
//         build->ray.moveleft = 1 ;
//     if(keycode == 2 )
//         build->ray.moveright = 1;
//     return(0);
// }