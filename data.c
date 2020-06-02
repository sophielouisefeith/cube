/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith         #+#    #+#                */
/*   Updated: 2020/06/02 15:50:31 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	check_input(char *str, t_build *build)
{
	int i ;

	i = 0;
	while((str[i] == ' ' || str[i] == 9 ) && str[i])
		i++;
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
	//build->sprite.num = 0;
	// nog even alle andere structs op NULL zetten. 
}

void 	checkmap(char *str)
{
	int i;
	printf("filename %s\n", str);
	i = ft_strlen(str);
	i--;
	if(str[i] == 'b' && str[i -1] == 'u' && str[i - 2] == 'c' && \
	str[i -3] == '.')
		return;
	else
		error("the file has an incorrect name");
}

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
	build->sprite.num = 0;
	int lines = 0;
	while(build->map.array[lines])
		lines++;
	charcheck(build->map.array);
	rule_one(build->map.array[0], build->map.array[1]);
	int y = 1;
	while (y < lines -1)
	{
		middel_part(build->map.array[y], build->map.array[y +1]);
		start_pos(y, build);
		y++;
	}
	rule_last(build->map.array[y]);	   
}

static int         space_tab(char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != 9)
            return (-1);
        i++;
    }
    return (0);
}
void 	read_string(t_build *build)
{
	int rule;

	rule = 0;
	initialise(build);
	while (*build->map.array && rule < 8)
	{
		check_input(*build->map.array, build);
		build->map.array++;
		rule++;
	}
	while (space_tab(*build->map.array) == 0 || *build->map.array == 0)
		build->map.array++;
 	check_valid_map(build);	
}