/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_one2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:09:18 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/11 13:56:04 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_one.h"

void	*safe_return(t_ph *ph)
{
	pthread_mutex_unlock(&ph->limit_check);
	return (NULL);
}

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
		if (ph->activity == THINKING)
		{
			while (1)
			{
				gettimeofday(&ph->end, NULL);
				if (thinking(ph))
					break ;
				if (ph->data->over == 1)
					return (safe_return(ph));
			}
		}
		if (ph->activity == SLEEPING)
			if (!sleeping(ph))
				return (safe_return(ph));
	}
	return (NULL);
}
