SRCS                    =       ft_split.c  ft_atoi.c   main.c ft_strdup.c  get_next_line.c \
								 get_next_line_utils.c  draw_utils.c  draw_utils2.c magic.c parssing.c Mydrawline.c\

OBJS                    = 		$(SRCS:.c=.o)

CC                              = cc

CFLAGS                  = -Wall -Wextra -Werror

RM                              = rm -f

NAME                    = fdf.a

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) 

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re 
                                          