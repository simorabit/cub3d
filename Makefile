.PHONY: all clean fclean re

CC = cc
FLAGS = #-Wall -Wextra -Werror #-g -fsanitize=address -fsanitize=undefined
RM = rm -rf
NAME = cub3D
# B_NAME = Cub3d_bonus

CFILES = parsing.c list_making.c initialization.c main.c events.c utils.c \
	raycasting.c render.c draw_3d.c

OBJ = $(patsubst %.c, %.o, $(CFILES))
B_OBJ = $(patsubst %.c, %.o, $(BFILES))

all: lib $(NAME)

lib:
	@make -C libft

$(OBJ) : %.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : libft/libft.a $(OBJ) Includes/Cub3d.h
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