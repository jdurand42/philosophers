#include "../includes/philo_two.h"

void	*dying(t_ph *ph)
{
	ph->activity = DEAD;
	ph->data->dead = 1;
	printf("Dead\n");
//	pthread_mutex_lock(&ph->data->lock);
	if (sem_wait(ph->data->lock) == 0)
	{						
		ph->data->id_dead = ph->n;
		sem_post(ph->data->lock);
	//	sem_close(
		sem_unlink("/lock");
	}
	return (NULL);
}

int	waiting(t_ph *ph, int lock)
{
	usleep(TIME);
	ph->i += 1;
	if (ph->data->dead == 1 || (ph->limit > 0 && ph->data->limit_check >= ph->data->n_p))
	{
		if (lock == 1)
		{
			sem_post(ph->data->forks);
			sem_post(ph->data->forks);
//			pthread_mutex_unlock(&ph->fork);
//			pthread_mutex_unlock(&ph->prev->fork);
		}				
		return (0);
	}
	if (ph->i == ph->data->time_to_eat && ph->activity == EATING)
	{
		ph->activity = SLEEPING;
		printf("Philosopher %d is SLEEPING\n", ph->n);
		sem_post(ph->data->forks);
		sem_post(ph->data->forks);		
//		pthread_mutex_unlock(&ph->fork);
//		pthread_mutex_unlock(&ph->prev->fork);
	}	
	return (1);
}

void	start_eating(t_ph *ph)
{
	ph->i = 0;
//	pthread_mutex_lock(&ph->fork);
//	pthread_mutex_lock(&ph->prev->fork);
	ph->activity = EATING;
	if (ph->data->limit > 0)
	{
		ph->limit += 1;
//		pthread_mutex_lock(&ph->data->limit_mutex);
		sem_wait(ph->data->limit_sem);
		if (ph->limit == ph->data->limit)
			ph->data->limit_check += 1;
		sem_post(ph->data->limit_sem);
//		pthread_mutex_unlock(&ph->data->limit_mutex);
	}		
	printf("Philosopher %d has taken two fork\nPhilosopher %d is EATING\n", ph->n, ph->n);
}	

int	try_unlock(t_ph *ph)
{
	if (sem_wait(ph->data->forks) == 0)
	{
		if (sem_wait(ph->data->forks) == 0)
			return (1);
		else
			sem_post(ph->data->forks);
	}
	return (0);
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
			if (ph->data->dead == 0 && try_unlock(ph))
			{
				start_eating(ph);
				while (ph->i <= ph->data->time_to_eat)
					if (!waiting(ph, 1))
						return (NULL);
			}
			else
			{
				printf("la\n");	
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
