SRCS	=	get_next_line.c ft_split.c get_next_line_utils.c parssing.c utils_pars.c init1.c main.c \
			dimensionning.c coloring.c drawing.c drawing2.c redraw.c projections.c keys_press.c \
			extras.c 

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I. -I/root/fdf/kouchi/fdf/minilibx-linux
LDFLAGS	=	-L/root/fdf/kouchi/fdf/minilibx-linux -L/root/fdf/kouchi/fdf/minilibx-linux
LDLIBS	=	-lmlx -lXext -lX11 -lm
RM		=	rm -f
NAME	=	fdf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re