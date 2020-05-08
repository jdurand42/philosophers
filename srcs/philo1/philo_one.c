#include "../../includes/philo_one.h"

int	ft_error(int i)
{
	if (i == 1)
	{
		ft_putstr("Error: arguments\n");
		ft_putstr("Must be: [nb of philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optionnal: nb_ot_time_each_philosophers_to_eat]\n");
	}
	else if (i == 2)
		ft_putstr("Error on a Malloc\n");
	else if (i == 3)
		ft_putstr("Error while creating threads\n");
	return (i);
}

int init_mutex(t_data *data)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
/*	if (!(data->forks = malloc(data->n_p * sizeof(pthread_mutex_t))))
		return (0);
	while (i < data->n_p)
	{
		printf("%d\n", i);
		ret = pthread_mutex_init(data->forks[i], NULL);
		if (ret != 0)
			return (0);

		i++;
	}*/
	//data->deads = sem_open("/deads", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (pthread_mutex_init(data->dead_lock, NULL) ||
	pthread_mutex_init(data->limit_lock , NULL) ||
	pthread_mutex_init(data->output, NULL))
		return (0);
	return (1);
}

int ft_init_data(t_data *data, int ac, char **av)
{
	data->n_p = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->limit = ft_atoi(av[5]);
		if (data->limit <= 0)
			return (0);
		data->limit_check = 0;
	}
	else
		data->limit = -1;
	gettimeofday(&data->time, NULL);
	if (!init_mutex(data))
		return (0);
	data->over = 0;
	if (data->time_to_die > 0 && data->time_to_eat > 0 && data->time_to_sleep > 0 && data->n_p > 0)
		return (1);
	else
		return (0);
}

t_ph	*ft_init_ph(t_data *data)
{
	int	i;
	t_ph	*ph;

	i = 0;
	if (!(ph = (t_ph*)malloc(data->n_p * sizeof(t_ph))))
		return (NULL);
	while (i < data->n_p)
	{
		ph[i].n = i;
		ph[i].i = 0;
		ph[i].activity = THINKING;
		ph[i].limit = 0;
		ph[i].data = data;
		ph[i].has_a_fork = 0;
		ph[i].started_eating = 0;
		if (pthread_mutex_init(ph[i].forks, NULL) != 0)
			return (NULL);
		i++;
	}
	return (ph);
}


void *check_limit(void *data2)
{
	t_data *data = (t_data*)data2;
	int i;

	i = 0;
	while (1)
	{
		if (data->limit_check >= data->limit)
			break ;
	}
	pthread_mutex_lock(data->output);
	ft_putstr("All philosophers have eaten enough time\n");
	data->over = 1;
	// free all ph;
	return (0);
}

int safe_exit(t_data *data)
{
	free(data->ph);
	return (0);
}

int threading(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_p)
	{
		if (pthread_create(&data->ph[i].thread, NULL, philo, (void*)&data->ph[i]) != 0)
			return (0);
		i++;
	}
	if (data->limit > 0)
		if (pthread_create(&data->limit_thread, NULL, check_limit, (void*)data) != 0)
			return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_data	data;
	int i;

	if (ac != 5 && ac != 6)
		return (ft_error(1));
	if (!ft_init_data(&data, ac, av))
		return (ft_error(1));
	if (!(data.ph = ft_init_ph(&data)))
		return (ft_error(2));
	i = 0;
	if (!threading(&data))
		return (safe_exit(&data));
	while (data.over != 1)
		continue ;
	ft_putstr("Simulation over\n");
	return (safe_exit(&data));
		// free ph
		//break ;
	//sem_close(data.limit_sem);
}
