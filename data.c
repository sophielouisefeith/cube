/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/30 17:59:49 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <CoreGraphics/CGDirectDisplay.h>

static void				charcheck(char **str)
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
				error("invalid character", 17);
			i++;
		}
		y++;
	}
}

void					check_valid_map(t_build *build)
{
	int		lines;
	int		y;

	y = 1;
	lines = 0;
	build->sprite.num = 0;
	while (build->map.array[lines])
		lines++;
	if (lines == 0)
		error("there is no map", 15);
	charcheck(build->map.array);
	rule_one(build->map.array[0], build->map.array[1]);
	while (y < lines - 1)
	{
		middel_part(build->map.array[y], build->map.array[y + 1]);
		y++;
	}
	start_pos(build);
	if (!build->cor.validstartpost)
		error("no start position", 17);
	rule_last(build->map.array[y]);
}

static int				space_tab(char *str)
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

static void				dis_res(double *res_x, double *res_y)
{
	int		maindisplayid;
	int		pixelswidth;
	int		pixelsheight;

	maindisplayid = CGMainDisplayID();
	pixelswidth = CGDisplayPixelsWide(maindisplayid);
	pixelsheight = CGDisplayPixelsHigh(maindisplayid);
	if (*res_x > pixelswidth)
		*res_x = pixelswidth;
	if (*res_y > pixelsheight)
		*res_y = pixelsheight;
}

void					read_string(t_build *build)
{
	int rule;

	rule = 0;
	initialise(build);
	while (build->map.array[build->data.rule])
		build->data.rule++;
	while (*build->map.array && rule < 8)
	{
		check_input(*build->map.array, build);
		build->map.array++;
		rule++;
	}
	if (!build->data.north || !build->data.south || \
	!build->data.west || !build->data.east || !build->data.floor \
	|| !build->data.ceiling || !build->data.res || !build->data.sprite)
		error("not a valid map", 15);
	dis_res(&build->data.res_x, &build->data.res_y);
	while (space_tab(*build->map.array) == 0 || *build->map.array == 0)
		build->map.array++;
	check_valid_map(build);
}
