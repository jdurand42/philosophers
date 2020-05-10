#include "../includes/philo_three.h"

void	*dying(t_ph *ph)
{

	ph->activity = DEAD;
	ft_print(ph);
	sem_post(ph->data->deads);
	exit (0);
}

void	*try_eating(void *ph2)
{
//	t_ph *ph = (t_ph*)ph2;

	sem_wait(((t_ph*)(ph2))->data->forks);
	sem_wait(((t_ph*)(ph2))->data->forks);
	((t_ph*)(ph2))->fork = 1;
	ft_print((t_ph*)ph2);
	ft_print((t_ph*)ph2);
	((t_ph*)(ph2))->started_eating = 1;
	//ft_print(ph);
	return (0);
}

void eating(t_ph *ph)
{
	long time;

	ph->activity = EATING;
	ft_print(ph);
	gettimeofday(&ph->start, NULL);
	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		while ((time = get_time(ph->start, ph->end)) < ph->data->time_to_die)
			continue ;
		sem_wait(ph->data->dead_lock); // pas de release des forks ici
		dying(ph);
		return ;
	}
	//gettimeofday(&ph->start, NULL);
	while (get_time(ph->start, ph->end) < ph->data->time_to_eat)
		gettimeofday(&ph->end, NULL);
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
	ph->limit += 1;
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		sem_post(ph->data->limit_sem);
	ph->fork = 0;
	ph->started_eating = 0;
	ph->activity = SLEEPING;
	ft_print(ph);
}

int sleeping(t_ph *ph)
{
	long time;
//	while (ph->i <= ph->data->time_to_sleep + ph->data->time_to_eat && ph->activity != DEAD)
//	{
/*	if (ph->data->over == 1)
		return (0);*/
	gettimeofday(&ph->end, NULL);
	while ((time = get_time(ph->start, ph->end)) < ph->data->time_to_sleep)
	{
		if (time > ph->data->time_to_die)
		{
			sem_wait(ph->data->dead_lock);
			dying(ph);
			return (0);
		}
	}
	ph->activity = THINKING;
	ft_print(ph);
	return (1);
}

void	*philo(t_ph *b)
{
	pthread_t eating_thread;
	//pthread_t waiting_thread;
	t_ph	*ph;

	ph = (t_ph*)b;
//	if (ph->n == 0)
//		gettimeofday(&ph->data->time, NULL);
	//printf("%d\n", ph->n);
	gettimeofday(&ph->start, NULL);
	//gettimeofday(&ph->end, NULL);
	while (1)
	{
		pthread_create(&eating_thread, NULL, try_eating, (void*)ph);
		if (ph->activity == THINKING)
		{
	//		pthread_create(&waiting_thread, NULL, try_wait, (void*)ph);
			while (1)
			{
				gettimeofday(&ph->end, NULL);
/*				if (ph->data->over == 1)
					return (NULL);*/
				if (ph->started_eating == 1)
				{
					eating(ph);
					break ;
				}
				else if (ph->started_eating == 0 && get_time(ph->start, ph->end) >= ph->data->time_to_die)
				{
					sem_wait(ph->data->dead_lock);
					dying(ph);
					return (NULL);
				}
			}
		}
		if (ph->activity == SLEEPING)
			if (!sleeping(ph))
				return (NULL);
	}
	return (NULL);
}
