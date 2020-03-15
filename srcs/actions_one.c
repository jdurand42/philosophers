#include "../includes/philo_one.h"

void	*dying(t_ph *ph)
{
	ph->activity = DEAD;
	ph->data->dead = 1;
	pthread_mutex_lock(&ph->data->lock);						
	ph->data->id_dead = ph->n;
	return (NULL);
}

int	waiting(t_ph *ph, int lock)
{
	usleep(TIME);
	ph->i += 1;
	if (ph->data->dead == 1)
	{
		if (lock == 1)
		{
			pthread_mutex_unlock(&ph->fork);
			pthread_mutex_unlock(&ph->prev->fork);
		}				
		return (0);
	}
	if (ph->i == ph->data->time_to_eat && ph->activity == EATING)
	{
		ph->activity = SLEEPING;
		printf("Philosopher %d is SLEEPING\n", ph->n);		
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(&ph->prev->fork);
	}	
	return (1);
}

void	start_eating(t_ph *ph)
{
	ph->i = 0;
	pthread_mutex_lock(&ph->fork);
	pthread_mutex_lock(&ph->prev->fork);
	ph->activity = EATING;
	printf("Philosopher %d has taken two fork\nPhilosopher %d is EATING\n", ph->n, ph->n);
}
	

void	*philo(void *b)
{
	t_ph *ph;

	ph = (t_ph*)b;
	while (1)
	{
	//	if (ph->activity & DEAD || ph->prev->activity == DEAD || ph->next->activity == DEAD || ph->data->dead == 1)
	//		return NULL;
		if (ph->activity == THINKING)
		{
			if (ph->data->dead == 0 && ph->prev->activity != EATING && ph->next->activity != EATING)
			{
				start_eating(ph);
				while (ph->i <= ph->data->time_to_eat)
					if (!waiting(ph, 1))
						return (NULL);
			}
			else
			{	
				if (ph->activity != SLEEPING)
				{
					if (!waiting(ph, 0))
						return (NULL);
					if (ph->i >= ph->data->time_to_die)
						return (dying(ph));
				}
			}
		}
		if (ph->activity == SLEEPING)
		{
			while (ph->i <= ph->data->time_to_sleep && ph->activity != DEAD)
			{
				if (!waiting(ph, 0))
					return (NULL);
				if (ph->i >= ph->data->time_to_die)
					return (dying(ph));
			}
			ph->activity = THINKING;
			printf("Philosopher %d is THINKING\n", ph->n);
		}
	}
	return (NULL);
}
