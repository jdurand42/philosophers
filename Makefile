
NAME		=	philo_one

SRCS_ONE	=	srcs/philo1/philo_one.c srcs/philo1/actions_one.c srcs/philo1/utils.c

SRCS_TWO	=	srcs/philo2/philo_two.c srcs/philo2/actions_two.c srcs/philo2/utils.c

SRCS_THREE	=	srcs/philo3/philo_three.c srcs/philo3/actions_three.c srcs/philo3/utils.c

UTILS		=	srcs/shared/commons.c

CC		=	gcc

SANI	=	-fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

all	:	$(NAME)
		gcc -o $(NAME) $(SRCS_ONE) $(UTILS)

c1	:
		gcc -o philo_one $(SRCS_ONE) $(UTILS)

c2	:
		gcc -o philo_two $(SRCS_TWO) $(UTILS)

c3	:
		gcc -o philo_three $(SRCS_THREE) $(UTILS)


s1	:
		gcc -o philo_one $(SANI) $(SRCS_ONE) $(UTILS)

s2	:
		gcc -o philo_two $(SANI) $(SRCS_TWO) $(UTILS)

s3	:
		gcc -o philo_three $(SANI) $(SRCS_THREE) $(UTILS)


w1	:
		gcc -o philo_one $(FLAGS) $(SRCS_ONE) $(UTILS)

w2	:
		gcc -o philo_two $(FLAGS) $(SRCS_TWO) $(UTILS)

w3	:
		gcc -o philo_three $(FLAGS) $(SRCS_THREE) $(UTILS)

clean	:
		echo "cleaning"

fclean	:	clean
		rm -rf philo_one philo_two philo_three

re	:	fclean all
