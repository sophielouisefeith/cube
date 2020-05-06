/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith        #+#    #+#                 */
/*   Updated: 2020/05/06 19:43:51 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
// nog kijken of ze er niet dubbel inzitten -> en als dat zo is moet er een error verschijnen 
// path openen
// map gaan lezen als een array. 
// static void	checkres(char *str, t_build *build)
// check of hij bestaat anders moet hij ook error 

void	check_input(char *str, t_build *build)
{
	int i ;

	i = 0;

	while((str[i] == ' ' || str[i] == 9 ) && str[i])
		i++;
	//------------------------------------------------------------------------------------------------input check of ze er wel inzitten en ook niet dubbel inzitten door dit dus al even een struct aan te zetten 
	//check_dubbel(str);
	if(str[i] == 'R' && str[i + 1] == ' ' && build->data.check_res != 1)
		check_res(str, build);
	if(str[i] == 'F' && str[i + 1] == ' ')
		check_color(str, build);
	if(str[i] == 'C' && str[i + 1] == ' ')
		check_color(str, build);
	if(str[i] == 'S' && str[i + 1] == ' ' && str[i + 2] == '.')
		build->data.sprite = check_path(str);
	if(str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ' && str[i + 3] == '.')
		build->data.north = check_path(str);
	if(str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ' && str[i + 3] == '.')
		build->data.south = check_path(str);
	if(str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ' && str[i + 3] == '.')
		build->data.west = check_path(str);
	if(str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ' && str[i + 3] == '.')
		build->data.east = check_path(str);
}

void 	initialise(t_build *build)
{
	// build->data.res_x = 0;
	// build->data.res_y = 0;
	// build->data.floor = -1;
	// build->data.ceiling = -1;
	// build->data.color_r = -1;
	// build->data.color_g = -1;
	// build->data.color_b = -1;
	// build->data.check_color = 0;
	// build->data.check_res = 0;
	// build->data.size_map = 0;
	build->data.count = 0;
	//build->ray.time = 0;
	//build->ray.oldtime = 0;
	//build->ray.frametime= 0;
	// build->ray.movespeed = 0;
	// build->ray.rotspeed= 0;
	// build->ray.oldirx = 0;
	// build->ray.moveup = 0;
	// build->ray.movedown = 0;
	// build->ray.moveright = 0;
	// build->ray.moveleft = 0;
	// build->ray.oldplanex = 0;
	// build->ray.oldplaney = 0;
	// build->ray.side = 0;
	// build->ray.drawstart = 0;
	// build->ray.drawend = 0;
	//build->data.error_i = 0;
	// nog even alle andere structs op NULL zetten. 
}
// void	check_map(int y,t_build *build)
// {
	// moet eigenlijk eerst weten hoeveel regels er zijn en hoelang die zijn 

	//printf(" string in check map[%s]",build->map.array[8]);
	//printf("in check map \n");
	//printf("wat is y %d\n", y);
	//printf(" hoeveel regels[%d]\n",build->data.size_map);
	// if(y == 8)
	// {
	// 	rule_one(y,build);
	// 	//printf(" hoeveel size[%d]\n", build->data.size_map);
	// 	y++;
		//build->data.size_map--;
	//}
	//printf(" string in check map[%s]\n",build->map.array[y]);
	//printf(" hoeveel size[%d]\n", build->data.size_map);
	// start_pos(y, build);
	// if(build->data.size_map > 1)
	// {
	// 	middel_part(y,build);
		// if(!build->data.n)
		// 	error("no starting point\n");

		//printf(" hoeveel size[%d]\n", build->data.size_map);
		//build->data.size_map--;
		
		//printf("after first rule \n");
	//}
	//printf(" hoeveel size[%d]\n", build->data.size_map);
	//printf("laatste regel moet dit zijn[%s]\n",build->map.array[y]);
	// if (build->data.size_map == 1)
	// {
	// 	//printf(" hoeveel size[%d]\n", build->data.size_map);
	// //	printf("laatste regel moet dit zijn[%s]\n",build->map.array[y]);
	// 	rule_last(y,build);
	// }
	// {
	// 	//printf("3darray[%s]\n", build->map.array[y]);
	// 	printf("x[%d]\n", build->map.array[y][x]);
	// 	x++;
	// 	printf("x[%d]\n", x);
	// 	//y++;
	// }
	// while(build->map.array[y][x])
	// {
	// 	printf("y [%d]", y);
	// 	printf("je bent nog niet op het eind \n");
	// 	x++;

	
	// 	if(build->map.array[y][x] != '1')
	// 	{
	// 		printf("if not 1 \n");
	// 		if(build->map.array[y][x] == 'N')
	// 		{
	// 			build->data.n = 1;
	// 			printf("je heb een N gevonden \n");
	// 		}
	// 		if(build->map.array[y][x] == ' ')
	// 		{
	// 			printf("je bent een spatie \n");	
	// 			if(build->map.array[y+1][x] != '1')
	// 			{
	// 				printf("tweede ronde \n");
	// 				printf("ben je niet valid\n[%d]", y);
	// 				//error("not a valid map\n");
	// 			}			
	// 		}
	// 	}
	// 	x++;
	// }
	//y++;
			// nu zijn we aangekomen dat we gaan checkken of het valid is
			// de rand moet een 1 zijn
			// als x = ' ' dan gaan we om ons heen kijkne
			// [Y +1] [x] != 1
			// 8 vakjes er om heen bekijken  voor het midden
			// 6 aan het eind 
// }

static void charcheck(char **str)
{
    int i;
    int y;
    i = 0;
    y = 0;
    while (str[y] != NULL)
    {
        i = 0;
        while (str[y][i])
        {
            if (str[y][i] != ' ' && str[y][i] != 9 && str[y][i] != '2' && \
            str[y][i] != '1' && str[y][i] != '0' && str[y][i] != 'N' && \
            str[y][i] != 'S' && str[y][i] != 'W' && str[y][i] != 'E')
                error("there is an invalid character in the map");
            i++;
        }
        y++;
    }
}

void 	check_valid_map(t_build *build)
{
	//printf("kom jij");
	// while(build->map.array[y][0] == '\n')
	// {
	// 	y++;
	// 	printf("y [%d]", y);
	// }
	// printf(" string[%s]",build->map.array[y]);
	// printf("y [%d]", y);
	//count_rules(build);
	int lines = 0;
	while(build->map.array[lines])
		lines++;
	charcheck(build->map.array);
	rule_one(build->map.array[0], build->map.array[1]);
	int y = 1;
	while (y < lines -1)		//< lines -1
	{
		middel_part(build->map.array[y], build->map.array[y +1]);
		start_pos(y, build);
		y++;
	}
	rule_last(build->map.array[y]);
	//while (build->map.array[y] != NULL)
	//{
	//	printf("kom jij");
		//check_map(y, build);
	//	y++;
		//build->data.size_map--;
		//printf(" hoeveel size[%d]\n", build->data.size_map);
		//printf("laatste regel moet dit zijn[%s]\n",build->map.array[y]);
		//printf(" string[%s]",build->map.array[y]);
		
		
		//printf("rule [%s]\n", build->map.array[y]);
		//printf("y [%d]", y);
		//y++;
		//printf("y [%d]", y);
	//	printf("kom je hier");
	//}
	//if(!build->data.n)
	//	error("not a valid map no starting point\n");
		//printf("je bent een 1[%x]\n", x);
	//printf("y[%d]", y);
	// build->map.array[y][x]
   	// printf("kom je hier al in");
	// printf("rule [%d]/n", build->data.check_color);
	   
}

static int         space_tab(char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != 9)
            return (-1);// error
        i++;
    }
    return (0);
}
void 	read_string(t_build *build)
{
	int rule;

	rule = 0;

	initialise(build);
	//build->data.str = build->map.array[rule];
	//while (build->map.array[rule])
	// int y;

	// y = 0;
	// while (build->map.array[y] != NULL)
	// {
	// 	printf("3darray[%s]\n", build->map.array[y]);
	// 	y++;
	// }
	while (*build->map.array && rule < 8)
	{
		check_input(*build->map.array, build);
		build->map.array++;
		rule++;
	}
	// while (rule < 8) /// tot 9 pas als je iets hebt opgeslagen dan verhoog je hem.
	// {
	// 	check_input(build->map.array[rule], build );
	// 	//error messages
		
	// //	printf(" string[%s]\n",build->map.array[rule]);
	// 	rule++;	
	// }
	//printf("rule [%d]", rule);
	//printf(" string die ik mee geef[%s]",build->map.array[rule]);
	while (space_tab(*build->map.array) == 0 || *build->map.array == 0)
		build->map.array++;
 	check_valid_map(build);
	
}