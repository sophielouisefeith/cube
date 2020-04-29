/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 10:23:38 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/04/29 14:41:38 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void  ft_locate_sprites(t_build *build)
{
    int x;
    int y;
    int i;
    
    i = 0;
    y = 0;
    while (y < 24) //mapheight
    {
        x = 0;
        while (x < 24) // mapwidth
        {
          if (build->map.array[y][x] == 2)
          {
            mlx->sprites_tab[i].x = y + 0.5;
            mlx->sprites_tab[i].y = x + 0.5;
            i++;
          }
          x++;
        }
        y++;
    }
}


static char  *sprite_chose(t_build *build)
{
    
    return(build->data.sprite);
}

static int makesprite(t_build *build)
{
    char *path;

    path = sprite_chose(build);
    
    build->sprite.sprite = mlx_xpm_file_to_image(build->img.mlx, path, &build->sprite.width, &build->sprite.height);
    build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian);
    
    build->sprite.y = build->sprite.drawstarty;
    while(build->sprite.y < build->sprite.drawendx)
    {
        build->sprite.d = (build->sprite.y) * 256 - build->data.res_y * 128  + build->sprite.spriteheight * 128;
        build->sprite.texy ((build->sprite.d * build->tex.height) / build->sprite.spriteheight) / 256;
        
    }
    
}

static int loop(t_build *build)
{
    build->sprite.stripe = build->sprite.drawstartx;
    while( build->sprite.stripe < build->sprite.drawendx)
    {
        build->sprite.texx = (int)256 * build->sprite.stripe / 2 + build->sprite.spritescreenx;
        if(build->sprite.transformy > 0 && build->sprite.stripe > 0 && build->sprite.stripe < build->data.res_x && build->sprite.transformy < build->sprite.zbuffer[build->sprite.stripe]);
           makesprite(build);
        // build->sprite.stripe++;
    }
}
static char  *sortspirtes(int x, t_build *build)
{
    int i;

    i = 0;
    x = 0;
     while(i < build->sprite.numsprites)
    {
        build->sprite.spriteorder[i] = i;
        build->sprite.spritedistance[i] = 
        ((build->cor.start_pos_x - sprite[i].x) * (build->cor.start_pos_x - sprite[i].x) + (build->cor.start_pos_y - sprite[i].y) * (build->cor.start_pos_y - sprite[i].y));
        i++;
    }
}


void        sprite(t_build *build)
{
   int x;
   int i;
   

   x =0;
   i =0;
   
    build->sprite.numsprites = 19;

    build->sprite.zbuffer[x] = build->ray.perpwalldist;
    sortspirtes(x, build);
    while( i < build->sprite.numsprites)
    {
        build->sprite.spritex = sprite[build->sprite.spriteorder[i]].x - build->cor.start_pos_x;
        build->sprite.spritey = sprite[build->sprite.spriteorder[i]].x - build->cor.start_pos_y;
        build->sprite.invdet = 1.0 / (build->ray.planex * build->cor.diry -build->cor.dirx * build->ray.planey);
        build->sprite.transformx = build->sprite.invdet * (build->cor.diry - build->cor.dirx * build->sprite.spritey);
        build->sprite.transformy = build->sprite.invdet * (-build->ray.planey * build->sprite.spritex + build->ray.planex * build->sprite.spritey);
        build->sprite.spritescreenx = (int)build->data.res_x / 2 * (1 + build->sprite.transformx / build->sprite.transformy);
        build->sprite.spriteheight = (int)build->data.res_y / build->sprite.transformy; // ik heb hier nu geen abs voorgezet even aan maran vragen 
        build->sprite.drawstarty = -build->sprite.spriteheight / 2 + build->data.res_y / 2;
        if(build->sprite.drawstarty < 0 )
            build->sprite.drawendy = build->sprite.spriteheight / 2 + build->data.res_y / 2;
        if(build->sprite.drawstarty >= build->data.res_y)
             build->sprite.drawendy = build->data.res_y - 1;
        build->sprite.spritewidth = (int)build->data.res_y / ( build->sprite.transformy);
        build->sprite.drawstartx = -build->sprite.spritewidth / 2 + build->sprite.spritescreenx;
        if(build->sprite.drawstartx < 0)
            build->sprite.drawstartx = 0;
        build->sprite.drawendx = build->sprite.spritewidth / 2 + build->sprite.spritescreenx;
        if(build->sprite.drawendx >= build->data.res_x -1);
        loop(build);
        build->sprite.stripe++;
        
        
        i++; 
    }
    
    
}