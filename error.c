/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 19:39:34 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/12 13:00:39 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	error(int i)
// {
// 	if(i)
// 	{
	
// 		if( i == 1)
// 			printf(" The floor color is not valid\n");
// 		if( i == 2)
// 			printf(" The ceiling color is not valid\n");
// 		if( i == 3)
// 			printf("input is checked\n");
// 	}
// 	//return(printf("no errors in input\n"));
// }

void	error(char *str)
{
	printf("ERROR!%s\n", str);
	exit(0);
}
