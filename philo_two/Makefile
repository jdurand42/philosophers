
NAME		=	philo_two

SRCS	=	./actions_two.c ./utils.c ./philo_two.c ./init.c \
				./commons.c ./commons2.c ./actions_two2.c

CC		=	clang

SANI	=	-fsanitize=address -g3

CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

RM		= rm -rf

LIB		=	-lpthread

all	:	$(NAME)

$(NAME): $(OBJS)
		$(CC) $(LIB) -o $(NAME) $(CFLAGS) $(OBJS)

c1	:
		clean
		$(CC) -o $(NAME) $(OBJS) $(SRCS)

s1	:
		clean
		$(CC) -o $(NAME) $(SANI) $(SRCS)

w1	:
		clean
		$(CC) -o $(NAME) $(CFLAGS) $(SRCS)

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	clean fclean all c1 s1 w1
