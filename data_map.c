/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/26 15:58:16 by SophieLouis    #+#    #+#                */
/*   Updated: 2020/03/30 14:31:01 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    rule_one(int y, t_build *build)
{
    int x;

	x = 0;
    build->data.len_be = ft_strlen(build->map.array[y]);
	while(build->map.array[y][x] != '\0')
	{
		if(build->map.array[y][x] != '1' && build->map.array[y][x] != '\0')
		{
            //printf("het is geen 1\n");	
			if(build->map.array[y][x] == ' ')
			{
				if(build->map.array[y+1][x] != '1')
					error("not a valid first rule\n");
			}
			error("not a valid first rule\n");
		}
        //printf("het is niet een spatie met wel een 1\n");	
        x++;
	}
} 
// skips the right ones so something goes wrong if its right.

void   middel_part(int y, t_build *build)
{
    int x;
    int count;
    
    x  = 0;
    count = 0;
    build->data.len_middel = ft_strlen(build->map.array[y]);
    //if(!build->data.len_array )
      //  error("empty rule\n");
    //if ( )
    printf("lengte eerste[%d]\n",build->data.len_be);
    printf("lengte middelste[%d]\n",build->data.len_middel);
    while(build->map.array[y][x] != '\0')
    {
        if (x == 0 && build->map.array[y][x]!= '1')
		    error("not a valid mid rule 1\n");
        //printf("N\n");
        // if(build->map.array[y][x] == 'N')
        // {
        //     printf("N\n");
        //     build->data.n = 1;
        // }
        if(build->data.len_middel > build->data.len_be)
        {
            //count = build->data.len_middel - build->data.len_be;
            //count++;
            x = 0;
            x = build->data.len_middel - count;
            printf("x[%d]\n", x);
            while(build->map.array[y][x] < build->data.len_be)
            {
                x++;
                printf("x [%d]\n", x);
                printf("welk karakter [%c]\n", build->map.array[y][x]);
           // x = count;
                if(build->map.array[y][x]!= '1' && build->map.array[y +1][x]!= '1')
                    error("not a protected mid rule\n");
                    printf("count [%d]\n", count);
                x++;
            }
        }
        x++;
   // printf("het is wel 1\n"); 
        
    build->data.len_middel = 0;
    //printf("after first rule \n");
    //printf(" middelste regels[%s]\n",build->map.array[y]);
    // moet ook checkken als het geen 1 is of er boven wel een 1 staat als het leeg is dan
    //is de map ook niet valid
    // en dus ook kijken als x == '/0' of x-1 een 1 is. anders ook een error
    }
}

void    count_rules(int y, t_build *build)
{
    int count;
    
    count = 0;
    while(build->map.array[y] != '\0')
    {
		count++;
        y++;
    }
	build->data.size_map = count;
}

void    rule_last(int y, t_build *build)
{
    int x;

	x = 0;
    build->data.len_be  = 0;
    build->data.len_be = ft_strlen(build->map.array[y]);
   // printf("lengte laatste[%d]\n",build->data.len_be);
    //printf("lengte middel[%d]\n",build->data.len_middel);
    //printf(" y[%d]\n", y);
    //printf(" dit moet de laatste string zijn[%s]\n",build->map.array[y]);
	while(build->map.array[y][x] != '\0')
	{
        //printf("hoevaak kom je hier in \n");
		if(build->map.array[y][x] != '1' && build->map.array[y][x] != '\0')
		    error("not a valid last rule\n"); 
        x++;
	}
}


// start coordinatien opslaan die moet je opslaan welke coordniaten wat i y en wat is x
// als het een n is kijkt je poppetje naar het noorden dan is je x = 0 en y= 1
// if there two N also wrong. 
// eerst chekken of er een n is als je die vind coordienaten opslaan