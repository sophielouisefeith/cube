/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 12:54:42 by sfeith        #+#    #+#                 */
/*   Updated: 2020/05/13 13:45:29 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>


#define screenWidth 640 
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24
#define textwidth 64
#define textheight 64
#define numsprites 3


// # ifndef DATA
// #  define DATA build.
// # endif

typedef struct s_sprite_s
{
	int x;
	int y;
	char **sprite_s;
	
}		t_sprite_s;

typedef struct s_sprite
{
	double  *zbuffer;
	double		spriteorder[numsprites];  //*
	double  spritedistance[numsprites]; //*
	int 	num;
	//int		numsprites;
	double  spritex;
	double  spritey;
	double  invdet;
	double transformx;
	double transformy;
	int	spritescreenx;
	int		spriteheight;
	int 	drawstarty;
	int		drawstartx;
	int 	drawendy;
	int		drawendx;
	int 	spritewidth;
	int		texx;
	int 	d;
	int 	y;
	int		x;
	int 	texy;
	int 	stripe;
	void	*sprite_tex;
	char	*dataadres;
	int			bpp;
	int		endian;
	int     line_length;
	int		width;
	int		height;
	char	*sprite_cor;
	
	
	

}				t_sprite;

typedef struct s_tex
{
	int 	texnum;
	double  wallx;
	int 	texx;
	double  step;
	double  texpos;
	int 	texy;
	void  	*texture;
	void  	*texture_w;
	char *dataadres;
	int			bpp;
	int		endian;
	int     line_length;
	int		width;
	int		height;

}				t_tex;

typedef struct s_ray 
{
	double time;
	double oldtime;
	double frametime;
	double movespeed;
	double rotspeed;
	double oldirx;
	double oldplanex;
	double oldplaney;
	double planex;
	double planey;
	int		moveup;
	int		movedown;
	int		moveright;
	int		moveleft;
	int		update;
	double camerax;
	double raydiry;
	double raydirx;
	int hit;	
	int side;
	double perpwalldist;
	int		drawstart;
	int		drawend;
	double 	lineheight;
	int		stepx;
	int 	stepy;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	//double camerax;
	
}				t_ray;
				

typedef struct s_img	// Building the image 
{
	void		*img1;
	char		*addr;
	int			bits_per_pixel;		
	int			line_length;		
	int			endian;				
 	void	    *mlx;
 	void	    *win;
	int			floor;
	int			*fill;
	// int			bpp;		
}				t_img;

typedef struct	s_cor //---------- coordinates-----------------------------------
{
	int		start_pos_x; //double
	int		start_pos_y; //double
	int		mapx;
	int 	mapy;
	double	dirx;
	double	diry;
}				t_cor;		

typedef struct s_map //------------to open the map and safe 3Darray-----------------------------------
{

	char	*str;
	char 	**array;
}				t_map;
			
				
typedef struct s_data //-------------to collect and validate information---------------------
{
	char	*str;
	double	res_x;
	double	res_y;
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
	int		error_i;
	int		n;
	int		size_map;
	int		len_be;
	int		len_middel;	
	int		count;
}			t_data;
				
typedef struct				s_sprite_cor    
{				
	char			*sprite_cor;	
	int x;
	int y;
		
}			t_sprite_cor;

typedef struct	s_build   // Umbrella struct 
{
	t_img		img;
	t_cor		cor;
	t_map		map;
	t_data		data; 
	t_ray       ray;
	t_tex		tex;
	t_sprite	sprite;
	//t_sprite_cor    *sprites_cor;
	t_sprite_s	sprite_s[numsprites];
}				t_build;

int	close_game(t_build *build);

//--------------------------------- Opens the file reads in then safe first a string and then dubbel array--------------------------
t_build			*savearray(char *argv);
//-----------------------------------Will check all the strings------------------------------------------------------------------
void 	read_string(t_build *build);
//-----------------------------------will read the arrays and saves it in data------------------------
void	check_res(char *str, t_build *build);
void	check_color(char *str, t_build *build);
int		create_trgb(int r, int g, int b, t_build *build);
char	*check_path(char *str);
void	check_input(char *str, t_build *build);
void 	initialize(t_build *build);
int		define_color(char *str, t_build *build, int *i);
//---------------------------------valid map----------------------------
void    rule_one(char *str1, char *str2);

void	middel_part(char *str1, char *str2);
void    rule_last(char *str);
void    count_rules(int y, t_build *build);
void    start_pos(int y, t_build *build);
//---------------------------------error warning----------------------------
void 			error(char *str);
//--------------------------------image building/raycasting -------------------------------
void            my_mlx_pixel_put(t_build *build, int x, int y, int color);
void    		square(t_build *build);
int   			presskey(int keycode, t_build *build);
int     		ray(t_build *build);
void         	move(t_build *build);
int				startgame(t_build *build);
int   			fill(int x, t_build *build);
void           floor_ceiling(t_build *build);
char    		*side(t_build *build);
//void			loop(t_build *build);
//int				render(t_build *build);

//---------------------------------------sprites------------------------------------------
void	 		sprite(t_build *build);
//void  			locate_sprites(t_build *build);
//void 			order_sprites(t_build *build);
//void 			sort_sprites(t_build *build);	
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














