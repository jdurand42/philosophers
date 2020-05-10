/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:45:25 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/10 19:19:41 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*check_limit(void *data2)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data*)data2;
	while (i < data->n_p)
	{
		if (data->over == 1)
			return (NULL);
		sem_wait(data->limit_sem);
		i++;
	}
	sem_post(data->deads);
	return (0);
}

void	prepare_sems(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_p)
	{
		sem_wait(data->deads);
		i++; /* A CHANGER ? */
	}
	i = 0;
	while (i < data->n_p)
	{
		sem_wait(data->limit_sem);
		i++;
	}
}

void	safe_exit(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->deads);
	sem_close(data->dead_lock);
	sem_close(data->output);
	//sem_close(data->limit_sem);
	sem_unlink("/forks");
	sem_unlink("/limit_sem");
	sem_unlink("/deads");
	sem_unlink("/dead_lock");
	sem_unlink("/output");
	free(data->ph);
	exit(0);
}

void	forking(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_p)
	{
		if ((data->ph[i].pid = fork()) == 0)
		{
			philo(&data->ph[i]);
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
	gettimeofday(&data.time, NULL);
	forking(&data);
	while (1)
	{
		sem_wait(data.deads);
		data.over = 1;
		while (i < data.n_p)
		{
			kill(data.ph[i].pid, SIGKILL);
			i++;
		}
		break ;
	}
	safe_exit(&data);
	return (0);
}
