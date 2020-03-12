/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/12 13:15:34 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
// nog kijken of ze er niet dubbel inzitten -> en als dat zo is moet er een error verschijnen 
// alle error meldingen checken
// path openen
// map gaan lezen als een array. 
// static void	checkres(char *str, t_build *build)
// check of hij bestaat 

void	check_input(char *str, t_build *build)
{
	int i ;

	i = 0;
	// build->map.array[y][i]
	while((str[i] == ' ' || str[i] == 9 ) && str[i])
		i++;
	//------------------------------------------------------------------------------------------------input check of ze er wel inzitten en ook niet dubbel inzitten door dit dus al even een struct aan te zetten 
	//check_dubbel(str);
	if(str[i] == 'R' && str[i + 1] == ' ' && build->data.check_res != 1)
		check_res(str, build);
	// if(str[i] == 'F' && str[i + 1] == ' ')
	// 	check_color(str, build);
	if(str[i] == 'C' && str[i + 1] == ' ')
		check_color(str, build);
	// if(str[i] == 'S' && str[i + 1] == ' ' && str[i + 2] == '.')
	// 	build->data.sprite = check_path(str);
	// if(str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ' && str[i + 3] == '.')
	// 	build->data.north = check_path(str);
	// if(str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ' && str[i + 3] == '.')
	// 	build->data.south = check_path(str);
	// if(str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ' && str[i + 3] == '.')
	// 	build->data.west = check_path(str);
	// if(str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ' && str[i + 3] == '.')
	// 	build->data.east = check_path(str);
}

static void 	initialise(t_build *build)
{
	build->data.res_x = 0;
	build->data.res_y = 0;
	build->data.floor = -1;
	build->data.ceiling = -1;
	build->data.color_r = -1;
	build->data.color_g = -1;
	build->data.color_b = -1;
	build->data.check_color = 0;
	build->data.check_res = 0;
	//build->data.error_i = 0;
	// nog even alle andere structs op NULL zetten. 
}

void 	read_string(t_build *build)
{
	int rule;

	rule = 0;

	initialise(build);
	//build->data.str = build->map.array[rule];
	while (build->map.array[rule]) /// tot 9 pas als je iets hebt opgeslagen dan verhoog je hem.
	{
		check_input(build->map.array[rule], build);
		//error messages
		rule++;
	}
}