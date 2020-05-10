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
	sem_wait(((t_ph*)(ph2))->data->forks);
	sem_wait(((t_ph*)(ph2))->data->forks);
	((t_ph*)(ph2))->fork = 1;
	ft_print((t_ph*)ph2);
	ft_print((t_ph*)ph2);
	((t_ph*)(ph2))->started_eating = 1;
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
			gettimeofday(&ph->end, NULL) ;
		sem_wait(ph->data->dead_lock);
		sem_post(ph->data->forks);
		sem_post(ph->data->forks);
		dying(ph);
		return ;
	}
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
	struct timeval start_sleep;

	gettimeofday(&ph->end, NULL);
	gettimeofday(&start_sleep, NULL);
	while ((get_time(start_sleep, ph->end)) < ph->data->time_to_sleep)
	{
		if (get_time(ph->start, ph->end) > ph->data->time_to_die)
		{
			sem_wait(ph->data->dead_lock);
			dying(ph);
			return (0);
		}
		gettimeofday(&ph->end, NULL);
	}
	ph->activity = THINKING;
	ft_print(ph);
	return (1);
}

void	*philo(t_ph *b)
{
	pthread_t eating_thread;
	t_ph	*ph;

	ph = (t_ph*)b;
	gettimeofday(&ph->start, NULL);
	gettimeofday(&ph->end, NULL);
	while (1)
	{
		pthread_create(&eating_thread, NULL, try_eating, (void*)ph);
		if (ph->activity == THINKING)
		{
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
