/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_three2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:28:38 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/03 13:00:55 by jeromedurand     ###   ########.fr       */
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
		while (1)
		{
			if (thinking(ph))
				break ;
		}
		if (!sleeping(ph))
			return (NULL);
	}
	return (NULL);
}
