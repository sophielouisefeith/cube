// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   sprite.c                                           :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2020/04/28 10:23:38 by SophieLouis    #+#    #+#                */
// /*   Updated: 2020/06/02 15:04:18 by sfeith        ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */


#include "cub3d.h"

static void makesprite(t_build *build)
{
	printf("wil je mij gaan printen");
    int x;
    int color;
    x = 0;
    int y = build->sprite.drawstarty;  // y = start x = end wat is de start positie hoe sta ik er voor alle waarden even checkken
    while(y < build->sprite.drawendy) 
    {
        int d = y * 256 - build->data.res_y * 128  + build->sprite.spriteheight * 128;
        build->sprite.texy = ((d * 64) / build->sprite.spriteheight) / 256;
        color = *(unsigned int*)(build->sprite.dataadres + (build->sprite.texy * build->sprite.line_length + build->sprite.texx * (build->sprite.bpp / 8)));
        my_mlx_pixel_put(build, build->sprite.stripe, y, color); //wat geef je mee voor y, welkle posities neemt hij stripedarwstrartx
        y++;
    }
}
static int loop(t_build *build)
{
    
    build->sprite.stripe = build->sprite.drawstartx; // miss moet dit end zijn 
    while( build->sprite.stripe < build->sprite.drawendx)
    {
        build->sprite.texx = (int)(256 * (build->sprite.stripe - (-build->sprite.spritewidth / 2 + build->sprite.spritescreenx)) * textwidth / build->sprite.spritewidth / 256); //klopt dit
        if(build->sprite.transformy > 0 && build->sprite.stripe > 0 && build->sprite.stripe < build->data.res_x\
        && build->sprite.transformy < build->sprite.zbuffer[build->sprite.stripe])
          makesprite(build);
        build->sprite.stripe++;
    }
    return(0);
}
void sort_sprites(t_build *build)
{
    int i;
    int tmp;
    double tmp2;
    i = 0;
    double spritedistance[build->sprite.num];
    while( i < build->sprite.num)
    {
         spritedistance[i] = ((build->cor.start_pos_x - build->sprite_s->sprite_cor[i][0]) * (build->cor.start_pos_x - build->sprite_s->sprite_cor[i][0]) + 
         (build->cor.start_pos_y - build->sprite_s->sprite_cor[i][1]) * (build->cor.start_pos_y - build->sprite_s->sprite_cor[i][1]));
         i++;
    }
    i = 0;
    while ( i < build->sprite.num -1)
    {
        if (spritedistance[i] < spritedistance[i + 1])
        {
            tmp2 = spritedistance[i +1];
            spritedistance[i] = spritedistance[i + 1];
            spritedistance[i + 1] = tmp2;
            tmp = build->sprite_s->sprite_cor[i][0];
            build->sprite_s->sprite_cor[i][0] = build->sprite_s->sprite_cor[i + 1][0];
            build->sprite_s->sprite_cor[i + 1][0] = tmp; 
            tmp = build->sprite_s->sprite_cor[i][1];
            build->sprite_s->sprite_cor[i][1] = build->sprite_s->sprite_cor[i + 1][1];
            build->sprite_s->sprite_cor[i + 1][1] = tmp; 
            i = -1;
        }
        i++;  
    }
    
}
void    calc_sprites(t_build *build)
{  
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
}
void        sprite(t_build *build)
{
    int i;
    int width;
    int height;
	 i = 0;
    char *path;
    path = build->data.sprite;
    if (!(build->sprite.sprite_tex = mlx_xpm_file_to_image(build->img.mlx, path, &width, &height)))
        error("no");
    if(!(build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite_tex, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian)))
        error("no");
    //order_sprites(build); 
    sort_sprites(build);
    // printf("%d\n", build->sprite.num);
    // printf("%f en %f\n", build->sprite_s->sprite_cor[i][0], build->sprite_s->sprite_cor[i][1]);
    // printf("%d en %d\n", build->cor.start_pos_x, build->cor.start_pos_y);
   
    while(i < build->sprite.num)
    {
        build->sprite.spritex = build->sprite_s->sprite_cor[i][0] - build->cor.start_pos_x;
        build->sprite.spritey = build->sprite_s->sprite_cor[i][1] - build->cor.start_pos_y;
        build->sprite.invdet = 1.0 / (build->ray.planex * build->cor.diry - build->cor.dirx * build->ray.planey);
        build->sprite.transformx = build->sprite.invdet * (build->cor.diry - build->cor.dirx * build->sprite.spritey);
        if( build->ray.x_cam == 1)
            build->sprite.transformx *= -1;
        build->sprite.transformy = build->sprite.invdet * (-build->ray.planey * build->sprite.spritex + build->ray.planex * build->sprite.spritey);
        calc_sprites(build);
        loop(build);
        i++;
    }
   
}
   









