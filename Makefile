# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 15:59:26 by f██████           #+#    #+#              #
#    Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = $(SRCS:.c=.o)
SRCS = main.c \
	sources/hooks/loop_hook.c sources/hooks/key_hook.c \
	sources/mlx/set_up_image.c sources/mlx/mlx_pixel_put.c \
		sources/mlx/exit_game.c sources/player/set_up_player.c \
	sources/player/move_player.c sources/player/look_player.c \
		sources/player/action_player.c \
	sources/algorithms/step_and_player_to_grid.c sources/algorithms/dda.c \
		sources/algorithms/floor_and_ceiling.c \
	sources/textures/load_textures.c \
	sources/parsing/map_parsing.c sources/parsing/map_file_parsing.c \
		sources/parsing/map_parsing_utils.c \
		sources/parsing/color_element_parsing.c \
		sources/parsing/texture_element_parsing.c \

CC = gcc
MF = Makefile

ifeq ($(DEBUG), 1)
  CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
else
  CFLAGS = -Wall -Wextra -Werror
endif

UNAME = $(shell uname -s)
LIBFT_PATH = ./libft/libft.a
NAME = cub3D
MS_HEADER_FILE = includes/cub3d.h

ifeq ($(UNAME),Darwin)
  GFLAGS = -L -lmlx -framework OpenGL -framework AppKit
  GPATH = ./mlx-opengl/
  MLX_PATH = $(GPATH)/libmlx.a
else
  GFLAGS = -L -lmlx -lXext -lX11 -lbsd
  GPATH = ./mlx-linux/
  MLX_PATH = $(GPATH)/libmlx.a
endif

all : _mlx _libft $(NAME)

$(NAME) : $(MF) $(OBJS) $(MLX_PATH) $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJS) -lm $(MLX_PATH) $(GFLAGS) $(LIBFT_PATH) -o $(NAME)
	@echo "\n${GREEN}> Compilation of cub3d is success 🎉${END}"

%.o : %.c $(MS_HEADER_FILE) $(MF)
	@/bin/echo -n .
	@$(CC) $(FLAGS) -Imlx -c $< -o $@

clean :
	@make clean -C ./libft
	@make clean -C ./$(GPATH)
	@rm -f $(OBJS)
	@echo "${YELLOW}> All objects files of cub3d have been deleted ❌${END}"

fclean : clean
	@make fclean -C ./libft
	@make clean -C ./$(GPATH)
	@rm -f $(NAME)
	@echo "${YELLOW}> Cleaning of cub3d has been done ❌${END}"

_mlx:
	@make -C ./$(GPATH)

_libft:
	make -C ./libft

re: fclean all

.PHONY:	all clean fclean re lib