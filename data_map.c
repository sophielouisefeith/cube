/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 13:11:59 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/30 18:15:34 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			rule_onesecond(char *str1, int x, char *str2)
{
	int len1;
	int len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	while (str1[x] != '\0')
	{
		if (str1[x] != '1')
			error("not valid first rule", 20);
		x++;
	}
	x--;
	if (len1 < len2)
	{
		while (str2[x] != '\0')
		{
			if (str2[x] != '1')
				error("not valid first rule", 20);
			x++;
		}
	}
}

void				rule_one(char *str1, char *str2)
{
	int len1;
	int len2;
	int x;
	int x2;

	x2 = 0;
	x = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	while (str1[x] == 9 || str1[x] == ' ')
		x++;
	while (str2[x2] == 9 || str2[x2] == ' ')
		x2++;
	while (x2 <= x)
	{
		if (str2[x2] != '1')
			error("not valid first rule", 20);
		x2++;
	}
	rule_onesecond(str1, x, str2);
}

void				rule_last(char *str)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] != '1')
			error("not a valid last rule", 21);
		x++;
	}
}
