# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sfeith <sfeith@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/28 12:24:37 by sfeith        #+#    #+#                  #
#    Updated: 2021/04/28 11:31:02 by sfeith        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
MLX = minilibx
LIBMLX = libmlx.a
SRC = cub3d.c utilities.c readmap.c  data.c data_check.c  \
		data_map.c  start_pos.c raycast.c move.c  mainread.c texture.c \
		sprite.c screenshot.c lines.c utilssecond.c error_free.c extra_check.c
LINKING = -lmlx  -framework OpenGL -framework AppKit
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -o cub3D -O3

RESET			= 	\033[0m
GREEN 			= 	\033[38;5;46m
WHITE 			= 	\033[38;5;15m
GREY 			= 	\033[38;5;8m
ORANGE 			= 	\033[38;5;202m
RED 			= 	\033[38;5;160m

all: $(LIBMLX) $(NAME)

$(NAME): $(LIBMLX)
	gcc $(FLAGS) -I $(MLX) -L $(MLX) $(LINKING) $(SRC)

$(LIBMLX):
	make -C $(MLX)
	@echo "$(GREEN)Executable: ./cub3D map.cub $(RESET)"
clean:
	make clean -C $(MLX)
	$(RM) $(OBJ) screenshot.bmp cub3D

fclean: clean
	$(RM) $(NAME)

re: fclean all
