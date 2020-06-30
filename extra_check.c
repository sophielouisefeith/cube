/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 16:03:01 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/30 18:04:22 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			path_check(char *str, int i, t_build *build)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
	{
		i = 3;
		build->data.north = check_path(str, i);
	}
	if (str[i] == 'S' && str[i + 1] == 'O')
	{
		i = 3;
		build->data.south = check_path(str, i);
	}
	if (str[i] == 'W' && str[i + 1] == 'E')
	{
		i = 3;
		build->data.west = check_path(str, i);
	}
	if (str[i] == 'E' && str[i + 1] == 'A')
	{
		i = 3;
		build->data.east = check_path(str, i);
	}
}

static void		middel_part_second(char *str1, char *str2, int len1, int len2)
{
	if (len1 > len2)
		while (len2 < len1)
		{
			if (str1[len2] != '1')
				error("not a protected map", 19);
			len2++;
		}
	if (len1 < len2)
	{
		while (len1 < len2)
		{
			if (str2[len1] == ' ')
				error("black whole/wall is not protected with 1", 40);
			len1++;
		}
	}
}

void			black_whole(char *str1, int x)
{
	int spatie;
	int xinside;

	spatie = 0;
	xinside = x;
	while (str1[xinside] == '1' || str1[xinside] == '0' || str1[xinside] == ' ')
	{
		if (str1[xinside] == ' ')
			spatie++;
		if (spatie == 1 && str1[xinside] == ' ')
			error("black hole", 11);
		xinside++;
	}
}

void			edge(int x2, int x, char *str1, char *str2)
{
	int len1;
	int len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (x2 >= x)
	{
		if (str1[x2] == '0')
			if (str2[x2 - 1] != '1')
				error("not a protected map", 20);
	}
	if (len1 < len2)
	{
		if (str2[len1 - 1] != '1')
			error("not a protected la", 20);
	}
}

void			middel_part(char *str1, char *str2)
{
	int x;
	int x2;
	int len1;
	int len2;

	x2 = 0;
	x = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	while (str1[x] == 9 || str1[x] == ' ')
		x++;
	black_whole(str1, x);
	while (str2[x2] == 9 || str2[x2] == ' ')
		x2++;
	if (str1[x] != '1' || str1[len1 - 1] != '1')
		error("not a protected map", 18);
	while (x2 <= x)
	{
		if (str2[x2] != '1')
			error("to many space in map", 20);
		x2++;
	}
	edge(x2, x, str1, str2);
	x--;
	middel_part_second(str1, str2, len1, len2);
}
