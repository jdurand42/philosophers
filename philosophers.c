#include "philosophers.h"

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
		data->limit = atoi(av[5]);
	else
		data->limit = -1;
	data->dead = 0;
	pthread_mutex_init(&data->lock, NULL);
	if (data->time_to_die > 0 && data->time_to_eat > 0 && data->time_to_sleep > 0 && data->n_p > 0)
		return (1);
	else
		return (0);
}	

void	ft_init_philo(t_ph *ph, t_data *data)
{
	ph->i = 0;
	ph->data = data;
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
	while (i < data->n_p)
	{
		printf("P: %d, act: %d, i: %d\n", ph->n, ph->activity, ph->i);
		if (ph->prev)
			printf("%d\n", ph->prev->n);
		i++;
		ph = ph->next;
	}
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
	ph = NULL;
	if (!ft_init_ph(&ph, &data))
		return (ft_error(2));
	b = ph;
	ft_print_datas(&data, ph);
	printf("%d\n", ph->data->time_to_sleep);
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
	b = ph;
//	while (i < data.n_p)
//	{
//		pthread_join(b->thread, NULL);
//		i++;
//		b = b->next;
//	}
	while (data.dead != 1)
	{	
		continue ;
	}
	printf("Philosopher %d has died\nEnding sim\n", data.id_dead);
	return (0);
}
