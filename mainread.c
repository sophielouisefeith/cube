/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainread.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:55:17 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/04 16:17:27 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// in de main willen we eigenlijk alle stapjes door gaan geven aan een functie. 
int main(int argc, char **argv)
{

// 
	t_build build;
	
    char	**array;
	char	*s;
    int     fd;
   int   i;
   
    i = 1;
	
	fd = open(argv[1], O_RDONLY);
   	array = ft_savearray(fd, &build);
      	printf("--%d--", i);
        printf("%s", *array);
        printf("\n");
        i++;
    // while (1){}
    return (0);

}