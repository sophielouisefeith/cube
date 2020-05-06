/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/26 15:58:16 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/05/06 15:01:04 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    rule_one(char *str1, char *str2)
{
   // int x;
    int len1;
    int len2;
    int x ;
    int x2= 0;

	x = 0;
    len1 = ft_strlen(str1);         //5
    len2 = ft_strlen(str2);         //3
    // begin
    while(str1[x] == 9 || str1[x] == ' ')
        x++;
    while(str2[x2] == 9 || str2[x2] == ' ')
        x2++;
    while (x2 <= x)
       {
        if (str2[x2] != '1')
		    error("1 not a valid map\n");
         x2++;
        }
    //middel
	while(str1[x] != '\0')
	{
		if(str1[x] != '1')
			error("2 not a valid first rule\n");
        x++;
    }
    //eind
    x--;
    if (len1 < len2)
    {
        while(str2[x] != '\0')
        {
            if (str2[x] != '1')
			    error("3 not a valid map\n");
            x++;
        }
    }
}
    
// skips the right ones so something goes wrong if its right.

void   middel_part(char *str1, char *str2)
{
    int x;
    int x2 = 0;
    int len1;
    int len2;

	x = 0;
    len1 = ft_strlen(str1);         //5
    len2 = ft_strlen(str2);   

    while(str1[x] == 9 || str1[x] == ' ')
        x++;
    while(str2[x2] == 9 || str2[x2] == ' ')
        x2++;
    //start en eindigt str1 met een 1
    if (str1[x] != '1' || str1[len1 -1] != '1')
		 error("4 not a valid map\n");
    //start positie verschillend
    while (x2 <= x)
       {
        if (str2[x2] != '1')
		    error("5 not a valid map\n");
         x2++;
        }
    //eindpositie verschillend
    x--;
    //situatie len1 is groter dan len2
    if (len1 > len2)
        while (len2 < len1)
        {
            if(str1[len2] != '1')
		        error("6 not a valid map\n");
            len2++;
        }    
    //situatie len1 is kleiner dan len2
    if (len1 < len2)
    {
        while(len1 < len2)
        {
            if (str2[len1] != '1')
		        error("7 not a valid map\n");
            len1++;
        }
    }
        
}



// {
//     int x;
//     int count;
    
//     x  = 0;
//     count = 0;
//     build->data.len_middel = ft_strlen(build->map.array[y]);
//     //if(!build->data.len_array )
//       //  error("empty rule\n");
//     //if ( )
//     // printf("lengte eerste[%d]\n",build->data.len_be);
//     // printf("lengte middelste[%d]\n",build->data.len_middel);
//     while(build->map.array[y][x] != '\0')
//     {
//         if (x == 0 && build->map.array[y][x]!= '1')
// 		    error("not a valid mid rule 1\n");
//         //printf("N\n");
//         // if(build->map.array[y][x] == 'N')
//         // {
//         //     printf("N\n");
//         //     build->data.n = 1;
//         // }
//         if(build->data.len_middel > build->data.len_be)
//         {
//             //count = build->data.len_middel - build->data.len_be;
//             //count++;
//             x = 0;
//             x = build->data.len_middel - count;
//             //printf("x[%d]\n", x);
//             while(build->map.array[y][x] < build->data.len_be)
//             {
//                 x++;
//                 // printf("x [%d]\n", x);
//                 // printf("welk karakter [%c]\n", build->map.array[y][x]);
//            // x = count;
//                 if(build->map.array[y][x]!= '1' && build->map.array[y +1][x]!= '1')
//                     error("not a protected mid rule\n");
//                    // printf("count [%d]\n", count);
//                 x++;
//             }
//         }
//         x++;
//    // printf("het is wel 1\n"); 
        
//     build->data.len_middel = 0;
//     //printf("after first rule \n");
//     //printf(" middelste regels[%s]\n",build->map.array[y]);
//     // moet ook checkken als het geen 1 is of er boven wel een 1 staat als het leeg is dan
//     //is de map ook niet valid
//     // en dus ook kijken als x == '/0' of x-1 een 1 is. anders ook een error
//     }
// }

// void    count_rules(char *str1)
// {
//     int count;
    
//     count = 0;
//     while(build->map.array[y] != '\0')
//     {
// 		count++;
//         y++;
//     }
// 	build->data.size_map = count;
// }

void    rule_last(char *str)
{
    int x;

    x = 0;
    while(str[x] != '\0')
	{
		if(str[x] != '1')
			error("not a valid last rule\n");
        x++;
    }   
}



    
    // int x;

	// x = 0;
    // build->data.len_be  = 0;
    // build->data.len_be = ft_strlen(build->map.array[y]);
   // printf("lengte laatste[%d]\n",build->data.len_be);
    //printf("lengte middel[%d]\n",build->data.len_middel);
    //printf(" y[%d]\n", y);
    //printf(" dit moet de laatste string zijn[%s]\n",build->map.array[y]);
// 	while(build->map.array[y][x] != '\0')
// 	{
//         //printf("hoevaak kom je hier in \n");
// 		if(build->map.array[y][x] != '1' && build->map.array[y][x] != '\0')
// 		    error("not a valid last rule\n"); 
//         x++;
// 	}
// }


// start coordinatien opslaan die moet je opslaan welke coordniaten wat i y en wat is x
// als het een n is kijkt je poppetje naar het noorden dan is je x = 0 en y= 1
// if there two N also wrong. 
// eerst chekken of er een n is als je die vind coordienaten opslaan
// eerst kijken welke coordinaten er zijn 