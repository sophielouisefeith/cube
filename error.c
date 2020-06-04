/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 19:39:34 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/03 17:32:43 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *str)
{
	printf("ERROR!%s\n", str);
	exit(0);
}

// geen printf write strlen. 