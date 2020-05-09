#include "../../includes/philo_three.h"

void	*dying(t_ph *ph)
{
	sem_wait(ph->data->dead_lock);
	ph->activity = DEAD;
	ft_print(ph);
	sem_post(ph->data->deads);
	exit (0);
}

void	waiting(t_ph *ph)
{
	usleep(TIME);
	ph->i += 1;
}

void	*try_eating(void *ph2)
{
	t_ph *ph = (t_ph*)ph2;
	sem_wait(ph->data->forks);
	ph->fork = 1;
	ft_print(ph);
	sem_wait(ph->data->forks);
	ph->started_eating = 1;
	ft_print(ph);
	return (0);
}

void eating(t_ph *ph)
{
	ph->i = 0;
	ph->activity = EATING;
	ft_print(ph);
	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		usleep(ph->data->time_to_die * TIME);
		dying(ph);
	}
	usleep(ph->data->time_to_eat * TIME);
	ph->limit += 1;
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		sem_post(ph->data->limit_sem);
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
	ph->fork = 0;
	ph->started_eating = 0;
	ph->activity = SLEEPING;
	ph->i += ph->data->time_to_eat;
	ft_print(ph);
}

void sleeping(t_ph *ph)
{
	while (ph->i <= ph->data->time_to_sleep + ph->data->time_to_eat && ph->activity != DEAD)
	{
		waiting(ph);
		if (ph->i >= ph->data->time_to_die)
			dying(ph);
	}
	ph->activity = THINKING;
		ft_print(ph);
}

void	*philo(t_ph *ph)
{
	pthread_t eating_thread;

	while (1)
	{
		if (ph->activity == THINKING)
		{
			pthread_create(&eating_thread, NULL, try_eating, (void*)ph);
			while (1)
			{
				if (ph->started_eating == 1)
				{
					eating(ph);
					break ;
				}
				else
				{
					waiting(ph);
					if (ph->i >= ph->data->time_to_die)
						dying(ph);
				}
			}
		}
		if (ph->activity == SLEEPING)
			sleeping(ph);
	}
	return (0);
}
