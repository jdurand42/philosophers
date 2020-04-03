
NAME		=	philo_one

SRCS_ONE	=	srcs/philo_one.c srcs/actions_one.c

SRCS_TWO	=	srcs/philo_two.c srcs/actions_two.c

SRCS_THREE	=	srcs/philo_three.c srcs/actions_three.c srcs/shared_utils.c

CC		=	gcc

SANI	=	-fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

all	:	$(NAME)
		gcc -o $(NAME) $(SRCS_ONE)

c1	:
		gcc -o philo_one $(SRCS_ONE)

c2	:
		gcc -o philo_two $(SRCS_TWO)

c3	:
		gcc -o philo_three $(SRCS_THREE)


s1	:
		gcc -o philo_one $(SANI) $(SRCS_ONE)

s2	:
		gcc -o philo_two $(SANI) $(SRCS_TWO)

s3	:
		gcc -o philo_three $(SANI) $(SRCS_THREE)


w1	:
		gcc -o philo_one $(FLAGS) $(SRCS_ONE)

w2	:
		gcc -o philo_two $(FLAGS) $(SRCS_TWO)

w3	:
		gcc -o philo_three $(FLAGS) $(SRCS_THREE)

clean	:
		echo "cleaning"

fclean	:	clean
		rm -rf philo_one philo_two philo_three

re	:	fclean all
