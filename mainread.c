/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainread.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:55:17 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/08 14:03:10 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void		arg_check(t_build *build, char *str)
{
	char *check;
	int		i;
	
	check = "--save";
	i = 0;
	while(check[i])
	{
		if (check[i] != str[i])
			error("2 argument invalid", 18);
		i++;
	}
	if(str[i] != '\0')
		error("2 argument invalid", 18);
	build->data.scrsht = 1;
	return ;
		
}


t_build		*savearray(char *argv)
{
	t_build *new;
	int fd;

	checkmap(argv);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error("programme didnt succeed", 21);
	new = (t_build*)malloc(sizeof(t_build));
	new->map.str = get_next_line(fd);
	if (new->map.str == 0)
		return (NULL);
	new->map.array = ft_split(new->map.str, '\n');
	if (!new->map.array)
		return (NULL);
	//free(new->map.str);
	return (new);
}

int main(int argc, char **argv)
{
    t_build	*build = NULL;
	
	//t_img	img;
	if(argc != 2 && argc != 3)
		error("to many arguments", 17);
	if (argc == 3)
		arg_check(build, argv[2]);
	build = savearray(argv[1]);
	read_string(build);
	startgame(build);
	return(0);
}
