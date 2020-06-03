/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_two2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:38:17 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/03 12:56:47 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_two.h"

void	*safe_return(t_ph *ph)
{
	if (ph->limit < ph->data->limit)
		sem_post(ph->data->limit_sem);
	return (NULL);
}

void	*philo(void *b)
{
	t_ph		*ph;

	ph = (t_ph*)b;
	gettimeofday(&ph->start, NULL);
	while (ph->data->over == 0)
	{
		pthread_create(&ph->eating_thread, NULL, try_eating, (void*)ph);
		while (!ph->started_eating && !gettimeofday(&ph->end, NULL))
		{
			pthread_detach(ph->eating_thread);
			if (get_time(ph->start, ph->end) >= ph->data->time_to_die &&
			ph->started_eating == 0)
			{
				sem_wait(ph->data->dead_lock);
				dying(ph);
				return (safe_return(ph));
			}
		}
		eating(ph);
		if (!sleeping(ph))
			return (safe_return(ph));
	}
	return (safe_return(ph));
}
