/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainread.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 18:55:17 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/29 19:18:35 by sfeith        ########   odam.nl         */
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

t_build		*savearray(char *argv)
{
	t_build	*new;
	int		fd;

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
	{
		free(new->map.str);
		return (NULL);
	}
	free(new->map.str);
	new->map.str = NULL;
	return (new);
}

int		main(int argc, char **argv)
{
	t_build	*build;

	build = NULL;
	if (argc != 2 && argc != 3)
		error("to many arguments", 17);
	build = savearray(argv[1]);
	if (argc == 3)
		arg_check(build, argv[2]);
	read_string(build);
	if (!(build->sprite.zbuffer = (double *)\
	malloc(sizeof(double) * build->data.res_x)))
		error_map("malloc failed1", 14, build);
	startgame(build);
	return (0);
}
