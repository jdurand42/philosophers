
NAME		=	philo_three

SRCS_ONE	=	./actions_three.c ./utils.c ./philo_three.c ./init.c

UTILS		=	./commons.c ./commons2.C

CC		=	clang

SANI	=	-fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

all	:	$(NAME)

$(NAME):
		$(CC) -o $(NAME) $(FLAGS) $(SRCS_ONE) $(UTILS)

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
