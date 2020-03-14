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
	return (i);
}
		
int ft_init_data(t_data *data, int ac, char **av)
{
	data->n_p = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->time_to_sleep = atoi(av[5]);
	else
		data->time_to_sleep = 0;
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
		b->activity = 4;	
		b->next = 0;
		b->prev = b_prev;
		b->fork = mutex_mun_cul;
		if (b_prev != 0)
		{
			b_prev->next = b;
		} 
		if (i == 0)
			*ph = b;
		b_prev = b;
		i++;
	}
	if (i > 0)
		b->next = *ph;
	return (0);
}
		
		

int main(int ac, char **av)
{
	t_data	data;
	pthread	table;
	t_ph	*ph;
	t_ph *b;
	int i = 0;
	int ret;
	
	if (ac != 5 && ac != 6)
		return (ft_error(1));
	data = NULL;
	if (!ft_init_data(&data, ac, av))
		return (ft_error(1));
	ph = NULL;
	if (!ft_init_ph(&ph, &data)
		return (ft_error(2));
	while (i < data->n_p)
	{
		b = ph->next;
		ret = pthread_create (&b->thread, NULL, philo, (void*)b);
	}
	i = 0;
	while (i < data->n_p)
	{
		b = ph->next;
		pthread_join(b, NULL);
	}
	return (0);
}
