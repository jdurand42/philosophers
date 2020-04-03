#include "../includes/philo_three.h"

void	*dying(t_ph *ph)
{
	ph->activity = DEAD;
	//printf("Philosopher %d has Died\n", ph->n);
	ft_print(" has died\n", 0, ph->n);
	sem_post(ph->data->deads);
	printf("Je suis ici\n");
	exit (0);
//	pthread_mutex_lock(&ph->data->lock);
//	if (sem_wait(ph->data->lock) == 0)
//	{
//		sem_post(ph->data->lock);
	//	sem_close(
//		sem_unlink("/lock");
	return (NULL);
}

int	waiting(t_ph *ph, int lock)
{
	usleep(TIME);
	ph->i += 1;
/*	if (ph->data->dead == 1 || (ph->limit > 0 && ph->data->limit_check >= ph->data->n_p))
	{
		if (lock == 1)
		{
			sem_post(ph->data->forks);
			sem_post(ph->data->forks);
//			pthread_mutex_unlock(&ph->fork);
//			pthread_mutex_unlock(&ph->prev->fork);
		}
		return (0);
	}*/
	if (ph->i == ph->data->time_to_eat && ph->activity == EATING)
	{
		ph->activity = SLEEPING;
		//printf("Philosopher %d is SLEEPING\n", ph->n);
		ft_print(" is SLEEPING\n", 0, ph->n);
		sem_post(ph->data->forks);
		sem_post(ph->data->forks);
//		pthread_mutex_unlock(&ph->fork);
//		pthread_mutex_unlock(&ph->prev->fork);
	}
	return (1);
}
/*
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
}*/

void	*try_eating(void *ph2)
{
	t_ph *ph = (t_ph*)ph2;
	sem_wait(ph->data->forks);
	//printf("Philosopher %d has taken a fork\n", ph->n);
	ft_print(" has taken a FORK\n", 0, ph->n);
	sem_wait(ph->data->forks);

	ph->started_eating = 1;

	//printf("Philosopher %d has taken a fork\n", ph->n);
	ft_print(" has taken a FORK\n", 0, ph->n);
	return (0);
}

void eating(t_ph *ph)
{
	ph->i = 0;
	ph->activity = EATING;
//	printf("Philosopher %d is EATING\n", ph->n);
	ft_print(" is EATING\n", 0, ph->n);

	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		usleep(ph->data->time_to_die);
		dying(ph);
	}
	usleep(ph->data->time_to_eat * TIME);

	ph->limit += 1;
	if (ph->data->limit > 0 && ph->limit == ph->data->limit)
		sem_post(ph->data->limit_sem);

	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
	ph->started_eating = 0;

	ph->activity = SLEEPING;
	ph->i += ph->data->time_to_eat;
//	printf("Philosopher %d is SLEEPING\n", ph->n);
	ft_print(" is SLEEPING\n", 0, ph->n);
}

void	*philo(t_ph *ph)
{
	ph->started_eating = 0;
	pthread_t eating_thread = NULL;

	while (1)
	{
	//	if (ph->activity & DEAD || ph->prev->activity == DEAD || ph->next->activity == DEAD || ph->data->dead == 1)
	//		return NULL;
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
					usleep(TIME);
					ph->i += 1;
					//printf("ici\n");
					if (ph->i >= ph->data->time_to_die)
					{
						printf("arg!!\n");
						dying(ph);
					}
				}
			}
		}
		else
		{
			//	printf("la\n");
			if (ph->activity != SLEEPING)
			{
				if (!waiting(ph, 0))
					return (NULL);
				if (ph->i >= ph->data->time_to_die)
					return (dying(ph));
			}
		}
		if (ph->activity == SLEEPING)
		{

			while (ph->i <= ph->data->time_to_sleep + ph->data->time_to_eat && ph->activity != DEAD)
			{
				if (!waiting(ph, 0))
					return (NULL);
				if (ph->i >= ph->data->time_to_die)
					return (dying(ph));
			}
			ph->activity = THINKING;
			//printf("Philosopher %d is THINKING\n", ph->n);
			ft_print(" is THINKING\n", 0, ph->n);
		}
	}
	return (NULL);
}
