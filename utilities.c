/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 13:18:17 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/06/04 16:59:29 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_build *build)
{
	mlx_destroy_window(build->img.mlx, build->img.win);
	exit(0);
}

void            my_mlx_pixel_put(t_build *build, int x, int y, int color)
{
    char    *dst;
    dst = build->img.addr + (y * build->img.line_length + x * (build->img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

char			*ft_strdup(const char *s1)
{
	int		len;
	char	*str;

	len = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str == 0)
		return (0);
	while (s1[len])
	{
		str[len] = s1[len];
		len++;
	}
	str[len] = '\0';
	return (str);
}

static char		*ft_strcpy(char *dest, char const *src1, char const *src2)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (src1[i] != '\0')
	{
		dest[i] = src1[i];
		i++;
	}
	while (src2[c] != '\0')
	{
		dest[i] = src2[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strjoin(char *s1, char *s2)
{
	size_t		s1len;
	size_t		s2len;
	char		*ns;

	if (!s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ns = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (ns == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strcpy(ns, s1, s2);
	free(s1);
	free(s2);
	return (ns);
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

char			*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	srclen;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL)
	{
		free(s);
		return (NULL);
	}
	while (i < len && start < srclen)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

size_t				ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

int	ft_isdigit(int c)
{
	int i;

	i = 0;
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}