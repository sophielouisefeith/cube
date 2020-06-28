/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lines.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 14:05:20 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/28 16:40:27 by sfeith        ########   odam.nl         */
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