// #include "cub3d.h"

// // void locate_sprites(t_build *build)
// // {
// //     printf("kom je hier");
// //     int x;
// //     int y;
// //     int i;
    
// //     i = 0;
// //     y = 0;
// //     x = 0;
   
// //     //build->sprite.zbuffer[x] = build->ray.perpwalldist;
// //     while (y < build->data.res_y) //mapheight
// //     {
// //         //x = 0;
// //         while (x < build->data.res_x) // mapwidth
// //         {
// //           if(build->map.array[y][x] == '2')
// //           {
// //             build->sprite_s[i].x = y + 0.5;
// //             build->sprite_s[i].y = x + 0.5;
// //             i++;
// //           }
// //           x++;
// //         }
// //         y++;
// //     }
// // }

// // static char  *sprite_chose(t_build *build)
// // {
// //     return(build->data.sprite);
// //     //printf("sprite: %s", build->data.sprite);
// // }

// // static void makesprite(t_build *build)
// // {
// //     int x;
// //     int color;

// //     x = 0;
// //     //path = sprite_chose(build);
// //     //build->sprite.y = build->sprite.drawstarty;
// //     // build->sprite.sprite = mlx_xpm_file_to_image(build->img.mlx, "./texture/pillar.xpm", &build->sprite.width, &build->sprite.height);
// //     // build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian);
// //     //  printf("lengte drawstarty%d\n",build->sprite.drawstarty );
// //     //  printf("y%d\n",build->sprite.y );
// //     //  printf("x%d\n",build->sprite.stripe);
// //     build->sprite.y = build->sprite.drawstarty;  // y = start x = end wat is de start positie hoe sta ik er voor alle waarden even checkken
// //     while(build->sprite.y < build->sprite.drawendy) 
// //     {
// //         build->sprite.d = build->sprite.y * 256 - build->data.res_y * 128  + build->sprite.spriteheight * 128;
// //         build->sprite.texy = ((build->sprite.d * 64) / build->sprite.spriteheight) / 256;
// //         color = *(unsigned int*)(build->sprite.dataadres + (build->sprite.texy * build->sprite.line_length + build->sprite.texx * (build->sprite.bpp / 8)));
// //         my_mlx_pixel_put(build, build->sprite.stripe, build->sprite.y, color); //wat geef je mee voor y, welkle posities neemt hij stripedarwstrartx
// //         build->sprite.y++;
// //     }
// // }

// // static int loop(t_build *build)
// // {
// //     build->sprite.stripe = build->sprite.drawstartx; // miss moet dit end zijn 
// //     while( build->sprite.stripe < build->sprite.drawendx)
// //     {
// //         build->sprite.texx = (int)(256 * (build->sprite.stripe - (-build->sprite.spritewidth / 2 + build->sprite.spritescreenx)) * textwidth / build->sprite.spritewidth / 256); //klopt dit
// //         // build->sprite.y = build->sprite.drawstarty;
// //         if(build->sprite.transformy > 0 && build->sprite.stripe > 0 && build->sprite.stripe < build->data.res_x)
// //            // && build->sprite.transformy < build->sprite.zbuffer[build->sprite.stripe])
// //           makesprite(build);
// //         build->sprite.stripe++;
// //     }
// //     return(0);
// // }
// // void order_sprites(t_build *build)
// // {
// //     int i;
// //     double spritedistance[build->sprite.num];

// //     i = 0;
// //     while(i < build->sprite.num)
// //     {
// //         build->sprite.spriteorder[i][0] = build->sprite_s->sprite_cor[i][0];
// //         build->sprite.spriteorder[i][1] = build->sprite_s->sprite_cor[i][1];
// //         i++;
// //     }
// //     while(i < build->sprite.num)
// //     {
// //          spritedistance[i] = ((build->cor.start_pos_x - build->sprite.spriteorder[i][0]) * (build->cor.start_pos_x - build->sprite.spriteorder[i][0]) + 
// //          (build->cor.start_pos_y - build->sprite.spriteorder[i][1]) * (build->cor.start_pos_y - build->sprite.spriteorder[i][1]));
// //          i++;
// //     }
// // }

