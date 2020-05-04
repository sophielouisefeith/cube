/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 10:23:38 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/05/04 12:41:10 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void locate_sprites(t_build *build)
// {
//     printf("kom je hier");
//     int x;
//     int y;
//     int i;
    
//     i = 0;
//     y = 0;
//     x = 0;
   
//     // build->sprite.zbuffer[x] = build->ray.perpwalldist;
//     while (y < build->data.res_y) //mapheight
//     {
//         //x = 0;
//         while (x < build->data.res_x) // mapwidth
//         {
//           if(build->map.array[y][x] == '2')
//           {
//             build->sprite_s[i].x = y + 0.5;
//             build->sprite_s[i].y = x + 0.5;
//             i++;
//           }
//           x++;
//         }
//         y++;
//     }
// }

// static char  *sprite_chose(t_build *build)
// {
//     return(build->data.sprite);
//     //printf("sprite: %s", build->data.sprite);
// }

static void makesprite(t_build *build)
{
    // printf("maken van sprite\n");
    int x;
    //char *path;
    int color;

    x = 0;
    //path = sprite_chose(build);
    //build->sprite.y = build->sprite.drawstarty;
    // build->sprite.sprite = mlx_xpm_file_to_image(build->img.mlx, "./texture/pillar.xpm", &build->sprite.width, &build->sprite.height);
    // build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian);
    //  printf("lengte drawstarty%d\n",build->sprite.drawstarty );
    //  printf("y%d\n",build->sprite.y );
    //  printf("x%d\n",build->sprite.stripe);
    build->sprite.y = build->sprite.drawstarty;  // y = start x = end wat is de start positie hoe sta ik er voor alle waarden even checkken
     printf("lengte drawstarty%d\n",build->sprite.drawstarty );
     printf("y%d\n",build->sprite.y );
     printf("x%d\n",build->sprite.stripe);
    while(build->sprite.y < build->sprite.drawendy) 
    {
        printf("maken van sprite\n");
        build->sprite.d = build->sprite.y * 256 - build->data.res_y * 128  + build->sprite.spriteheight * 128;
        build->sprite.texy = ((build->sprite.d * 64) / build->sprite.spriteheight) / 256;
        color = *(unsigned int*)(build->sprite.dataadres + (build->sprite.texy * build->sprite.line_length + build->sprite.texx * (build->sprite.bpp / 8)));
        my_mlx_pixel_put(build, build->sprite.stripe, build->sprite.y, color); //wat geef je mee voor y, welkle posities neemt hij stripedarwstrartx
        build->sprite.y++;
    }
   // return(0);
}

static int loop(t_build *build)
{
    printf("loop\n");
    build->sprite.stripe = build->sprite.drawstartx; // miss moet dit end zijn 
    while( build->sprite.stripe < build->sprite.drawendx)
    {
        build->sprite.texx = (int)(256 * (build->sprite.stripe - (-build->sprite.spritewidth / 2 + build->sprite.spritescreenx)) * textwidth / build->sprite.spritewidth / 256); //klopt dit
        // build->sprite.y = build->sprite.drawstarty;
        printf("loopen\n");
        if(build->sprite.transformy > 0 && build->sprite.stripe > 0 && build->sprite.stripe < build->data.res_x) //build->sprite.transformy < build->sprite.zbuffer[build->sprite.stripe])
          makesprite(build);
        build->sprite.stripe++;
    }
    return(0);
}
void order_sprites(t_build *build)
{
    
    int i;

    i = 0;
    while(i < numsprites)
    {
        build->sprite.spriteorder[i] = i;
        build->sprite.spritedistance[i] = ((build->cor.start_pos_x - build->sprite_s[i].x) * (build->cor.start_pos_x - build->sprite_s[i].x) + (build->cor.start_pos_y - build->sprite_s[i].y) * (build->cor.start_pos_y - build->sprite_s[i].y));
        i++;
    }
}

