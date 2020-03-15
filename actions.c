#include "philosophers.h"

void	*philo(void *b)
{
	t_ph *ph;

	ph = (t_ph*)b;
//	ph->activity = SLEEPING;
	while (1)
	{
		if (ph->activity & DEAD || ph->prev->activity == DEAD || ph->next->activity == DEAD || ph->data->dead == 1)
			return NULL;
		if (ph->activity == THINKING)
		{
// int pthread_mutex_lock(pthread_mutex_t *mutex))
			if (ph->prev->i != 0 && ph->next->i != 0)
			{
				ph->i = 0;
				pthread_mutex_lock(&ph->fork);
				pthread_mutex_lock(&ph->prev->fork);
				ph->activity = EATING;
				printf("Philosophers %d is EATING\n", ph->n);
				usleep(ph->data->time_to_eat);
				ph->activity = SLEEPING;
				pthread_mutex_unlock(&ph->fork);
				pthread_mutex_unlock(&ph->prev->fork);
			}
			else
			{	
				if (ph->activity != SLEEPING)
				{
					usleep(TIME);
					ph->i += TIME;
				//	printf("p: %d, %d\n", ph->n, ph->i);
					if (ph->i >= ph->data->time_to_die)
					{
						ph->activity = DEAD;
						pthread_mutex_lock(&ph->data->lock);
						ph->data->dead = 1;
						ph->data->id_dead = ph->n;
						printf("%d is dead\n", ph->n);
					}
				}
			}
		}
		if (ph->activity == SLEEPING)
		{
			printf("Philosopher %d is SLEEPING\n", ph->n);
			while (ph->i <= ph->data->time_to_sleep && ph->activity != DEAD)
			{
				usleep(TIME);
				ph->i += TIME;
				if (ph->i >= ph->data->time_to_die)
				{
					ph->activity = DEAD;
					ph->data->dead = 1;
					pthread_mutex_lock(&ph->data->lock);						ph->data->id_dead = ph->n;
					printf("Dead\n");
				}
			}
			if (ph->activity != DEAD)
			{
				ph->activity = THINKING;
				printf("Philosopher %d is THINKING\n", ph->n);
			}
		}
	}
	return (NULL);
}
