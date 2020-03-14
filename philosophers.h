#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

# define THINKING 1
# define EATING 2
# define SLEEPING 4
# define DEAD 8
# define TIME 1

typedef	struct s_data
{
	int n_p;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int limit;
}		t_data;


typedef struct s_ph
{
	int		activity;
	int		n;
	int		i;
	pthread_t 	thread;
	pthread_mutex_t fork = PTHREAD_MUTEX_INITIALIZER;
	struct s_ph *prev;
	struct s_ph *next;
	struct s_data *data;
}

#endif


