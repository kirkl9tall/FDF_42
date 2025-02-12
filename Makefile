SRCS	=					 get_next_line.c ft_split.c get_next_line_utils.c parssing.c utils_pars.c main.c \
								dimensionning.c coloring.c drawing.c drawing2.c  redraw.c projections.c \

OBJS	=	$(SRCS:.c=.o)

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

NAME	= fdf.a

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean :	clean
	$(RM) $(NAME)

re : fclean $(NAME)

.PHONY:	all clean fclean re 
