/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmourik <mmourik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 09:21:21 by mmourik        #+#    #+#                */
/*   Updated: 2020/02/28 15:50:29 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
    char    *dst;

    dst = cub->img->addr + (y * cub->img->line_length + x * (cub->img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}