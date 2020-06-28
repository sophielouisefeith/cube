/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/28 15:37:12 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <CoreGraphics/CGDirectDisplay.h>

void	check_input(char *str, t_build *build)
{
	int i;

	i = 0;
	while ((str[i] == ' ' || str[i] == 9) && str[i])
		i++;
	if (str[i] == 'R' && str[i + 1] == ' ' && build->data.check_res != 1)
		check_res(str, build);
	if (str[i] == 'F' && str[i + 1] == ' ')
		check_color(str, build);
	if (str[i] == 'C' && str[i + 1] == ' ')
		check_color(str, build);
	if (str[i] == 'S' && str[i + 1] == ' ' && str[i + 2] == '.')
		build->data.sprite = check_path(str);
	if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == \
	' ' && str[i + 3] == '.')
		build->data.north = check_path(str);
	if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == \
	' ' && str[i + 3] == '.')
		build->data.south = check_path(str);
	if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == \
	' ' && str[i + 3] == '.')
		build->data.west = check_path(str);
	if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == \
	' ' && str[i + 3] == '.')
		build->data.east = check_path(str);
}

void	initialise(t_build *build)
{
	build->cor.validstartpost = 0;
	build->data.count = 0;
	build->data.rule = 0;
	build->data.res_x = 0;
	build->data.res_y = 0;
	build->data.check_res = -1;
	build->data.floor = -1;
	build->data.ceiling = -1;
	build->data.color_r = -1;
	build->data.color_g = -1;
	build->data.color_b = -1;
	build->data.check_color = 0;
	build->data.check_res = 0;
	build->data.size_map = 0;
	build->data.count = 0;
	build->ray.time = 0;
	build->ray.oldirx = 0;
	build->ray.oldplanex = 0;
	build->ray.oldplaney = 0;
	build->ray.side = 0;
	build->ray.drawstart = 0;
	build->ray.drawend = 0;
	build->sprite.num = 0;
	build->img.mlx = NULL;
	build->img.win = NULL;
}

void	checkmap(char *str)
{
	int i;

	i = ft_strlen(str);
	i--;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c' && \
	str[i - 3] == '.')
		return ;
	else
		error("incorrect name", 16);
}

static void		charcheck(char **str)
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

void	check_valid_map(t_build *build)
{
	int lines;
	int y;

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

static int		space_tab(char *str)
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

static void	dis_res(double *res_x, double *res_y)
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

void	read_string(t_build *build)
{
	int rule;

	rule = 0;
	initialise(build);
	while (build->map.array[build->data.rule])
		build->data.rule++;
	while (*build->map.array && rule < 8)
	{
		check_input(*build->map.array, build);
		// free(*build->map.array);
		build->map.array++;
		rule++;
	}
	dis_res(&build->data.res_x, &build->data.res_y);
	while (space_tab(*build->map.array) == 0 || *build->map.array == 0)
		build->map.array++;
	check_valid_map(build);
}
