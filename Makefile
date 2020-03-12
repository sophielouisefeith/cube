# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sfeith <sfeith@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/28 12:24:37 by sfeith         #+#    #+#                 #
#    Updated: 2020/03/12 11:42:27 by sfeith        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
MLX = minilibx
LIBMLX = libmlx.dylib
SRC = utilities.c readmap.c mainread.c data.c data_check.c error.c
#OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
# You may also need to specify the path to the  MiniLibX  library,  using the -L flag.
LINKING = -lmlx -framework OpenGL -framework AppKit
all: $(NAME)
$(NAME): $(LIBMLX) $(OBJ)
	gcc $(FLAGS) -I $(MLX) -L $(MLX) $(LINKING) $(SRC)
#$(LIBMLX):
#   @make -C $(MLX)
#   @cp $(MLX)/$(LIBMLX) .
clean:
	make clean -C $(MLX)
	$(RM) $(OBJ) a.out
fclean: clean
	$(RM) $(NAME)
re: fclean all