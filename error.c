/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 19:39:34 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/18 11:05:25 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *str, int i)
{
	write(1, "An error occured because:\n", 27);
	write(1, str, i);
	write(1, ".\n", 2);
	exit(0);
}

void	error_map(char *str, int i, t_build *build)
{
	free_map(build);
	write(1, "An error occured because:\n", 27);
	write(1, str, i);
	write(1, ".\n", 2);
	exit(0);
}

void	error_start(char *str, int i)
{
	write(1, "An error occured because:\n", 27);
	write(1, str, i);
	write(1, ".\n", 2);
	exit(0);
}

void	error_game(char *str, int i, t_build *build)
{
	free_game(build);
	write(1, "An error occured because:\n", 27);
	write(1, str, i);
	write(1, ".\n", 2);
	exit(0);
}
