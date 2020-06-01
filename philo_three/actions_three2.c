/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_three2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:28:38 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/01 18:23:50 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_three.h"

void	*philo(t_ph *b)
{
	pthread_t	eating_thread;
	t_ph		*ph;

	ph = (t_ph*)b;
	gettimeofday(&ph->start, NULL);
	gettimeofday(&ph->end, NULL);
	while (1)
	{
		pthread_create(&eating_thread, NULL, try_eating, (void*)ph);
	//	if (ph->activity == THINKING)
	//	{
			while (1)
			{
				if (thinking(ph))
					break ;
			}
	//	}
	//	if (ph->activity == SLEEPING)
			if (!sleeping(ph))
				return (NULL);
	}
	return (NULL);
}
