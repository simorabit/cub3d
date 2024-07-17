CC = cc

SRCS       = initialization.c main.c events.c

CFLAGS = -Wall -Wextra -Werror -O3

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit 

OBJS = $(SRCS:.c=.o)


TARGET = cub3d


all : $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $@ $^

%.o: %.c  cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@