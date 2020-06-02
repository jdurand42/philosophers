/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_two2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:38:17 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/02 16:26:03 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_two.h"

void	*philo(void *b)
{
	pthread_t	eating_thread;
	t_ph		*ph;

	ph = (t_ph*)b;
	gettimeofday(&ph->start, NULL);
	gettimeofday(&ph->end, NULL);
	while (ph->data->over == 0)
	{
		pthread_create(&eating_thread, NULL, try_eating, (void*)ph);
//		while (1)
//		{
		//	if (!thinking(ph) || ph->data->over == 1)
		//		return (NULL);
			/*if (ph->data->over == 1)
				return (NULL);*/
//		}
		while (!ph->started_eating && !gettimeofday(&ph->end, NULL))
		{
				//printf("lol\n");
			if (get_time(ph->start, ph->end) > ph->data->time_to_die)
			{
		//printf("lol\n");
				sem_wait(ph->data->dead_lock);
				dying(ph);
				return (NULL);
			}
		}
		eating(ph);
		if (!sleeping(ph))
			return (NULL);
	}
	return (NULL);
}
