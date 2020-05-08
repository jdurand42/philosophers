#include "../../includes/philo_one.h"

void	dying(t_ph *ph)
{
	pthread_mutex_lock(ph->data->dead_lock);
	ph->activity = DEAD;
	ft_print(ph);
	ph->data->over = 1;
}

void	waiting(t_ph *ph)
{
	usleep(TIME);
	ph->i += 1;
}

void	*try_eating(void *ph2)
{
	t_ph *ph = (t_ph*)ph2;

	if (ph->n > 0)
		pthread_mutex_lock(ph->data->ph[ph->n - 1].forks);
	else
		pthread_mutex_lock(ph->data->ph[ph->data->n_p - 1].forks);
	ph->has_a_fork = 1;
	ft_print(ph);
	pthread_mutex_lock(ph->data->ph[ph->n].forks);
	ph->has_a_fork = 1;
	ft_print(ph);
	ph->started_eating = 1;
	//ft_print(ph);
	return (0);
}

void eating(t_ph *ph)
{
	ph->i = 0;
	ph->activity = EATING;
	ft_print(ph);
	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		usleep(ph->data->time_to_die);
		dying(ph);
	}
	usleep(ph->data->time_to_eat * TIME);
	ph->limit += 1;
	pthread_mutex_lock(ph->data->limit_lock);
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		ph->data->limit_check +=1;
	pthread_mutex_unlock(ph->data->limit_lock);
	if (ph->n > 0)
		pthread_mutex_unlock(ph->data->ph[ph->data->n_p - 1].forks);
	else
		pthread_mutex_unlock(ph->data->ph[ph->n - 1].forks);
	pthread_mutex_unlock(ph->data->ph[ph->n].forks);
	ph->has_a_fork= 0;
	ph->started_eating = 0;
	ph->activity = SLEEPING;
	ph->i += ph->data->time_to_eat;
	ft_print(ph);
}

int sleeping(t_ph *ph)
{
	while (ph->i <= ph->data->time_to_sleep + ph->data->time_to_eat && ph->activity != DEAD)
	{
		waiting(ph);
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
	while (1 && ph->data->over == 0)
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
					{
						dying(ph);
						return (0);
					}
				}
			}
		}
		if (ph->activity == SLEEPING)
			if (!sleeping(ph))
				return (0);
	}
	return (0);
}
