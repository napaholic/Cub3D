NAME = Cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = -L ./mlx -lmlx -framework OpenGL -framework AppKit -fsanitize=address

SRCS =	$(addprefix src/, Cub3D.c \
					get_next_line.c \
					get_next_line_utils.c \
					map_parse.c \
					map_parse2.c \
					map_parse3.c \
					movement.c \
					movement2.c \
					init.c \
					init2.c \
					loop_hook.c \
					calculate_wall.c \
					wall_cast.c \
					save_map.c \
					hook_func.c \
					get_direction.c \
					utils.c \
					utils2.c)
					# load_texture.c \
					# draw_floor.c \
					# calculate_floor.c \
					# engine_run.c \
					# texture_set.c \
					# draw_floor.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	make clean

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MFLAGS)

bonus:
	make all -C $(BONUS)

clean: 
	rm -f $(OBJS)
	# make fclean -C $(BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re