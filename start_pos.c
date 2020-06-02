/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_pos.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 12:34:46 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/05/26 15:37:34 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void  direction(int y, int x, t_build *build)
{
    if(build->map.array[y][x] == 'N')
    {
        printf("noord\n");
        build->cor.dirx = 0;
        build->cor.diry = -1; //-1
    }
    if(build->map.array[y][x] == 'E')
    {
        printf("east\n");
        build->cor.dirx = 1;
        build->cor.diry = 0;
    }
    if(build->map.array[y][x] == 'S')
    {
        printf("zuid\n");
        build->cor.dirx = 0;
        build->cor.diry = 1; //1
        build->ray.x_cam = 1;
    }
    if(build->map.array[y][x] == 'W')
    {
        build->cor.dirx = -1;
        build->cor.diry = 0;
        build->ray.x_cam = 1;
    }
}

static void sprite_cor(t_build *build)
{
    int x;
    int y;
    int i;
    
    y = 0;
    i = 0;
   
    printf("spritenum %d\n", build->sprite.num);
    if(!(build->sprite_s->sprite_cor = (double **)malloc(sizeof(double *) * build->sprite.num)))
        error("malloc failed");
    while(build->map.array[y] != NULL)
    {
        x = 0;
        while (build->map.array[y][x])
        {
            if(build->map.array[y][x] == '2')
            {
                build->sprite_s->sprite_cor[i] = malloc(sizeof(int) * 2);
                build->sprite_s->sprite_cor[i][0] = x;
                build->sprite_s->sprite_cor[i][1] = y;
                i++;
            
            }
            x++;
        }
        y++;
    
    }
    // build->sprite.num = i -1;
}
void    start_pos(int y, t_build *build)
{
    int x;
   
    
    x = 0;
    while( build->map.array[y][x])
    {
        if(build->map.array[y][x] == 'W' || build->map.array[y][x] == 'E'||
        build->map.array[y][x] == 'N' || build->map.array[y][x] == 'S')
        {
            build->cor.start_pos_x = x + 0.5;
            build->cor.start_pos_y = y + 0.5;
            build->data.count++;
            direction(y, x, build);
        }
        if(build->data.count > 1)
            error("to many start positonions \n");
        if(build->map.array[y][x] == '2')
            build->sprite.num++;
        x++; 
    }
    sprite_cor(build);
}