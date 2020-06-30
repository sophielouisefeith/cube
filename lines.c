/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lines.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 14:05:20 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/30 18:05:26 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char			*ft_treatment(char *new, int ret, int fd)
{
	char	*buf;

	while (ret > 0)
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buf == 0)
		{
			free(new);
			return (NULL);
		}
		ret = (read(fd, buf, BUFFER_SIZE));
		if (ret == -1)
		{
			free(buf);
			free(new);
			return (NULL);
		}
		buf[ret] = '\0';
		new = ft_strjoin(new, buf);
		if (new == NULL)
			return (NULL);
	}
	return (new);
}

char				*get_next_line(const int fd)
{
	int			ret;
	static char *new;

	ret = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (new == NULL)
		new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	new = ft_treatment(new, ret, fd);
	if (new == NULL)
		return (NULL);
	return (new);
}

void				checkmap(char *str)
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

void				check_input(char *str, t_build *build)
{
	int i;

	i = 0;
	while ((str[i] == ' ' || str[i] == 9) && str[i])
		i++;
	if (str[i] == 'R' && str[i + 1] == ' ' && build->data.check_res != 1)
		check_res(str, build);
	if (str[i] == 'F')
		check_color(str, build);
	if (str[i] == 'C')
		check_color(str, build);
	if (str[i] == 'S' && str[i + 1] != 'O')
	{
		i = 2;
		build->data.sprite = check_path(str, i);
	}
	path_check(str, i, build);
}

void				initialise(t_build *build)
{
	build->cor.validstartpost = 0;
	build->data.res = 0;
	build->data.count = 0;
	build->data.rule = 0;
	build->data.floor = -1;
	build->data.ceiling = -1;
	build->data.color_r = -1;
	build->data.color_g = -1;
	build->data.color_b = -1;
	build->ray.movespeed = 0;
	build->ray.rotspeed = 0;
	build->ray.oldirx = 0;
	build->data.check_color = 0;
	build->data.check_res = 0;
	build->data.size_map = 0;
	build->data.count = 0;
	build->ray.oldplanex = 0;
	build->ray.oldplaney = 0;
	build->ray.side = 0;
	build->ray.drawstart = 0;
	build->ray.drawend = 0;
	build->sprite.num = 0;
	build->img.mlx = NULL;
	build->img.win = NULL;
}
