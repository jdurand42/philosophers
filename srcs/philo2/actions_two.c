#include "../../includes/philo_two.h"

void	dying(t_ph *ph)
{
	sem_wait(ph->data->dead_lock);
	ph->activity = DEAD;
	ft_print(ph);
	ph->data->over = 1;
	sem_post(ph->data->deads);
	sem_post(ph->data->dead_lock);
}

int	waiting(t_ph *ph)
{
	if (ph->data->over == 1)
		return (0);
	usleep(TIME);
	ph->i += 1;
	return (1);
}

void	*try_eating(void *ph2)
{
	t_ph *ph = (t_ph*)ph2;
	sem_wait(ph->data->forks);

	sem_wait(ph->data->forks);
	ph->fork = 1;
	ft_print(ph);
	ph->started_eating = 1;
	ft_print(ph);
	return (0);
}

int eating(t_ph *ph)
{
	ph->i = 0;
	ph->activity = EATING;
	ft_print(ph);
	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		usleep(ph->data->time_to_die * TIME);
		sem_post(ph->data->forks);
		sem_post(ph->data->forks);
		dying(ph);
		return (0);
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
	return (1);
}

int sleeping(t_ph *ph)
{
	while (ph->i <= ph->data->time_to_sleep + ph->data->time_to_eat && ph->activity != DEAD)
	{
		if (!waiting(ph))
			return (0);
		if (ph->i >= ph->data->time_to_die)
		{
			dying(ph);
			return (0);
		}
	}
	ph->activity = THINKING;
	ft_print(ph);
	return (1);
}

void	*philo(void *b)
{
	pthread_t eating_thread;
	t_ph	*ph;

	ph = (t_ph*)b;
	while (ph->data->over == 0)
	{
		if (ph->activity == THINKING)
		{
			pthread_create(&eating_thread, NULL, try_eating, (void*)ph);
			while (1)
			{
				if (ph->started_eating == 1)
				{
					if (!eating(ph))
						return (NULL);
					break ;
				}
				else
				{
					if (!(waiting(ph)))
						return (NULL);
					if (ph->i >= ph->data->time_to_die)
					{
						dying(ph);
						return (NULL);
					}
				}
			}
		}
		if (ph->activity == SLEEPING)
			if (!sleeping(ph))
				return (NULL);
	}
	return (NULL);
}
