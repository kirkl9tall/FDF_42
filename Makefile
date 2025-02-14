SRCS	=					get_next_line.c ft_split.c get_next_line_utils.c parssing.c utils_pars.c main.c\
							dimensionning.c coloring.c drawing.c drawing2.c  redraw.c projections.c keys_press.c\
							extras.c \

OBJS	=	$(SRCS:.c=.o)

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

MLX_DIR = /usr/include/minilibx-linux/

INCLUDE = -I -L$(MLX_DIR) -linux -lmlx -lXext -lX11 -lm

RM	= rm -f

NAME	= fdf

all:	$(NAME)

$(NAME):	$(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

clean:
	$(RM) $(OBJS)

fclean :	clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re 
