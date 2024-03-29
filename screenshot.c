/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 13:51:27 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/30 18:09:18 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			arg_check(t_build *build, char *str)
{
	char	*check;
	int		i;

	check = "--save";
	i = 0;
	while (check[i])
	{
		if (check[i] != str[i])
			error("2 argument invalid", 18);
		i++;
	}
	if (str[i] != '\0')
		error("2 argument invalid", 18);
	build->data.scrsht = 1;
	return ;
}

static void		header_bmp(int fd, int width, int height)
{
	int		size;
	int		first_pix;
	int		headersize;
	short	plain;
	short	bpp;

	headersize = 40;
	plain = 1;
	bpp = 32;
	first_pix = 54;
	size = height * width * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	write(fd, &headersize, 4);
	write(fd, &width, 4);
	write(fd, &height, 4);
	write(fd, &plain, 2);
	write(fd, &bpp, 2);
	while (plain <= 24)
	{
		write(fd, "\0", 1);
		plain++;
	}
}

static void		put_pixel(int fd, int width, int height, t_build *build)
{
	int		x;
	int		length;
	char	*addr;

	addr = build->img.addr;
	length = 0;
	if (width % 64 != 0)
		length = 1;
	length = (length + (width / 64)) * 256;
	x = 0;
	height -= 1;
	while (height >= 0)
	{
		while (x < width)
		{
			write(fd, &addr[height * build->img.line_length + x * 4], 4);
			x++;
		}
		x = 0;
		height--;
	}
}

void			make_bmp(char *name, t_build *build)
{
	int		fd;
	int		width;
	int		height;

	fd = open(name, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		error_total("cant open BMP", 13, build);
	width = build->data.res_x;
	height = build->data.res_y;
	header_bmp(fd, width, height);
	put_pixel(fd, width, height, build);
	exit(0);
}
