/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:35:30 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/02 20:48:26 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_two.h"

void	*dying(t_ph *ph)
{
//	ph->activity = DEAD;
	ft_print(ph, DEAD);
	ph->data->over = 1;

//	if (ph->activity == DEAD)
//		pthread_join(ph->output, NULL);
	if (ph->limit < ph->data->limit)
		sem_post(ph->data->limit_sem);
	sem_post(ph->data->dead_lock);
	return (0);
}

void	*try_eating(void *ph2)
{
	sem_wait(((t_ph*)(ph2))->data->forks);
	sem_wait(((t_ph*)(ph2))->data->forks);
	((t_ph*)(ph2))->started_eating = 1;
	ft_print((t_ph*)ph2, FORK);
	ft_print((t_ph*)ph2, FORK);
	ft_print((t_ph*)ph2, EATING);
	return (0);
}

void	eating(t_ph *ph)
{
	gettimeofday(&ph->start, NULL);
	gettimeofday(&ph->end, NULL);
	while (get_time(ph->start, ph->end) < ph->data->time_to_eat)
		gettimeofday(&ph->end, NULL);
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
	ft_print(ph, SLEEPING);
	ph->limit += 1;
}
/*
int		sleeping(t_ph *ph)
{
	struct timeval	start_sleep;

	gettimeofday(&ph->end, NULL);
	gettimeofday(&start_sleep, NULL);
	ph->limit += 1;
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		sem_post(&ph->limit_check);
	while ((get_time(start_sleep, ph->end)) < ph->data->time_to_sleep)
	{
		if (get_time(ph->start, ph->end) > ph->data->time_to_die)
		{
			sem_wait(&ph->data->dead_lock);
			dying(ph);
			return (0);
		}
		gettimeofday(&ph->end, NULL);
	}
	//ph->activity = THINKING;
	ft_print(ph, THINKING);
	return (1);
}

int		thinking(t_ph *ph)
{
	while (1)
	{
		gettimeofday(&ph->end, NULL);
		if (ph->started_eating == 1)
		{
			//pthread_join(ph->eating_thread, NULL);
			eating(ph);
			return (1);
		}
		else if (ph->started_eating == 0 &&
		get_time(ph->start, ph->end) >= ph->data->time_to_die)
		{
			sem_wait(&ph->data->dead_lock);
			dying(ph);
			return (0);
		}
	}
	return (0);
}
*/int		sleeping(t_ph *ph)
{
	//struct timeval	start_sleep;

	//gettimeofday(&ph->end, NULL);
	gettimeofday(&ph->start_sleep, NULL);
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		sem_post(ph->data->limit_sem);
	while (!gettimeofday(&ph->end, NULL) &&
	get_time(ph->start_sleep, ph->end) < ph->data->time_to_sleep)
	{
		ph->started_eating = 0;
		if (get_time(ph->start, ph->end) > ph->data->time_to_die)
		{
			sem_wait(ph->data->dead_lock);
			dying(ph);
			return (0);
		}
	}
	ft_print(ph, THINKING);
	return (1);
}
// /*
// int		thinking(t_ph *ph)
// {
// 	/*
// 	gettimeofday(&ph->end, NULL);
// 	if (ph->started_eating == 1)
// 	{
// 		eating(ph);
// 		return (1);
// 	}
// 	else if (ph->started_eating == 0 &&
// 	get_time(ph->start, ph->end) >= ph->data->time_to_die)
// 	{
// 		sem_wait(ph->data->dead_lock);
// 		dying(ph);
// 		return (0);
// 	}*/
// 	while (!ph->started_eating && !gettimeofday(&ph->end, NULL))
// 	{
// 					//printf("lol\n");
// 		if (get_time(ph->start, ph->end) > ph->data->time_to_die)
// 		{
// 			//printf("lol\n");
// 			sem_wait(ph->data->dead_lock);
// 			dying(ph);
// 			return (0);
// 		}
// 	}
// 	eating(ph);
// 	return (1);
// }
