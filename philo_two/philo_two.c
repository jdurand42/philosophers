/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:35:33 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/11 11:58:22 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void	*check_limit(void *data2)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data*)data2;
	while (i < data->n_p)
	{
		if (data->over == 1)
			return (0);
		sem_wait(data->limit_sem);
		i++;
	}
	data->over = 1;
	sem_post(data->deads);
	return (0);
}
// CHECK IF ANY PRINTF/EXIT lol
void	prepare_sems(t_data *data)
{
	int	i;

	//sem_wait(data->deads);
	i = 0;
	while (i < data->n_p)
	{
		sem_wait(data->limit_sem);
		i++;
	}
	i = 0;
	while (i < data->n_p)
	{
		sem_wait(data->deads);
		i++;
	}
}

int		safe_exit(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_p)
		pthread_join(data->ph[i++].thread, NULL);
	printf("prout\n");
	sem_unlink("/forks");
	sem_unlink("/limit_sem");
	sem_unlink("/deads");
	sem_unlink("/dead_lock");
	sem_unlink("/output");
	free(data->ph);
	return (0);
}

int		threading(t_data *data)
{
	int i;

	i = 0;
	gettimeofday(&data->time, NULL);
	if (data->limit > 0)
		if (pthread_create(&data->limit_thread, NULL, check_limit,
		(void*)data) != 0)
			return (0);
	while (i < data->n_p)
	{
		if (pthread_create(&data->ph[i].thread, NULL, philo,
		(void*)&data->ph[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac != 5 && ac != 6)
		return (ft_error(1));
	if (!ft_init_data(&data, ac, av))
		return (ft_error(1));
	if (!(data.ph = ft_init_ph(&data)))
		return (ft_error(2));
	i = 0;
	prepare_sems(&data);
	if (!threading(&data))
		return (safe_exit(&data));
	while (1)
	{
		sem_wait(data.deads);
		return (safe_exit(&data));
	}
	safe_exit(&data);
	return (0);
}
