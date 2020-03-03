/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainread.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:55:17 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/03 21:06:47 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    char     *res;
    int     fd;
   int   i;
    //char    *line;
    i = 1;
   //	res = 1;
    fd = open(argv[1], O_RDONLY);
   // while (res != '\0')
    //{
        res = get_next_line(fd);
       printf("--%d--", i);
        printf("%s", res);
        printf("\n");
        i++;
       // free(line);
   // }
    while (1){}
    return (0);

}