// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   sprite.c                                           :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2020/04/28 10:23:38 by SophieLouis    #+#    #+#                */
// /*   Updated: 2020/06/02 15:04:18 by sfeith        ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(double *spritedistance, t_build *build)
{
	int		i;
	int		tmp;
	double	tmp2;

	i = 0;
	while (i < (build->sprite.num - 1))
	{
		if (spritedistance[i] < spritedistance[i + 1])
		{
			tmp2 = spritedistance[i + 1];
			spritedistance[i] = spritedistance[i + 1];
			spritedistance[i + 1] = tmp2;
			tmp = build->sprite_s.sprite_cor[i][0];
			build->sprite_s.sprite_cor[i][0] = \
			build->sprite_s.sprite_cor[i + 1][0];
			build->sprite_s.sprite_cor[i + 1][0] = tmp;
			tmp = build->sprite_s.sprite_cor[i][1];
			build->sprite_s.sprite_cor[i][1] =\
			build->sprite_s.sprite_cor[i + 1][1];
			build->sprite_s.sprite_cor[i + 1][1] = tmp;
			i = -1;
		}
		i++;
	}
}

static void		makesprite(t_build *build)
{
	int x;
	int color;
	int d;
	int y;

	x = 0;
	d = 0;
	y = build->sprite.drawstarty;
	while (y < build->sprite.drawendy)
	{
		d = y * 256 - build->data.res_y * \
		128 + build->sprite.spriteheight * 128;
		build->sprite.texy = ((d * 64) / build->sprite.spriteheight) / 256;
		color = *(unsigned int*)(build->sprite.dataadres + \
		(build->sprite.texy * build->sprite.line_length
		+ build->sprite.texx * (build->sprite.bpp / 8)));
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(build, build->sprite.stripe, y, color);
		y++;
	}
}

void	calc_sprites(t_build *build)
{
	build->sprite.spritescreenx = (int)build->data.res_x / 2 * \
	(1 + build->sprite.transformx / build->sprite.transformy);
	build->sprite.spriteheight = fabs(build->data.res_y / \
	(double)(build->sprite.transformy));
	build->sprite.drawstarty = -build->sprite.spriteheight \
	/ 2 + build->data.res_y / 2;
	if (build->sprite.drawstarty < 0)
		build->sprite.drawstarty = 0;
	build->sprite.drawendy = build->sprite.spriteheight / 2 + \
	build->data.res_y / 2;
	if (build->sprite.drawendy >= build->data.res_y)
		build->sprite.drawendy = build->data.res_y - 1;
	build->sprite.spritewidth = fabs((build->data.res_y / \
	(build->sprite.transformy)));
	build->sprite.drawstartx = (-build->sprite.spritewidth / 2) \
	+ build->sprite.spritescreenx;
	if (build->sprite.drawstartx < 0)
		build->sprite.drawstartx = 0;
	build->sprite.drawendx = build->sprite.spritewidth / 2 \
	+ build->sprite.spritescreenx;
	if (build->sprite.drawendx >= build->data.res_x)
		build->sprite.drawendx = build->data.res_x - 1;
}

static void		order(t_build *build)
{
	int		i;
	int		width;
	int		height;
	double	spritedistance[build->sprite.num];
	char	*path;

	path = build->data.sprite;
	if (!(build->sprite.sprite_tex = mlx_xpm_file_to_image(build->img.mlx,\
	path, &width, &height)))
		error_game("malloc failed", 13, build);
	if (!(build->sprite.dataadres = mlx_get_data_addr(build->sprite.sprite_tex,\
	&build->sprite.bpp, &build->sprite.line_length, &build->sprite.endian)))
		error_game("malloc failed", 13, build);
	i = 0;
	while (i < build->sprite.num)
	{
		spritedistance[i] = ((build->cor.start_pos_x \
		- build->sprite_s.sprite_cor[i][0]) * \
		(build->cor.start_pos_x - build->sprite_s.sprite_cor[i][0]) +
		(build->cor.start_pos_y - build->sprite_s.sprite_cor[i][1]) * \
		(build->cor.start_pos_y - build->sprite_s.sprite_cor[i][1]));
		i++;
	}
	sort_sprites(spritedistance, build);
}

static int	loop(t_build *build)
{
	build->sprite.stripe = build->sprite.drawstartx;
	while (build->sprite.stripe < build->sprite.drawendx)
	{
		build->sprite.texx = (int)(256 * (build->sprite.stripe\
		- (-build->sprite.spritewidth / 2 + build->sprite.spritescreenx))\
		* textwidth / build->sprite.spritewidth / 256);
		if (build->sprite.transformy > 0 && build->sprite.stripe > 0 \
		&& build->sprite.stripe < build->data.res_x && \
		build->sprite.transformy < build->sprite.zbuffer[build->sprite.stripe])
			makesprite(build);
		build->sprite.stripe++;
	}
	return (0);
}

void	sprite(t_build *build)
{
	int	i;

	i = 0;
	order(build);
	while (i < build->sprite.num)
	{
		build->sprite.spritex = build->sprite_s.sprite_cor[i][0] \
		- build->cor.start_pos_x + 0.5;
		build->sprite.spritey = build->sprite_s.sprite_cor[i][1] \
		- build->cor.start_pos_y + 0.5;
		build->sprite.invdet = 1.0 / (build->ray.planex * build->cor.diry \
		- build->cor.dirx * build->ray.planey);
		build->sprite.transformx = (build->sprite.invdet * (build->cor.diry *\
		build->sprite.spritex - build->cor.dirx * build->sprite.spritey));
		build->sprite.transformy = build->sprite.invdet * (-build->ray.planey \
		* build->sprite.spritex + build->ray.planex * build->sprite.spritey);
		if( build->ray.x_cam == 1)
        	build->sprite.transformx *= -1;
		calc_sprites(build);
		loop(build);
		i++;
	}
}
