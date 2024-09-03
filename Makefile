.PHONY: all clean fclean re

CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined
RM = rm -rf
NAME = cub3D
# B_NAME = Cub3d_bonus

CFILES = main.c\
		 src/parsing.c\
		 src/list_making.c\
		 src/initialization.c\
		 src/events.c\
		 src/utils.c \
		 src/raycasting.c\
		 src/render.c\
		 src/draw_3d.c\
		 src/texture.c\
		 src/ray_cast_utils.c\
		 src/draw_3d_utils.c

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