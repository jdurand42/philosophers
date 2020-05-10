#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>

#include <signal.h>

# define THINKING 1
# define EATING 2
# define SLEEPING 4
# define DEAD 8
# define TIME 1000

typedef	struct s_data
{
	int n_p;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int limit;
	int limit_check;
	int over;
	pthread_mutex_t	forks;
	//pthread_mutex_t	*deads;
	pthread_mutex_t	dead_lock;
	//pthread_mutex_t limit_lock;
	pthread_mutex_t	output;
	struct timeval time;
	struct s_ph	*ph;
//	pthread_t limit_thread;
}		t_data;


typedef struct s_ph
{
	int		activity;
	int		n;
	int		i;
	int		limit;
	int 	started_eating;
	int		has_a_fork;
	int		fork_priority_1;
	int		fork_priority_2;
	pthread_mutex_t forks;
	pthread_mutex_t limit_check;
	pthread_t thread;
	struct s_data *data;
	struct timeval start;
	struct timeval end;
}		t_ph;

void	*philo(void *ph);
long	get_time(struct timeval ini, struct timeval now);
void 	ft_print(t_ph *ph);
int		ft_atoi(char const *str);
void	ft_putstr(char *s);
char	*ft_itoa(int n);
size_t	ft_strlen(char const *str);
int 	fork_priority_1(int n, int n_max);
int		fork_priority_2(int n, int n_max);
int		ft_error(int i);
int		init_mutex(t_data *data);
int		ft_init_data(t_data *data, int ac, char **av);
t_ph	*ft_init_ph(t_data *data);

#endif
