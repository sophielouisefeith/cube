/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/09 17:44:25 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


// de eerste 9 regels. 
// ( build.map->array)
#include "cub3d.h"

// wanneer is het een valid R ? moeten twee waardes inzitten de characters moeten omgezet worden in een getal dus van character naar int atoi 
void	checkres(char *str, t_build *build)
{
	int i;

	i = 0;
	printf("wat is de string nu[%s][%c]\n", str, str[i]);
	while((str[i] != ' ' || str[i] != 9 ) && str[i])  //ht en spatie 
		i++;
	while(str[i] != ' ' || str[i] >= '0'  && str[i] <= '9')
	//nu even dat regeltje uit atoi erin zetten 
	
	//printf("wat is de string nu[%s][%c]\n", str, str[i]);
	//build->data->res = 
	// printf("je bent nu in res");
	// printf("wat is nu de str[%s]", str);
	 printf("wat is nu de str[%s]", build->map.str);
		
}

void 	initialise(t_build *build)
{
	build->data->res = 0;
	build->data->floor = 0;
	build->data->ceiling = 0;
	build->data->north = 0;
	build->data->south = 0;
	build->data->west = 0;
	build->data->east = 0;
}

void	check_input(char *str, t_build *build)
{
	int i ;

	i = 0;
	//-------------------------------------------------------------------------printf("kom je hier in[%s]\n", *build->map.array);
	// while((str[i] != ' ' || str[i] != 9 ) && str[i])  //ht en spatie 
	// 	i++;
	//printf("kom je hier in[%s]\n", *build->map.array);
	//printf("i[%d]\n", i);
	if(str[i] == 'R' && str[i + 1] == ' ')
		checkres(str, build);	
// if(str[i] == 'F' && str[i + 1] == ' ')
// 	check_data(str, build);
// if(str[i] == 'C' && str[i + 1] == ' ')
// 	check_data(str, build);
// if(str[i] == 'S' && str[i + 1] == ' ' && str[i + 2] == '.')
// 	check_data(str, build);
// if(str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ' && str[i + 3] == '.')
// 	check_data(str, build);
// if(str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ' && str[i + 3] == '.')
// 	check_data(str, build);
// if(str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ' && str[i + 3] == '.')
// 	check_data(str, build);
// if(str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ' && str[i + 3] == '.')
// 	check_data(str, build);
	
	
	
}

void 	readstr(t_build *build)
{
	//t_build *data;
	//printf("kom je in data");
	//printf("kom je in data[s]");
	//initialise(build);
	while (*build->map.array != NULL)
	{
		//--------------------------------------------------------------------------------------printf("kom je hier in[%s]\n", *build->map.array);
		check_input(*build->map.array, build);
		build->map.array++;
	}

	// int y;

	// y = 0;
	// while (build->map.array[y])
	// {
	// 	y++;
	// }
	
	
	// return(build->map.array);
}