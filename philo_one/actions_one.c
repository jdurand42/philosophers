#include "../includes/philo_one.h"

void	dying(t_ph *ph)
{
//	pthread_mutex_lock(&ph->data->dead_lock);
	//gettimeofday(&ph->time, NULL);
	ph->activity = DEAD;
	ft_print(ph);
//	pthread_mutex_lock(&ph->data->output);
	ph->data->over = 1;
	pthread_mutex_unlock(&ph->data->dead_lock);
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

	pthread_mutex_lock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
	ph->has_a_fork = 1;
	ft_print(ph);

	pthread_mutex_lock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
	ph->has_a_fork = 1;
	ft_print(ph);
	ph->started_eating = 1;
	ph->i = 0;
	ph->activity = EATING;
	ft_print(ph);
	//ft_print(ph);
	return (0);
}

int 	eating(t_ph *ph)
{
/*	if (ph->data->time_to_eat >= ph->data->time_to_die)
	{
		usleep(ph->data->time_to_eat * 1000);
		pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
		pthread_mutex_unlock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
		pthread_mutex_lock(&ph->data->dead_lock);
		dying(ph);
		return (0);
	}*/

	if (ph->data->over == 1)
	{
		pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
		pthread_mutex_unlock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
		return (0);
	}
	gettimeofday(&ph->start, NULL);
	while (get_time(ph->start, ph->end) < ph->data->time_to_eat)
		gettimeofday(&ph->end, NULL);
	//usleep(ph->data->time_to_eat * TIME);
	ph->limit += 1;
	//pthread_mutex_unlock(&ph->data->limit_lock);
	pthread_mutex_unlock(&ph->data->ph[fork_priority_1(ph->n, ph->data->n_p)].forks);
	pthread_mutex_unlock(&ph->data->ph[fork_priority_2(ph->n, ph->data->n_p)].forks);
	ph->has_a_fork = 0;
	ph->started_eating = 0;
//	gettimeofday(&ph->start, NULL);
	ph->activity = SLEEPING;
	ph->i += ph->data->time_to_eat;
	ft_print(ph);
	return (1);
}

int sleeping(t_ph *ph)
{
	long time;
//	while (ph->i <= ph->data->time_to_sleep + ph->data->time_to_eat && ph->activity != DEAD)
//	{
	if (ph->data->over == 1)
		return (0);
	gettimeofday(&ph->end, NULL);
	while ((time = get_time(ph->start, ph->end)) < ph->data->time_to_sleep)
	{
		if (time > ph->data->time_to_die)
		{
			pthread_mutex_lock(&ph->data->dead_lock);
			dying(ph);
			return (0);
		}
	}

	/*else if (ph->i + ph->data->time_to_sleep >= ph->data->time_to_die)
	{
		usleep((ph->data->time_to_die - ph->i) * 1000);
		pthread_mutex_lock(&ph->data->dead_lock);
		dying(ph);
		return (0);
	}
	else
		usleep(ph->data->time_to_sleep * 1000);*/
	ph->activity = THINKING;
	//ph->i += ph->data->time_to_sleep;
	ft_print(ph);
	return (1);
}
/*
void	*try_wait(void *ph2)
{
	t_ph *ph;

	ph = (t_ph*)ph2;
	while (ph->i < ph->data->time_to_die && ph->started_eating == 0)
	{
		if (ph->data->time_to_die - ph->i > 100)
		{
			usleep(100 * TIME);
			ph->i += 100;
		}
		else
		{
			usleep((ph->data->time_to_die - ph->i) * 1000);
			ph->i += (ph->data->time_to_die - ph->i);
		}
	}
	if (ph->started_eating == 0)
		ph->starved = 1;
	return (NULL);
}
*/
void	*philo(void *b)
{
	pthread_t eating_thread;
	//pthread_t waiting_thread;
	t_ph	*ph;

	ph = (t_ph*)b;
//	if (ph->n == 0)
//		gettimeofday(&ph->data->time, NULL);
	//printf("%d\n", ph->n);
	gettimeofday(&ph->start, NULL);
	//gettimeofday(&ph->end, NULL);
	while (ph->data->over == 0)
	{
		if (ph->activity == THINKING)
		{
			pthread_create(&eating_thread, NULL, try_eating, (void*)ph);
	//		pthread_create(&waiting_thread, NULL, try_wait, (void*)ph);
			while (1)
			{
				gettimeofday(&ph->end, NULL);
				if (ph->data->over == 1)
					return (NULL);
				if (ph->started_eating == 1)
				{
					if (!eating(ph))
						return (NULL);
					break ;
				}
				else if (ph->started_eating == 0 && get_time(ph->start, ph->end) >= ph->data->time_to_die)
				{
					pthread_mutex_lock(&ph->data->dead_lock);
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
