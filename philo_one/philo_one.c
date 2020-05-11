/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:35:10 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/11 13:58:56 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_one.h"

int		safe_exit(t_data *data)
{
	usleep(20000);
	free(data->ph);
	return (0);
}

int		threading(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_p)
	{
		if (pthread_create(&data->ph[i].thread, NULL, philo,
		(void*)&data->ph[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	*check_limit(t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_p && data->over == 0)
		pthread_mutex_lock(&data->ph[i++].limit_check);
	data->over = 1;
	return (0);
}

int		main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (ft_error(1));
	if (!ft_init_data(&data, ac, av))
		return (ft_error(1));
	if (!(data.ph = ft_init_ph(&data)))
		return (ft_error(2));
	gettimeofday(&data.time, NULL);
	if (!threading(&data))
		return (safe_exit(&data));
	if (data.limit > 0)
		check_limit(&data);
	while (i < data.n_p)
	{
		pthread_join(data.ph[i].thread, NULL);
		i++;
	}
	return (safe_exit(&data));
}
