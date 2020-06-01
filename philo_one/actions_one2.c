/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_one2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:09:18 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/01 16:58:20 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_one.h"

void	*safe_return(t_ph *ph)
{
	if (ph->limit < ph->data->limit)
		pthread_mutex_unlock(&ph->limit_check);
	return (NULL);
}

void	*philo(void *b)
{
	t_ph		*ph;

	ph = (t_ph*)b;
	gettimeofday(&ph->start, NULL);
	gettimeofday(&ph->end, NULL);
	while (ph->data->over == 0)
	{
		pthread_create(&ph->eating_thread, NULL, try_eating, (void*)ph);
		while (1)
		{
			if (thinking(ph))
				break ;
			if (ph->data->over == 1)
				return (safe_return(ph));
		}
		if (!sleeping(ph))
			return (safe_return(ph));
	}
	return (safe_return(ph));
}
