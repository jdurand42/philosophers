/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:12:56 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/03 12:53:41 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_one.h"

void	*dying(t_ph *ph)
{
	ft_print(ph, DEAD);
	ph->data->over = 1;
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
	((t_ph*)(ph2))->started_eating = 1;
	ft_print((t_ph*)ph2, FORK);
	ft_print((t_ph*)ph2, FORK);
	ft_print((t_ph*)ph2, EATING);
	return (0);
}

void	eating(t_ph *ph)
{
	gettimeofday(&ph->start, NULL);
	while (get_time(ph->start, ph->end) < ph->data->time_to_eat)
		gettimeofday(&ph->end, NULL);
	pthread_mutex_unlock(&ph->data->ph[ph->fork_priority_1].forks);
	pthread_mutex_unlock(&ph->data->ph[ph->fork_priority_2].forks);
	ft_print(ph, SLEEPING);
	ph->limit += 1;
}

int		sleeping(t_ph *ph)
{
	gettimeofday(&ph->start_sleep, NULL);
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		pthread_mutex_unlock(&ph->limit_check);
	while (!gettimeofday(&ph->end, NULL) &&
	get_time(ph->start_sleep, ph->end) < ph->data->time_to_sleep)
	{
		ph->started_eating = 0;
		if (get_time(ph->start, ph->end) > ph->data->time_to_die)
		{
			pthread_mutex_lock(&ph->data->dead_lock);
			dying(ph);
			return (0);
		}
	}
	ft_print(ph, THINKING);
	return (1);
}