// // void sort_sprites(t_build *build)
// // {
// //     int i;
// //     int tmp;
// //     double tmp2;
// //     double spritedistance[build->sprite.num];

// //     i = 0;
// //     while ( i < build->sprite.num -1)
// //     {
// //         if (spritedistance[i] < spritedistance[i + 1])
// //         {
// //             tmp2 = spritedistance[i +1];
// //             spritedistance[i] = spritedistance[i + 1];
// //             spritedistance[i + 1] = tmp2;
// //             tmp = build->sprite.spriteorder[i][1];
// //             build->sprite.spriteorder[i][0] = build->sprite.spriteorder[i + 1][0];
// //             build->sprite.spriteorder[i + 1][0] = tmp; 
// //             tmp = build->sprite.spriteorder[i][1];
// //             build->sprite.spriteorder[i][1] = build->sprite.spriteorder[i + 1][1];
// //             build->sprite.spriteorder[i + 1][1] = tmp; 
// //             i = -1;
// //         }
// //         i++;  
// //     }
    
// // }

// // void    calc_sprites(t_build *build)
// // {  
// //     int    x;
// //     int    i;
// //     int    y;
    
// //     x = 0;
// //     i = 0;
// //     y = 0;
// //    // locate_sprites(build);
// //    // build->sprite.zbuffer[x] = build->ray.perpwalldist;
// //     while(i < build->sprite.num)
// //     {
// //         build->sprite.spritex = build->sprite_s->sprite_cor[i][0]; //- build->cor.start_pos_x;
// //         build->sprite.spritey = build->sprite_s->sprite_cor[i][1]; // - build->cor.start_pos_y;
// //         build->sprite.invdet = 1.0 / (build->ray.planex * build->cor.diry - build->cor.dirx * build->ray.planey);
// //         build->sprite.transformx = build->sprite.invdet * (build->cor.diry - build->cor.dirx * build->sprite.spritey);
// //         if( build->ray.x_cam == 1)
// //             build->sprite.transformx *= -1;
// //         build->sprite.transformy = build->sprite.invdet * (-build->ray.planey * build->sprite.spritex + build->ray.planex * build->sprite.spritey);
        
// //         build->sprite.spritescreenx = (int)build->data.res_x / 2 * (1 + build->sprite.transformx / build->sprite.transformy);
// //         build->sprite.spriteheight = abs((int)(build->data.res_y / (build->sprite.transformy))); // ik heb hier nu geen abs voorgezet even aan maran vragen res_y?
// //         build->sprite.drawstarty = -build->sprite.spriteheight / 2 + build->data.res_y / 2;
// //         if(build->sprite.drawstarty < 0 ) //  dit nog even vergelijken
// //             build->sprite.drawstarty = 0;
// //         build->sprite.drawendy = build->sprite.spriteheight / 2 + build->data.res_y / 2;
// //         if(build->sprite.drawendy >= build->data.res_y)
// //             build->sprite.drawendy = build->data.res_y - 1; // klopt hier res_y wel?    
// //         build->sprite.spritewidth = abs((int)(build->data.res_y / ( build->sprite.transformy)));
// //         build->sprite.drawstartx = (-build->sprite.spritewidth / 2) + build->sprite.spritescreenx;
// //         if(build->sprite.drawstartx < 0)
// //             build->sprite.drawstartx = 0;
// //         build->sprite.drawendx = build->sprite.spritewidth / 2 + build->sprite.spritescreenx;
// //         if(build->sprite.drawendx >= build->data.res_x )
// //             build->sprite.drawendx = build->data.res_x - 1;
// //         loop(build);
// //         i++; 
// //    } 
// // }

// // void        sprite(t_build *build)
// // {
    
// //     char *path;
// //     path = build->data.sprite;
// //     if (!(build->sprite.sprite_tex = mlx_xpm_file_to_image(build->img.mlx, path, &build->sprite.width, &build->sprite.height)))
// //         error("malloc failes");
// //     if(!(build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite_tex, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian)))
// //         error("malloc failed");

// //     order_sprites(build); 
// //     sort_sprites(build);
// //     calc_sprites(build);
// // }
   

 
   

// static void makesprite(t_build *build)
// {
//     int x;
//     int color;

