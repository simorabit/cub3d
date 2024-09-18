.PHONY: all clean fclean re

CC = cc
FLAGS = #-Wall -Wextra -Werror -o3 #-g -fsanitize=address,undefined,float-divide-by-zero
RM = rm -rf
NAME = cub3D

CFILES = main.c\
		 src/parsing.c\
		 src/list_making.c\
		 src/initialization.c\
		 src/events.c\
		 src/utils.c \
		 src/raycasting.c\
		 src/render.c\
		 src/draw_3d.c\
		 src/ray_cast_utils.c\
		 src/draw_3d_utils.c\
		 src/parse_colors.c\
		 src/parse_map.c\
		 src/parse_map1.c\
		 src/parse_map2.c\
		 src/parse_player.c\
		 src/parse_textures.c\
		 src/parsing_utils.c\
		 src/animation.c\
		 src/animation_utils.c\
		 src/init_sprint.c\

OBJ = $(patsubst %.c, %.o, $(CFILES))
B_OBJ = $(patsubst %.c, %.o, $(BFILES))

all: lib $(NAME)

lib:
	@make -C libft

$(OBJ) : %.o: %.c includes/Cub3d.h
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : libft/libft.a $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) ./MLX42/build/libmlx42.a -lglfw -L/Users/$(USER)/.brew/opt/glfw/lib -pthread -lm libft/libft.a -o $(NAME)
	@echo making ... Done.


clean:
	@$(RM) $(OBJ) $(B_OBJ)
	@make -C libft clean
	@echo cleaning ... Done.

fclean: clean
	$(RM) $(NAME) $(B_NAME)
	make -C libft fclean

re: fclean all
