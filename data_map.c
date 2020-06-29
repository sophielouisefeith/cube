/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/26 15:58:16 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/06/29 14:49:45 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		rule_onesecond(char *str1, int x, char *str2)
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

void	rule_one(char *str1, char *str2)
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

static void		middel_part_second(char *str1, char *str2, int len1, int len2)
{
	if (len1 > len2)
		while (len2 < len1)
		{
			if (str1[len2] != '1')
				error("6 middel", 8);
			len2++;
		}
	if (len1 < len2)
	{
		while (len1 < len2)
		{
			if( str2[len1] == ' ' )  // dit was eerst str2]len2] == !1 || str2[len2] == !1 || str2[len2] == !0 || str2[len2] == !2 ) 
				error("black whole/wall is not protected with 1", 40);
			len1++;
		}
	}
}

void	black_whole(char *str1, int x)
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

void	middel_part(char *str1, char *str2)
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
		error("4 middel", 8);
	while (x2 <= x)
	{
		if (str2[x2] != '1')
			error("to many space in map", 20);
		x2++;
	}
	x--;
	middel_part_second(str1, str2, len1, len2);
}

void	rule_last(char *str)
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
