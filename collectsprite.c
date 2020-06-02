/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collectsprite.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/13 14:56:03 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/05/13 15:15:47 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void collectsprite(t_build *build)
{
    int x;
    int y;

    y = 0;
    x = 0;
    int **spritecor;
    build->sprite_s->sprite_cor = (double **)malloc((sizeof(double*) * build->sprite.num * 2));
    if(build->map.array[y][x] == '2')
    {
            // build->sprite_s[build->sprite.num].x = y + 0.5; 
            // build->sprite_s[build->sprite.num].y = x + 0.5;
     }
}