//     x = 0;
//     //path = sprite_chose(build);
//     //build->sprite.y = build->sprite.drawstarty;
//     // build->sprite.sprite = mlx_xpm_file_to_image(build->img.mlx, "./texture/pillar.xpm", &build->sprite.width, &build->sprite.height);
//     // build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian);
//     //  printf("lengte drawstarty%d\n",build->sprite.drawstarty );
//     //  printf("y%d\n",build->sprite.y );
//     //  printf("x%d\n",build->sprite.stripe);
//     build->sprite.spritey= build->sprite.drawstarty;  // y = start x = end wat is de start positie hoe sta ik er voor alle waarden even checkken
//     while(build->sprite.spritey < build->sprite.drawendy) 
//     {
//         printf("spritex : [%f]", build->sprite.spritey);
//         build->sprite.d = build->sprite.spritey * 256 - build->data.res_y * 128  + build->sprite.spriteheight * 128;
//         build->sprite.texy = ((build->sprite.d * 64) / build->sprite.spriteheight) / 256;
//         color = *(unsigned int*)(build->sprite.dataadres + (build->sprite.texy * build->sprite.line_length + build->sprite.texx * (build->sprite.bpp / 8)));
//         my_mlx_pixel_put(build, build->sprite.stripe, build->sprite.y, color); //wat geef je mee voor y, welkle posities neemt hij stripedarwstrartx
//         build->sprite.spritey++;
//     }
// }

// static int loop(t_build *build)
// {
    
//     printf("transformy %f\n", build->sprite.transformy);
//     build->sprite.stripe = build->sprite.drawstartx; // miss moet dit end zijn 
//     while( build->sprite.stripe < build->sprite.drawendx)
//     {
//         build->sprite.texx = (int)(256 * (build->sprite.stripe - (-build->sprite.spritewidth / 2 + build->sprite.spritescreenx)) * textwidth / build->sprite.spritewidth / 256); //klopt dit
//         // build->sprite.y = build->sprite.drawstarty;
//         printf("transformy %f\n", build->sprite.transformy);
//         printf("zbuffer %f\n", build->sprite.zbuffer[build->sprite.stripe]);
//         if(build->sprite.transformy > 0 && build->sprite.stripe > 0 && build->sprite.stripe < build->data.res_x \
//             && build->sprite.transformy < build->sprite.zbuffer[build->sprite.stripe])
//           makesprite(build);
//         build->sprite.stripe++;
//     }
//     return(0);
// }
// // void order_sprites(t_build *build)
// // {
// //     int i;
// //     double spritedistance[build->sprite.num];

// //     i = 0;
// //     // while(i < build->sprite.num)
// //     // {
// //     //     build->sprite.spriteorder[i][0] = build->sprite_s->sprite_cor[i][0];
// //     //     build->sprite.spriteorder[i][1] = build->sprite_s->sprite_cor[i][1];
// //     //     i++;
// //     // }
// //     // while(i < build->sprite.num)
// //     // {
// //     //      spritedistance[i] = ((build->cor.start_pos_x - build->sprite_s->sprite_cor[i][0]) * (build->cor.start_pos_x - build->sprite_s->sprite_cor[i][0]) + 
// //     //      (build->cor.start_pos_y - build->sprite_s->sprite_cor[i][1]) * (build->cor.start_pos_y - build->sprite_s->sprite_cor[i][1]));
// //     //      i++;
// //     // }
// // }

// static void sort_sprites(t_build *build)
// {
//     int i;
//     int tmp;
//     double tmp2;
//     double spritedistance[build->sprite.num];
// 	//printf("nu zit je in de loop van sprite ");

//     i = 0;
// 	while(i < build->sprite.num)
//     {
//          spritedistance[i] = ((build->cor.start_pos_x - build->sprite_s->sprite_cor[i][0]) * (build->cor.start_pos_x - build->sprite_s->sprite_cor[i][0]) + 
//          (build->cor.start_pos_y - build->sprite_s->sprite_cor[i][1]) * (build->cor.start_pos_y - build->sprite_s->sprite_cor[i][1]));
//          i++;
//     }
// 	i = 0;
//     while ( i < build->sprite.num -1)
//     {
//         if (spritedistance[i] < spritedistance[i + 1])
//         {
//             tmp2 = spritedistance[i +1];
//             spritedistance[i] = spritedistance[i + 1];
//             spritedistance[i + 1] = tmp2;
//             tmp = build->sprite_s->sprite_cor[i][1];
//            	build->sprite_s->sprite_cor[i][0] = build->sprite_s->sprite_cor[i + 1][0];
//             build->sprite_s->sprite_cor[i + 1][0] = tmp; 
//             tmp = build->sprite_s->sprite_cor[i][1];
//             build->sprite_s->sprite_cor[i][1] = build->sprite_s->sprite_cor[i + 1][1];
//             build->sprite_s->sprite_cor[i + 1][1] = tmp; 
//             i = -1;
//         }
//         i++;  
//     }
    
