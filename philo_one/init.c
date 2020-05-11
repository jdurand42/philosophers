/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:17:56 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/11 13:12:00 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_one.h"

int		ft_error(int i)
{
	if (i == 1)
	{
		ft_putstr("Error: arguments\n");
		ft_putstr("Must be: [nb of philosophers] [time_to_die] [time_to_eat]");
		ft_putstr("[time_to_sleep] [optionnal:");
		ft_putstr("nb_ot_time_each_philosophers_to_eat]\n");
	}
	else if (i == 2)
		ft_putstr("Error on a Malloc\n");
	else if (i == 3)
		ft_putstr("Error while creating threads\n");
	return (i);
}

int		init_mutex(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (pthread_mutex_init(&data->dead_lock, NULL) ||
	pthread_mutex_init(&data->output, NULL))
		return (0);
	return (1);
}

int		ft_init_data(t_data *data, int ac, char **av)
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
	if (!init_mutex(data))
		return (0);
	data->over = 0;
	data->limit_check = 0;
	if (data->time_to_die > 0 && data->time_to_eat > 0 &&
	data->time_to_sleep > 0 && data->n_p > 1)
		return (1);
	else
		return (0);
}

t_ph	*ft_init_ph(t_data *data)
{
	int		i;
	t_ph	*ph;

	i = 0;
	if (!(ph = (t_ph*)malloc(data->n_p * sizeof(t_ph))))
		return (NULL);
	while (i < data->n_p)
	{
		ph[i].n = i;
		ph[i].activity = THINKING;
		ph[i].limit = 0;
		ph[i].data = data;
		ph[i].has_a_fork = 0;
		ph[i].started_eating = 0;
		ph[i].fork_priority_1 = fork_priority_1(ph[i].n, data->n_p);
		ph[i].fork_priority_2 = fork_priority_2(ph[i].n, data->n_p);
		if (pthread_mutex_init(&ph[i].forks, NULL) != 0 ||
		pthread_mutex_init(&ph[i].limit_check, NULL) != 0)
			return (NULL);
		pthread_mutex_lock(&ph[i].limit_check);
		i++;
	}
	return (ph);
}
