/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:54:42 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/03 21:14:47 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_img			
{
	void		*img1;
	char		*addr;
	int			bits_per_pixel;		
	int			line_length;		
	int			endian;				
 	void	    *mlx;
 	void	    *win1;
}				t_img;

typedef struct	s_var
{
	int		    x;
	int		    y;
}				t_var;				

typedef struct	s_cub
{
	t_img		*img;
	t_var		var;
}				t_cub;

void            my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void    		square(t_cub *cub);
char			**ft_savemap(char const *s, const int fd);


char	*get_next_line(const int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);





