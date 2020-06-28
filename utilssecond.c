/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilssecond.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 15:57:45 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/28 17:04:21 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_build *build)
{
	if (build->img.win)
		mlx_destroy_window(build->img.mlx, build->img.win);
	if (build->img.img1)
		mlx_destroy_image(build->img.mlx, build->img.img1);
	if (build->tex.texture)
		mlx_destroy_image(build->img.mlx, build->tex.texture);
	free(build);
	exit(0);
}

int	ft_isdigit(int c)
{
	int i;

	i = 0;
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_atoi(const char *str)
{
	int						i;
	unsigned long long		b;
	int						mp;

	i = 0;
	b = 0;
	mp = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		mp = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && (str[i] <= '9'))
	{
		if (b >= 9223372036854775808ULL && mp == 1)
			return (-1);
		if (b >= 9223372036854775809ULL && mp == -1)
			return (0);
		b = b * 10 + str[i] - '0';
		i++;
	}
	return ((int)mp * b);
}

void	my_mlx_pixel_put(t_build *build, int x, int y, int color)
{
	char *dst;

	dst = build->img.addr + (y * build->img.line_length + x * \
	(build->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

char			*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	if (*s == c)
		return ((char*)s);
	return (0);
}
