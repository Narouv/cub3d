# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 17:59:41 by rnauke            #+#    #+#              #
#    Updated: 2023/10/21 14:14:36 by rnauke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX42 =	./MLX42/Build/libmlx42.a

OBJECTS_DIR = obj
SOURCES_DIR = src

user = "$USER"

SOURCES = main.c ray.c control.c parser.c
OBJECTS = $(SOURCES:.c=.o)

DIR_SRC = $(addprefix $(SOURCES_DIR)/, $(SOURCES))
DIR_OBJ = $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))

FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
# INCLUDES = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
INCLUDES = -Iinclude -lglfw -L\"/opt/homebrew/Cellar/glfw/3.3.8/lib/\"
ARGS = $(LIBFT) $(MLX42) $(INCLUDES) $(FLAGS)
all:  $(NAME)

$(NAME): $(MLX42) $(DIR_OBJ) $(LIBFT)
	cc -o $(NAME) $(DIR_OBJ) $(ARGS) 

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	mkdir -p $(OBJECTS_DIR)
	cc -o $@ -c $< $(FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(MLX42):
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B Build && cmake --build Build -j4

clean:
	rm -rf $(OBJECTS_DIR)
	rm -rf $(BONUS_DIR)/$(OBJECTS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJECTS_DIR)
	rm -rf $(BONUS_DIR)/$(OBJECTS_DIR)
	rm -f $(NAME)
	rm -rf ./MLX42
	$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: re fclean clean

re: clean all