void sort_sprites(t_build *build)
{
    //t_sprite      sprite_s[3];
    int i;
    int tmp;
    double tmp2;

    i = 0;
    while ( i < numsprites)
    {
        if (build->sprite.spritedistance[i] < build->sprite.spritedistance[i + 1])
        {
            tmp2 = build->sprite.spritedistance[i + 1];
            build->sprite.spritedistance[i + 1] = build->sprite.spritedistance[i];
            build->sprite.spritedistance[i] = tmp2;
            tmp = build->sprite.spriteorder[i + 1];
            build->sprite.spriteorder[i + 1] = build->sprite.spriteorder[i];
            build->sprite.spriteorder[i] = tmp;
            i = 0;
        }
        else
        i++;  
    }
    
}

void    calc_sprites(t_build *build)
{
    //t_sprite      sprite_s[3];   
    printf("calc\n"); 
    int    x;
    int    i;
    x = 0;
    i = 0;
   // locate_sprites(build);
   // build->sprite.zbuffer[x] = build->ray.perpwalldist;
    while(i < numsprites)
    {
        printf("calcloop\n"); 
        build->sprite.spritex = build->sprite_s[build->sprite.spriteorder[i]].x - build->cor.start_pos_x;
        build->sprite.spritey = build->sprite_s[build->sprite.spriteorder[i]].x - build->cor.start_pos_y;
        build->sprite.invdet = 1.0 / (build->ray.planex * build->cor.diry -build->cor.dirx * build->ray.planey);
        build->sprite.transformx = build->sprite.invdet * (build->cor.diry - build->cor.dirx * build->sprite.spritey);
        build->sprite.transformy = build->sprite.invdet * (-build->ray.planey * build->sprite.spritex + build->ray.planex * build->sprite.spritey);
        build->sprite.spritescreenx = (int)build->data.res_x / 2 * (1 + build->sprite.transformx / build->sprite.transformy);
        build->sprite.spriteheight = abs((int)(build->data.res_y / (build->sprite.transformy))); // ik heb hier nu geen abs voorgezet even aan maran vragen res_y?
        build->sprite.drawstarty = -build->sprite.spriteheight / 2 + build->data.res_y / 2;
        if(build->sprite.drawstarty < 0 ) //  dit nog even vergelijken
            build->sprite.drawstarty = 0;
        build->sprite.drawendy = build->sprite.spriteheight / 2 + build->data.res_y / 2;
        if(build->sprite.drawendy >= build->data.res_y)
            build->sprite.drawendy = build->data.res_y - 1; // klopt hier res_y wel?    
        build->sprite.spritewidth = abs((int)(build->data.res_y / ( build->sprite.transformy)));
        build->sprite.drawstartx = (-build->sprite.spritewidth / 2) + build->sprite.spritescreenx;
        if(build->sprite.drawstartx < 0)
            build->sprite.drawstartx = 0;
        build->sprite.drawendx = build->sprite.spritewidth / 2 + build->sprite.spritescreenx;
        if(build->sprite.drawendx >= build->data.res_x )
            build->sprite.drawendx = build->data.res_x - 1;
        printf("calc\n");
        loop(build);
        //build->sprite.stripe++;
       //sort_sprite(build);
       i++; 
   } 
}

void        sprite(t_build *build)
{

    build->sprite_s[0].x = 6; //#0
    build->sprite_s[0].y = 10;
   // build->sprite_s[1].x = 37; //#1
   // build->sprite_s[1].y = 17;
   // build->sprite_s[2].x = 29; //#2
   // build->sprite_s[2].y = 18;
    build->sprite.sprite_tex = mlx_xpm_file_to_image(build->img.mlx, "./texture/health.xpm", &build->sprite.width, &build->sprite.height);
    build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite_tex, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian);
    printf("sprite\n"); 
    order_sprites(build);
    printf("ordersprite\n"); 
    sort_sprites(build);
    printf("sorteprite\n"); 
    calc_sprites(build);
}
   

 
   
