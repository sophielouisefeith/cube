/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 13:40:29 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/23 14:51:23 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rules(int i, t_build *build)
{
	if (i == 0)
		return ;
	while (i > 0)
	{
		i--;
		if (build->map.array[i])
			free(build->map.array[i]);
	}
	free(build->map.array);
	return ;
}

void	free_sprites(int i, double **sprite_cor)
{
	if (i == 0)
		return ;
	while (i > 0)
	{
		i--;
		if (sprite_cor[i])
			free(sprite_cor[i]);
	}
	return ;
}

void	free_game(t_build *build)
{
	free_rules(build->data.rule, build);
	free_sprites(build->sprite.num, build->sprite_s.sprite_cor);
	if (build->sprite.zbuffer)
		free(build->sprite.zbuffer);
	if (build->sprite.sprite_tex)
		free(build->sprite.sprite_tex);
	if (build->data.north)
		free(build->data.north);
	if (build->data.south)
		free(build->data.south);
	if (build->data.west)
		free(build->data.west);
	if (build->data.east)
		free(build->data.east);
	if (build->data.sprite)
		free(build->data.sprite);
	free(build);
}

void	free_map(t_build *build)
{
	if (build->data.north)
		free(build->data.north);
	if (build->data.south)
		free(build->data.south);
	if (build->data.west)
		free(build->data.west);
	if (build->data.east)
		free(build->data.east);
	free_rules(build->data.rule, build);
	free_sprites(build->sprite.num, build->sprite_s.sprite_cor);
	free(build);
}
