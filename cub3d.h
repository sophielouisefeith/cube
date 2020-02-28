/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:54:42 by sfeith         #+#    #+#                */
/*   Updated: 2020/02/28 18:34:43 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_img			//image en window
{
	void		*img1;
	char		*addr;
	int			bits_per_pixel;		//stores the number of bits needed to represent a pixel color
	int			line_length;		//stores the number of bytes used to store one line of the image in memory
	int			endian;				//tells wether the pixel color in the image needs to be stored in 
 	void	    *mlx;
 	void	    *win1;
}				t_img;

typedef struct	s_var
{
	int		    x;
	int		    y;
}				t_var;				//little endian (endian == 0), or big endian(endian == 1)

typedef struct	s_cub
{
	t_img		*img;
	t_var		var;
}				t_cub;

void            my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void    		square(t_cub *cub);