/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 02:00:33 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/02 16:35:44 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <signal.h>

# define THINKING 1
# define EATING 2
# define SLEEPING 4
# define DEAD 8
# define FORK 16
# define TIME 1000

typedef	struct		s_data
{
	int				n_p;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				limit;
	int				limit_check;
	int				over;
	pthread_mutex_t	forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	output;
	struct timeval	time;
	struct s_ph		*ph;
}					t_data;

typedef struct		s_ph
{
//	int				activity;
	int				n;
	int				i;
	int				limit;
	int				started_eating;
	int				has_a_fork;
	int				fork_priority_1;
	int				fork_priority_2;
	int				time_output;
	int				activity_output;
	int				has_a_fork_output;
	pthread_mutex_t	forks;
	pthread_mutex_t	limit_check;
	pthread_t		thread;
	pthread_t		output;
	pthread_t		eating_thread;
	struct s_data	*data;
	struct timeval	start;
	struct timeval	end;
	struct timeval	start_sleep;
}					t_ph;

typedef struct s_output
{
	int	activity;
	int	n;
	int	over;
	int	time_output;
	pthread_mutex_t *output;
}				t_output;

void				*philo(void *ph);
long				get_time(struct timeval ini, struct timeval now);
void				ft_print(t_ph *ph, int activity);
int					ft_atoi(char const *str);
void				ft_putstr(char *s);
char				*ft_itoa(int n);
size_t				ft_strlen(char const *str);
int					fork_priority_1(int n, int n_max);
int					fork_priority_2(int n, int n_max);
int					ft_error(int i);
int					init_mutex(t_data *data);
int					ft_init_data(t_data *data, int ac, char **av);
t_ph				*ft_init_ph(t_data *data);
void				*safe_return(t_ph *ph);
void				*dying(t_ph *ph);
void				*try_eating(void *ph2);
void				eating(t_ph *ph);
int					sleeping(t_ph *ph);
int					thinking(t_ph *ph);
int					safe_exit(t_data *data);
int					threading(t_data *data);
void				*check_limit(t_data *data);

void 				*ft_print_thread(void *ph);

#endif
