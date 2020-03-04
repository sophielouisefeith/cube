/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainread.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:55:17 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/04 18:02:43 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
//---------------------------------step1----------------------------------------------
//first we will call the function savearray to open the map.cub this function reads the map----------------------------------------------
//and to return the map as an 3darray
	
	t_build *build;
	
	
	int y;

	y = 0;
	//if(argc != 2)
  	 	build = savearray(argv[1]);
	while (build->map.array[y])
	{
		printf("3darray[%s]\n", build->map.array[y]);
		y++;
	}
	// return(build.map->array);
	// while (1){}  
//---------------------------------step2----------------------------------------------
//now we have to safe the data of the array and check on cases. 

	return (0);
}
