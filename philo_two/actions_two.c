/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:35:30 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/02 17:08:04 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_two.h"

void	*dying(t_ph *ph)
{
	gettimeofday(&ph->end, NULL);
	ft_print(ph, DEAD);
	ph->data->over = 1;
	sem_post(ph->data->deads);
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
	return (0);
}

void	eating(t_ph *ph)
{
	ft_print(ph, EATING);
	gettimeofday(&ph->start, NULL);
	/*if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		while ((get_time(ph->start, ph->end)) < ph->data->time_to_die)
			gettimeofday(&ph->end, NULL);
		sem_wait(ph->data->dead_lock);
		sem_post(ph->data->forks);
		sem_post(ph->data->forks);
		dying(ph);
		return ;
	}*/
	while (get_time(ph->start, ph->end) < ph->data->time_to_eat)
		gettimeofday(&ph->end, NULL);
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
	ft_print(ph, SLEEPING);
	ph->limit += 1;
}

int		sleeping(t_ph *ph)
{
	//struct timeval	start_sleep;

	//gettimeofday(&ph->end, NULL);
	gettimeofday(&ph->start_sleep, NULL);
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		sem_post(ph->data->limit_sem);
	while (!gettimeofday(&ph->end, NULL) && get_time(ph->start_sleep, ph->end) < ph->data->time_to_sleep)
	{
		ph->started_eating = 0;
		if (get_time(ph->start, ph->end) > ph->data->time_to_die)
		{
			sem_wait(ph->data->dead_lock);
			dying(ph);
			return (0);
		}
		//gettimeofday(&ph->end, NULL);
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
