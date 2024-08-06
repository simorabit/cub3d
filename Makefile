CC = cc

SRCS       = initialization.c main.c events.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
				utils.c raycasting.c render.c draw_3d.c
# //-fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror -O3 

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit 

OBJS = $(SRCS:.c=.o)


TARGET = cub3d


all : $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $@ $^

%.o: %.c  cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(TARGET)

re : fclean all
