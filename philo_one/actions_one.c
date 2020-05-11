/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:12:56 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/11 16:42:13 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_one.h"

void	*dying(t_ph *ph)
{
	ph->activity = DEAD;
	ft_print(ph);
	ph->data->over = 1;

//	if (ph->activity == DEAD)
//		pthread_join(ph->output, NULL);
	if (ph->limit < ph->data->limit)
		pthread_mutex_unlock(&ph->limit_check);
	pthread_mutex_unlock(&ph->data->dead_lock);
	return (0);
}

void	*try_eating(void *ph2)
{
	pthread_mutex_lock(
	&((t_ph*)(ph2))->data->ph[((t_ph*)(ph2))->fork_priority_1].forks);
	pthread_mutex_lock(
	&((t_ph*)(ph2))->data->ph[((t_ph*)(ph2))->fork_priority_2].forks);
	((t_ph*)(ph2))->has_a_fork = 1;
	ft_print((t_ph*)ph2);
	ft_print((t_ph*)ph2);
	((t_ph*)(ph2))->started_eating = 1;
	return (0);
}

void	eating(t_ph *ph)
{
	ph->activity = EATING;
	ft_print(ph);
	gettimeofday(&ph->start, NULL);
	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		while ((get_time(ph->start, ph->end)) < ph->data->time_to_die)
			gettimeofday(&ph->end, NULL);
		pthread_mutex_lock(&ph->data->dead_lock);
		pthread_mutex_unlock(&ph->data->ph[ph->fork_priority_1].forks);
		pthread_mutex_unlock(&ph->data->ph[ph->fork_priority_2].forks);
		pthread_mutex_unlock(&ph->limit_check);
		dying(ph);
		return ;
	}
	while (get_time(ph->start, ph->end) < ph->data->time_to_eat)
		gettimeofday(&ph->end, NULL);
	pthread_mutex_unlock(&ph->data->ph[ph->fork_priority_1].forks);
	pthread_mutex_unlock(&ph->data->ph[ph->fork_priority_2].forks);
	ph->has_a_fork = 0;
	ph->activity = SLEEPING;
	ft_print(ph);
	ph->started_eating = 0;
}

int		sleeping(t_ph *ph)
{
	struct timeval	start_sleep;

	gettimeofday(&ph->end, NULL);
	gettimeofday(&start_sleep, NULL);
	ph->limit += 1;
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		pthread_mutex_unlock(&ph->limit_check);
	while ((get_time(start_sleep, ph->end)) < ph->data->time_to_sleep)
	{
		if (get_time(ph->start, ph->end) > ph->data->time_to_die)
		{
			pthread_mutex_lock(&ph->data->dead_lock);
			dying(ph);
			return (0);
		}
		gettimeofday(&ph->end, NULL);
	}
	ph->activity = THINKING;
	ft_print(ph);
	return (1);
}

int		thinking(t_ph *ph)
{
	if (ph->started_eating == 1)
	{
		eating(ph);
		return (1);
	}
	else if (ph->started_eating == 0 &&
	get_time(ph->start, ph->end) >= ph->data->time_to_die)
	{
		pthread_mutex_lock(&ph->data->dead_lock);
		dying(ph);
		return (0);
	}
	return (0);
}
