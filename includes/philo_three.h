/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 02:00:36 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/11 12:13:44 by jeromedurand     ###   ########.fr       */
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

# define THINKING 1
# define EATING 2
# define SLEEPING 4
# define DEAD 8
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
	struct timeval	start;
	struct timeval	end;
	struct s_data	*data;
}					t_ph;

void				*philo(t_ph *ph);
long				get_time(struct timeval ini, struct timeval now);
void				ft_print(t_ph *ph);
int					ft_atoi(char const *str);
void				ft_putstr(char *s);
char				*ft_itoa(int n);
size_t				ft_strlen(char const *str);
int					ft_error(int i);
void				init_sems(t_data *data);
int					ft_init_data(t_data *data, int ac, char **av);
t_ph				*ft_init_ph(t_data *data);

#endif
