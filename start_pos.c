/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_pos.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 12:34:46 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/07 18:28:40 by SophieLouis   ########   odam.nl         */
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

