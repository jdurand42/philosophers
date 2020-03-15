#include "../includes/philo_one.h"

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
		pthread_mutex_init(&data->limit_mutex, NULL);
	}
	else
		data->limit = -1;
	data->dead = 0;
	data->limit_check = 0;
	gettimeofday(&data->time, NULL);
	pthread_mutex_init(&data->lock, NULL);
	if (data->time_to_die > 0 && data->time_to_eat > 0 && data->time_to_sleep > 0 && data->n_p > 0)
		return (1);
	else
		return (0);
}	

int	ft_init_ph(t_ph **ph, t_data *data)
{
	int	i;
	t_ph 	*b;
	t_ph	*b_prev;

	i = 0;
	b_prev = NULL;
	while (i < data->n_p)
	{
		if (!(b = (t_ph*)malloc(sizeof(t_ph)))) // penser a free si mallox foireux
			return (0);
		b->n = i;
		b->i = 0;
		b->activity = THINKING;	
		b->next = 0;
		b->prev = b_prev;
		b->thread = NULL;
//		b->fork = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_init(&b->fork, NULL);
		if (b_prev != 0)
		{
			b_prev->next = b;
		} 
		if (i == 0)
			*ph = b;
		b_prev = b;
		b->data = data;
		i++;
	}
	if (i > 0)
	{
		b->next = *ph;
		(*ph)->prev = b;
	}
	return (1);
}
		
		
void ft_print_datas(t_data *data, t_ph *ph)
{
	int i = 0;
	
	printf("args: %d %d %d %d\n", data->n_p, data->time_to_die, data->time_to_eat, data->time_to_sleep);
	printf("secs: %ld\n", data->time.tv_sec);
	while (i < data->n_p)
	{
		printf("P: %d, act: %d, i: %d\n", ph->n, ph->activity, ph->i);
		if (ph->prev)
			printf("%d\n", ph->prev->n);
		i++;
		ph = ph->next;
	}
}

double	get_time(struct timeval ini, struct timeval now)
{
	double	now_ms;

	now_ms = ini.tv_sec + (ini.tv_usec * 0.001);
	now_ms = now.tv_sec + now.tv_usec * 0.001 - now_ms;
	return (now_ms);
}

int main(int ac, char **av)
{
	t_data	data;
	t_ph	*ph;
	t_ph *b;
	int i = 0;
	int ret;
	printf("%d\n", ac);	
	if (ac != 5 && ac != 6)
		return (ft_error(1));
	if (!ft_init_data(&data, ac, av))
		return (ft_error(1));
	if (data.n_p == 1)
	{
		printf("%d philosopher 0 died\n", data.time_to_die);
		return (0);
	}
	if (!ft_init_ph(&ph, &data))
		return (ft_error(2));
	b = ph;
	//ft_print_datas(&data, ph);
	printf("limit: %d\n", data.limit);
	while (i < data.n_p)
	{
		ret = pthread_create(&b->thread, NULL, philo, (void*)b);
		if (ret != 0)
			return (ft_error(3));
		i++;
		b = b->next;
	}
	i = 0;
//	b = ph;
	while (i < data.n_p)
	{
		pthread_join(b->thread, NULL);
		i++;
		b = b->next;
	}
//	while (data.dead != 1)
//	{	
//		continue ;
//	}
	struct timeval time2; gettimeofday(&time2, NULL);
	if (data.dead == 1)
		printf("%lf Philosopher %d has died\nEnding sim\n", get_time(data.time, time2), data.id_dead);
	else
		printf("%lf All philosophers have eaten at least %d times\nEnding sim\n", get_time(data.time, time2), data.limit);
	return (0);
}
