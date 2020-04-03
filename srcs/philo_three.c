#include "../includes/philo_three.h"

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		write(1, &s[i], 1);
		i++;
	}
}


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

int ft_init_data(t_data *data, int ac, char **av)
{
	data->n_p = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
	{
		data->limit = atoi(av[5]);
//		pthread_mutex_init(&data->limit_mutex, NULL);
		data->limit_sem = sem_open("/limit_sen", O_CREAT | O_EXCL, S_IRWXU, 1);
		if (data->limit_sem == 0)
			return (0);
	}
	else
		data->limit = -1;
	data->limit_check = 0;
	gettimeofday(&data->time, NULL);
//	pthread_mutex_init(&data->lock, NULL);
	sem_unlink("/lock");
	sem_unlink("/forks");
	sem_unlink("/limit_sem");
	sem_unlink("/deads");
	data->lock = sem_open("/lock", O_CREAT | O_EXCL, S_IRWXU, 1);
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	data->deads = sem_open("/deads", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	data->limit_sem = sem_open("/limit_sem", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	if (data->lock == SEM_FAILED || data->forks == SEM_FAILED || data->deads == SEM_FAILED)
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
//		if (!(ph[i] = (t_ph*)malloc(sizeof(t_ph)))) // penser a free si mallox foireux
//			return (NULL);
		ph[i].n = i;
		ph[i].i = 0;
		ph[i].activity = THINKING;
		ph[i].limit = 0;
		ph[i].data = data;
		//data->limit_sem = sem_open("/limit_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
		i++;
	}
	return (ph);
}


void ft_print_datas(t_data *data, t_ph *ph)
{
	int i = 0;

	printf("args: %d %d %d %d\n", data->n_p, data->time_to_die, data->time_to_eat, data->time_to_sleep);
	printf("secs: %ld\n", data->time.tv_sec);
	/*while (i < data->n_p)
	{
		printf("P: %d, act: %d, i: %d\n", ph->n, ph->activity, ph->i);
		if (ph->prev)
			printf("%d\n", ph->prev->n);
		i++;
		ph = ph->next;
	}*/
}

double	get_time(struct timeval ini, struct timeval now)
{
	double	now_ms;

	now_ms = ini.tv_sec + (ini.tv_usec * 0.001);
	now_ms = now.tv_sec + now.tv_usec * 0.001 - now_ms;
	return (now_ms);
}

void *check_limit(void *data2)
{
	t_data *data = (t_data*)data2;
	int i;

	i = 0;
	while (i < data->n_p)
	{
		sem_wait(data->limit_sem);
		i++;
	}
	i = 0;
	while (i < data->n_p)
	{
		kill(data->ph[i].pid, SIGKILL);
		printf("process %d killed\n", i);
		i++;
	}
	printf("All philosophers have eaten at least %d times\n", data->limit);
	exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	t_ph	*ph;
	t_ph 	*b;
	int i;
	int ret;
	if (ac != 5 && ac != 6)
		return (ft_error(1));
	if (!ft_init_data(&data, ac, av))
		return (ft_error(1));
	if (!(ph = ft_init_ph(&data)))
		return (ft_error(2));

	i = 0;
	data.ph = ph;
	while (i < data.n_p)
	{
		sem_wait(data.deads);
		printf("%d\n", i);
		i++;
	}

	i = 0;

	while (i < data.n_p)
	{
		sem_wait(data.limit_sem);
		i++;
	}

	i = 0;

	while (i < data.n_p)
	{
		if ((ph[i].pid = fork()) == 0)
		{
			printf("process %d created\n", i);
			philo(&ph[i]);
			printf("Fork %d ended\n", i);
			exit(0);
		}
		else if (ph[i].pid < 0)
		{
			printf("Error while forking\n");
			return (1);
		}
		i++;
	}
	i = 0;
	usleep(0);

	if (data.limit > 0)
		pthread_create(&data.limit_thread, NULL, check_limit, (void*)&data);

	// check if dead;
	while (1)
	{
		sem_wait(data.deads);
		printf("ici\n");
		while (i < data.n_p)
		{
			kill(ph[i].pid, SIGKILL);
			printf("process %d killed\n", i);
			i++;
		}
		printf("Simulation over\n");
		sem_close(data.limit_sem);
		sem_close(data.lock);
		sem_close(data.forks);
		sem_close(data.deads);
		return (0);
	}
	/*while (i < data.n_p)
	{
		pthread_join(b->thread, NULL);
		i++;
		b = b->next;
	}*/
//	while (data.dead != 1)
//	{
//		continue ;
//	}
/*	struct timeval time2; gettimeofday(&time2, NULL);
	if (data.dead == 1)
		printf("%lf Philosopher %d has died\nEnding sim\n", get_time(data.time, time2), data.id_dead);
	else
		printf("%lf All philosophers have eaten at least %d times\nEnding sim\n", get_time(data.time, time2), data.limit);*/
	sem_close(data.limit_sem);
	sem_close(data.lock);
	sem_close(data.forks);
	sem_close(data.deads);
	return (0);
}
