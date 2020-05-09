
NAME		=	philo_one

SRCS_ONE	=	./actions_one.c ./utils.c ./philo_one.c

UTILS		=	./commons.c

CC		=	clang

SANI	=	-fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

all	:	$(NAME)

$(NAME):
		make w1

c1	:
		$(CC) -o $(NAME) $(SRCS_ONE) $(UTILS)

s1	:
		$(CC) -o $(NAME) $(SANI) $(SRCS_ONE) $(UTILS)

w1	:
		$(CC) -o $(NAME) $(FLAGS) $(SRCS_ONE) $(UTILS)

clean	:
		echo "cleaning"

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all
