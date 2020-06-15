/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilssecond.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 15:57:45 by sfeith        #+#    #+#                 */
/*   Updated: 2020/06/15 17:09:06 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_game(t_build *build)
{
    free_game(build);
	mlx_destroy_window(build->img.mlx, build->img.win);
	exit(0);
}
