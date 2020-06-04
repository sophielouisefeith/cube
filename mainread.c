/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainread.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:55:17 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/04 11:49:49 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_build	*build;
	//t_img	img;
	if(argc != 2)
		error("to many arguments"); 
	build = savearray(argv[1]);
	read_string(build);
	startgame(build);
	return(0);
}
