#include "../../includes/philo_one.h"

void	dying(t_ph *ph)
{
	pthread_mutex_lock(&ph->data->dead_lock);
	ph->activity = DEAD;
	ft_print(ph);
//	pthread_mutex_lock(&ph->data->output);
	ph->data->over = 1;
	pthread_mutex_unlock(&ph->data->dead_lock);
}

int	waiting(t_ph *ph)
{
	if (ph->data->over == 1)
	{
		return (0);
	}
	usleep(TIME);
	ph->i += 1;
	return (1);
}

int fork_priority_1(int n, int n_max)
{
	if (!(n % 2))
	{
		if (n < n_max - 1)
			return (n + 1);
		else
			return (0);
	}
	else
		return (n);
}

int fork_priority_2(int n, int n_max)
{
	if (!(n % 2))
		return (n);
	else
	{
		if (n < n_max - 1)
			return (n + 1);
		else
			return (0);
	}
}

void	*try_eating(void *ph2)
{
	t_ph *ph = (t_ph*)ph2;

/*	while (ph->data->ph[fork_priority(ph->n, ph->data->n_p)].fork == 1 ||
	ph->data->ph[ph->n].fork == 1)
		continue ;*/
	pthread_mutex_lock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
	ph->has_a_fork = 1;
	ft_print(ph);
	/*if (ph->data->over == 1)
	{
		pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
		return (0);
	}*/
	pthread_mutex_lock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
/*	if (ph->data->over == 1)
	{
		pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
		pthread_mutex_unlock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
		return (0);
	}*/
	ph->has_a_fork = 1;
	ft_print(ph);
//	ph->has_a_fork = 1;
//	ft_print(ph);

	ph->started_eating = 1;
	//ft_print(ph);
	return (0);
}

int 	eating(t_ph *ph)
{
	ph->i = 0;
	ph->activity = EATING;
	ft_print(ph);
	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		usleep(ph->data->time_to_die * 1000);
		pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
		pthread_mutex_unlock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
		dying(ph);
		return (0);
	}
	if (ph->data->over == 1)
	{
		pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
		pthread_mutex_unlock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
		return (0);
	}
	usleep(ph->data->time_to_eat * TIME);
	ph->limit += 1;
	//pthread_mutex_unlock(&ph->data->limit_lock);
	pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
	pthread_mutex_unlock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
	ph->has_a_fork = 0;
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
		if (!(waiting(ph)))
		{
			return (0);
		}
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