// }

// static void    calc_sprites(t_build *build)
// {  
//     int    x;
//     int    i;
//     int    y;
    
//     x = 0;
//     i = 0;
//     y = 0;
// 	//printf("nu zit je in de loop van sprite ");
//    // locate_sprites(build);
//    // build->sprite.zbuffer[x] = build->ray.perpwalldist;
//     // while(i < build->sprite.num)
//     // {
//         // build->sprite.spritex = build->sprite_s->sprite_cor[i][0]; //- build->cor.start_pos_x;
//         // build->sprite.spritey = build->sprite_s->sprite_cor[i][1]; // - build->cor.start_pos_y;
//         // build->sprite.invdet = 1.0 / (build->ray.planex * build->cor.diry - build->cor.dirx * build->ray.planey);
//         // build->sprite.transformx = build->sprite.invdet * (build->cor.diry - build->cor.dirx * build->sprite.spritey);
//         // if( build->ray.x_cam == 1)
//         //     build->sprite.transformx *= -1;
//         // build->sprite.transformy = build->sprite.invdet * (-build->ray.planey * build->sprite.spritex + build->ray.planex * build->sprite.spritey);
        
//         build->sprite.spritescreenx = (int)build->data.res_x / 2 * (1 + build->sprite.transformx / build->sprite.transformy);
//         build->sprite.spriteheight = abs((int)(build->data.res_y / (build->sprite.transformy))); // ik heb hier nu geen abs voorgezet even aan maran vragen res_y?
//         build->sprite.drawstarty = -build->sprite.spriteheight / 2 + build->data.res_y / 2;
//         if(build->sprite.drawstarty < 0 ) //  dit nog even vergelijken
//             build->sprite.drawstarty = 0;
//         build->sprite.drawendy = build->sprite.spriteheight / 2 + build->data.res_y / 2;
//         if(build->sprite.drawendy >= build->data.res_y)
//             build->sprite.drawendy = build->data.res_y - 1; // klopt hier res_y wel?    
//         build->sprite.spritewidth = abs((int)(build->data.res_x / ( build->sprite.transformy)));
//         build->sprite.drawstartx = (-build->sprite.spritewidth / 2) + build->sprite.spritescreenx;
//         if(build->sprite.drawstartx < 0)
//             build->sprite.drawstartx = 0;
//         build->sprite.drawendx = build->sprite.spritewidth / 2 + build->sprite.spritescreenx;
//         if(build->sprite.drawendx >= build->data.res_x )
//             build->sprite.drawendx = build->data.res_x - 1;
// }

// void        sprite(t_build *build)
// {
//     int i;

  
//    // printf("kom jij hier ");
//     char *path;
//     path = build->data.sprite;
//     if (!(build->sprite.sprite_tex = mlx_xpm_file_to_image(build->img.mlx, path, &build->sprite.width, &build->sprite.height)))
//         error("no");
//     if(!(build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite_tex, &build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian)))
//         error("no");
//     i = 0;
//     //order_sprites(build); 
//     sort_sprites(build);
//     //build->sprite.num = 1;
//     while(i < build->sprite.num)
//     {
// 		printf("nu zit je in de loop van sprite ");
//         build->sprite.spritex = build->sprite_s->sprite_cor[i][0] - build->cor.start_pos_x;
//         build->sprite.spritey = build->sprite_s->sprite_cor[i][1] - build->cor.start_pos_y;
//         build->sprite.invdet = 1.0 / (build->ray.planex * build->cor.diry - build->cor.dirx * build->ray.planey);
//         build->sprite.transformx = build->sprite.invdet * (build->cor.diry * build->sprite.spritex- build->cor.dirx * build->sprite.spritey);// build->sprite.transformx = build->sprite.invdet * (build->cor.diry - build->cor.dirx * build->sprite.spritey);
//         if( build->ray.x_cam == 1)
//             build->sprite.transformx *= -1;
//         build->sprite.transformy = build->sprite.invdet * (-build->ray.planey * build->sprite.spritex + build->ray.planex * build->sprite.spritey);
//         calc_sprites(build);
//         loop(build);
//         i++;
//     }
   
// }
   

 