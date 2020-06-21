/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 17:21:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/21 17:19:25 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_res(char *str, t_build *build)
{
	int i;

	i = 1;
	while ((str[i] == ' ' || str[i] == 9) && str[i])
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		build->data.res_x = build->data.res_x * 10 + str[i] - '0';
		i++;
	}
	while ((str[i] == ' ' || str[i] == 9) && str[i])
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		build->data.res_y = build->data.res_y * 10 + str[i] - '0';
		i++;
	}
	if (build->data.res_x && build->data.res_y && str[i])
	{
		i++;
		if (str[i] == ' ' || str[i] >= '0')
			error("to many res", 11);
	}
}

int		create_trgb(int r, int g, int b, t_build *build)
{
	int color;

	color = (r << 16 | g << 8 | b);
	build->data.color_r = 0;
	build->data.color_g = 0;
	build->data.color_b = 0;
	build->data.check_color = 0;
	return (color);
}

int		define_color(char *str, t_build *build, int *i)
{
	int color;

	color = 0;
	while ((str[*i] == ' ' || str[*i] == 9) && str[*i])
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9' && str[*i])
	{
		color = color * 10 + str[*i] - '0';
		(*i)++;
		if (color < 0 || color > 255)
			return (-1);
	}
	if (str[*i] == ',')
		(*i)++;
	if (!ft_isdigit(str[*i]) && str[*i] != '\0')
		return (-1);
	build->data.check_color++;
	return (color);
}

void	check_color(char *str, t_build *build)
{
	int i;

	i = 0;
	if (str[i] == 'F')
		build->data.floor = 1;
	if (str[i] == 'C')
		build->data.ceiling = 1;
	i++;
	while ((str[i] == ' ' || str[i] == 9) && str[i])
		i++;
	build->data.color_r = define_color(str, build, &i);
	if (build->data.color_r == -1)
		error("color r", 7);
	build->data.color_g = define_color(str, build, &i);
	if (build->data.color_g == -1)
		error("color g", 7);
	build->data.color_b = define_color(str, build, &i);
	if (build->data.color_b == -1)
		error("color b", 7);
	if ((build->data.check_color < 4) && build->data.floor == 1)
		build->data.floor = create_trgb(build->data.color_r,\
		build->data.color_g, build->data.color_b, build);
	if ((build->data.check_color < 4) && build->data.ceiling == 1)
		build->data.ceiling = create_trgb(build->data.color_r,\
		build->data.color_g, build->data.color_b, build);
}

char	*check_path(char *str)
{
	int		i;
	char	*temp;
	size_t	len;

	i = 0;
	while (str[i] != '.' && str[i + 1] != 'x')
		i++;
	len = ft_strlen(str);
	temp = ft_substr(str, i, len);
	return (temp);
}
