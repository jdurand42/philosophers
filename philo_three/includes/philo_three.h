/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 02:00:36 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/03 13:02:41 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>

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
	sem_t			*limit_sem;
	sem_t			*forks;
	sem_t			*deads;
	sem_t			*dead_lock;
	sem_t			*output;
	int				id_dead;
	struct timeval	time;
	struct s_ph		*ph;
	pthread_t		limit_thread;
}					t_data;

typedef struct		s_ph
{
	int				activity;
	int				n;
	int				i;
	int				limit;
	int				started_eating;
	int				fork;
	pid_t			pid;
	pthread_t		output;
	struct timeval	start;
	struct timeval	end;
	struct s_data	*data;
}					t_ph;

typedef struct		s_output
{
	int				activity;
	t_ph			*ph;
	int				time_output;
}					t_output;

void				*philo(t_ph *ph);
long				get_time(struct timeval ini, struct timeval now);
void				ft_print(t_ph *ph, int activity);
void				*ft_print_thread(void *output);
int					ft_atoi(char const *str);
void				ft_putstr(char *s);
char				*ft_itoa(int n);
size_t				ft_strlen(char const *str);
int					ft_error(int i);
void				init_sems(t_data *data);
int					ft_init_data(t_data *data, int ac, char **av);
t_ph				*ft_init_ph(t_data *data);
void				*dying(t_ph *ph);
void				*try_eating(void *ph2);
void				eating(t_ph *ph);
int					sleeping(t_ph *ph);
void				*check_limit(void *data2);
void				prepare_sems(t_data *data);
void				safe_exit(t_data *data);
void				forking(t_data *data);
int					thinking(t_ph *ph);

#endif
