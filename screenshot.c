/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 13:51:27 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/15 17:05:58 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	header_bmp(int fd, int width, int height)
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

static void	put_pixel(int fd, char *addr, int width, int height)
{
	int x;
	int length;

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
			write(fd, &addr[height * length + x * 4], 4);
			x++;
		}
		x = 0;
		height--;
	}
}

void	make_bmp(char *name, t_build *build)
{
	int		fd;
	char	*addr;
	int		width;
	int		height;

	fd = open(name, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		error("cant open BMP", 13);
	addr = build->img.addr;
	width = build->data.res_x;
	height = build->data.res_y;
	header_bmp(fd, width, height);
	put_pixel(fd, addr, width, height);
	free_game(build);
	exit(0);
}
