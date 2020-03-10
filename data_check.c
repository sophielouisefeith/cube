/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 17:21:18 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/10 19:36:45 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_res(char *str, t_build *build)
{
	int i;
	 
 	i = 1;
	
	while((str[i] == ' ' || str[i] == 9 ) && str[i])
		i++;
	
	while((str[i] >= '0' && str[i] <= '9' ))
	{
		build->data.res_x = build->data.res_x * 10 + str[i] - '0';
		i++;
	}
	while((str[i] == ' ' || str[i] == 9 ) && str[i])
		i++;
	while((str[i] >= '0' && str[i] <= '9' ))
	{
		build->data.res_y = build->data.res_y * 10 + str[i] - '0';
		i++;
	}
	
	//--------------------------------------------------------nu nog checken of er dan ook nog getallen achter zitten. 
 	//--------------------------------------------------------printf("res_x[%d]\n", build->data->res_x);
 	//--------------------------------------------------------printf("res_y[%d]\n", build->data->res_y);
}

int		define_color(char *str, t_build *build, int *i)
{
	int color;
	
	color = 0;
	while((str[*i] == ' ' || str[*i] == 9 ) && str[*i]) // tot het eind
		(*i)++;
	while(str[*i] >= '0' && str[*i] <= '9' && str[*i])
	{
		color = color * 10 + str[*i] - '0';
		(*i)++;
		if(color < 0 ||color > 255)
			return(-1);
	}
	if(str[*i] == ',')
		(*i)++;
	if(!ft_isdigit(str[*i]) && str[*i]!= '\0')
		return(-1);// ERROR
	build->data.check_color++;
	return (color);
}
int		check_color(char *str, t_build *build)
{
	int i;
	int final;
	
	i = 1;
	final = 0;
	while((str[i] == ' ' || str[i] == 9 ) && str[i])
		i++;
	build->data.color_r = define_color(str, build, &i);
	if (build->data.color_r == -1)
		return(-1);
	build->data.color_g = define_color(str, build, &i);
	if (build->data.color_g == -1)
		return(-1);
	build->data.color_b = define_color(str, build, &i);
	if (build->data.color_b == -1)
		return(-1);
	if(build->data.check_color < 4)
		return(final);
	else return (-1 );// ERROR 
		
}

char	*check_path(char *str)
{
		return(str);
		// moeten hier nog meer checks bij ?
}

// void	check_dubbel(char *str)
// {
// 	( R, N, S, W)
	
// }