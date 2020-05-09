#include "../includes/philo_three.h"

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

void init_sems(t_data *data)
{
	sem_unlink("/lock");
	sem_unlink("/forks");
	sem_unlink("/limit_sem");
	sem_unlink("/deads");
	sem_unlink("/dead_lock");
	sem_unlink("/output");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	data->deads = sem_open("/deads", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	data->dead_lock = sem_open("/dead_lock", O_CREAT | O_EXCL, S_IRWXU, 1);
	data->limit_sem = sem_open("/limit_sem", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	data->output = sem_open("/output", O_CREAT | O_EXCL, S_IRWXU, 1);
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
	}
	else
		data->limit = -1;
	gettimeofday(&data->time, NULL);
	init_sems(data);
	if (data->output == SEM_FAILED || data->forks == SEM_FAILED ||
	data->deads == SEM_FAILED
	|| data->limit_sem == SEM_FAILED || data->output == SEM_FAILED)
		return (0);
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
		ph[i].fork = 0;
		ph[i].started_eating = 0;
		i++;
	}
	return (ph);
}


void *check_limit(void *data2)
{
	t_data *data;
	int i;

	i = 0;
	data = (t_data*)data2;
	while (i < data->n_p)
	{
		sem_wait(data->limit_sem);
		i++;
	}
	sem_post(data->deads);
	ft_putstr("All philosophers have eaten enough time\n");
	return (0);
}

void prepare_sems(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_p)
	{
		sem_wait(data->deads);
		i++;
	}
	i = 0;
	while (i < data->n_p)
	{
		sem_wait(data->limit_sem);
		i++;
	}

}

void safe_exit(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->deads);
	sem_close(data->dead_lock);
	sem_close(data->output);
	free(data->ph);
	exit(0);
}

void forking(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_p)
	{
		if ((data->ph[i].pid = fork()) == 0)
		{
		//	printf("process %d created\n", i);
			philo(&data->ph[i]);
		//	printf("Fork %d ended\n", i);
			exit(0);
		}
		else if (data->ph[i].pid < 0)
		{
			ft_putstr("Error while forking\n");
			safe_exit(data);
		}
		i++;
	}
	i = 0;
	if (data->limit > 0)
		pthread_create(&data->limit_thread, NULL, check_limit, (void*)data);
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
	prepare_sems(&data);
	forking(&data);
	while (1)
	{
		sem_wait(data.deads);
		while (i < data.n_p)
		{
			kill(data.ph[i].pid, SIGKILL);
			i++;
		}
		// free ph
		break ;
	}
	//sem_close(data.limit_sem);
	safe_exit(&data);
	return (0);
}
