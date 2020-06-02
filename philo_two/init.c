/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:20:05 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/02 13:15:24 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_two.h"

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

void	init_sems(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/limit_sem");
	sem_unlink("/deads");
	sem_unlink("/dead_lock");
	sem_unlink("/output");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	data->deads = sem_open("/deads", O_CREAT | O_EXCL, S_IRWXU, data->n_p);
	data->dead_lock = sem_open("/dead_lock", O_CREAT | O_EXCL, S_IRWXU, 1);
	data->limit_sem = sem_open("/limit_sem", O_CREAT | O_EXCL, S_IRWXU,
	data->n_p);
	data->output = sem_open("/output", O_CREAT | O_EXCL, S_IRWXU, 1);
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
	init_sems(data);
	if (data->output == SEM_FAILED || data->forks == SEM_FAILED ||
	data->deads == SEM_FAILED
	|| data->limit_sem == SEM_FAILED || data->output == SEM_FAILED)
		return (0);
	data->over = 0;
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
		ph[i].limit = 0;
		ph[i].data = data;
		ph[i].started_eating = 0;
		i++;
	}
	return (ph);
}
