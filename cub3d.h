/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:54:42 by sfeith         #+#    #+#                */
/*   Updated: 2020/03/10 19:28:24 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

// # ifndef DATA
// #  define DATA build.
// # endif

typedef struct s_map //------------to open the map and safe 3Darray-----------------------------------
{

	char	*str;
	char 	**array;
}
				t_map;
				
typedef struct s_data //-------------to collect and validate information---------------------
{
	char	*str;
	int		res_x;
	int		res_y;
	int		check_res;
	int		floor;
	int		ceiling;
	int 	color_r;
	int 	color_g;
	int		color_b;
	int		check_color;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	
}
				t_data;
							

typedef struct	s_build   // Umbrella struct 
{
	// t_img		*img;
	// t_cor		cor;
	t_map			map;
	t_data			data; 
}				t_build;

//--------------------------------- Opens the file reads in then safe first a string and then dubbel array--------------------------
t_build			*savearray(char *argv);
//-----------------------------------Will check all the strings------------------------------------------------------------------
void 	read_string(t_build *build);
//-----------------------------------will read the arrays and saves it in data------------------------
void	check_res(char *str, t_build *build);
int		check_color(char *str, t_build *build);
char	*check_path(char *str);
void	check_input(char *str, t_build *build);
//--------------------------------image building -------------------------------
void            my_mlx_pixel_put(t_build *build, int x, int y, int color);
void    		image(t_build *build);
//---------------------------------------utilities------------------------------------
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
//---------------------------------------------------------------------------------------






















// typedef struct s_img	// Building the image 
// {
// 	void		*img1;
// 	char		*addr;
// 	int			bits_per_pixel;		
// 	int			line_length;		
// 	int			endian;				
//  	void	    *mlx;
//  	void	    *win1;
// }				t_img;

// typedef struct	s_cor //---------- coordinates-----------------------------------
// {
// 	int		    x;
// 	int		    y;
// }				t_cor;		
