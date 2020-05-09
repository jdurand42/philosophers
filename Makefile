
NAME		=	philo_one

NAME1		=	philo_one/philo_one

NAME2		=	philo_two/philo_two

NAME3		=	philo_three/philo_three

SRCS_ONE	=	philo_one/philo_one.c philo_one/actions_one.c philo_one/utils.c philo_one/commons.c

SRCS_TWO	=	philo_two/philo_two.c philo_two/actions_two.c philo_two/utils.c philo_two/commons.c

SRCS_THREE	=	philo_three/philo_three.c philo_three/actions_three.c philo_three/utils.c philo_three/commons.c

UTILS		=

CC		=	clang

SANI	=	-fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

all	:
		make w1
		make w2
		make w3

c1	:
		$(CC) -o $(NAME1) $(SRCS_ONE) $(UTILS)

c2	:
		$(CC) -o $(NAME2) $(SRCS_TWO) $(UTILS)

c3	:
		$(CC) -o $(NAME3) $(SRCS_THREE) $(UTILS)


s1	:
		$(CC) -o $(NAME1) $(SANI) $(SRCS_ONE) $(UTILS)

s2	:
		$(CC) -o $(NAME2) $(SANI) $(SRCS_TWO) $(UTILS)

s3	:
		$(CC) -o $(NAME3) $(SANI) $(SRCS_THREE) $(UTILS)


w1	:
		$(CC) -o $(NAME1) $(FLAGS) $(SRCS_ONE) $(UTILS)

w2	:
		$(CC) -o $(NAME2) $(FLAGS) $(SRCS_TWO) $(UTILS)

w3	:
		$(CC) -o $(NAME3) $(FLAGS) $(SRCS_THREE) $(UTILS)

clean	:


fclean	:	clean
		rm -rf $(NAME1) $(NAME2) $(NAME3)

re	:	fclean all
