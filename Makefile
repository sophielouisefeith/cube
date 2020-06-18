# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sfeith <sfeith@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/28 12:24:37 by sfeith        #+#    #+#                  #
#    Updated: 2020/06/18 10:59:02 by sfeith        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
MLX = minilibx
LIBMLX = libmlx.a
SRC = cub3d.c utilities.c readmap.c  data.c data_check.c error.c \
		data_map.c  start_pos.c raycast.c move.c  mainread.c texture.c \
		sprite.c screenshot.c lines.c utilssecond.c free.c
LINKING = -lmlx  -framework OpenGL -framework AppKit
#OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -g -Wno-deprecated-declarations
# remove debugger flag later

all: $(LIBMLX) $(NAME)

$(NAME): $(LIBMLX) $(OBJ)
	gcc $(FLAGS) -I $(MLX) -L $(MLX) $(LINKING) $(SRC)

$(LIBMLX):
	make -C $(MLX)

clean:
	make clean -C $(MLX)
	$(RM) $(OBJ) a.out

fclean: clean
	$(RM) $(NAME)

re: fclean all