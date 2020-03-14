#include "philosophers.h"

void	**philo(void *b)
{
	t_ph *ph;

	ph = (t_ph*)b;
	while (1)
	{
		if (ph->activity & DEAD)
			return NULL;
		if (ph->activity & THINKING)
		{
			if (unlock, && unlock (ph->prev->fork))
			{
				lock && lock prev->fork;
				ph->activity = EATING;
				ph->i = 0;
				printf("Philosophers %d is EATING\n", ph->n);
//				while (ph->i <= ph->data->time_to_eat)
//				{
					usleep(ph->data->time_to_eat);
//					ph->i += TIME;
				}
				unlock && unlock prev;
				ph->i = 0;
				ph->activity = SLEEPING;
			}
			else
			{
				usleep(TIME)
				ph->i += TIME;
				if (ph->i >= ph->data->time_to_die)
					ph->activity = DEAD;
			}
		}
		if (ph->activity & SLEEPING)
		{
			printf("Philosopher %d is SLEEPING\n", ph->n);
			while (ph->i <= ph->data->time_to_sleep && ph->activity != DEAD)
			{
				usleep(TIME);
				ph->i += TIME;
				if (ph->i >= ph->data->time_to_die)
					ph->acticity = DEAD;
			}
			if (ph->activity != DEAD)
			{
				ph->activity = THINKING;
				printf("Philosopher %d is THINKING\n", ph->n);
			}
		}
	}
	return NULL;
}
