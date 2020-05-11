/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:52:01 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/11 16:39:05 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_one.h"

void	ft_print(t_ph *ph)
{
	if (ph->data->over == 1)
		return ;
	ph->time_output = get_time(ph->data->time, ph->end);
	ph->activity_output = ph->activity;
	ph->has_a_fork_output = ph->has_a_fork;
	if ((pthread_create(&ph->output, NULL, ft_print_thread,
	(void*)ph)) != 0)
		return ;
}

void	*ft_print_thread(void *ph)
{
	char	*b;

	if (((t_ph*)(ph))->data->over == 1 && ((t_ph*)(ph))->activity != DEAD)
	{
		return (NULL);
	}
	pthread_mutex_lock(&((t_ph*)(ph))->data->output);
	b = ft_itoa(((t_ph*)(ph))->time_output);
	ft_putstr(b);
	free(b);
	ft_putstr(" ms: ");
	b = ft_itoa(((t_ph*)(ph))->n + 1);
	ft_putstr(b);
	free(b);
	if (((t_ph*)(ph))->activity_output == THINKING && ((t_ph*)(ph))->has_a_fork_output == 0)
		ft_putstr(" is THINKING\n");
	else if (((t_ph*)(ph))->activity_output == EATING)
		ft_putstr(" is EATING\n");
	else if (((t_ph*)(ph))->activity_output == SLEEPING)
		ft_putstr(" is SLEEPING\n");
	else if (((t_ph*)(ph))->activity_output == DEAD)
		ft_putstr(" has died\n");
	else if (((t_ph*)(ph))->activity_output == THINKING &&
	((t_ph*)(ph))->has_a_fork_output == 1)
		ft_putstr(" has taken a fork\n");
	pthread_mutex_unlock(&((t_ph*)(ph))->data->output);
	return (NULL);
}

long	get_time(struct timeval ini, struct timeval now)
{
	long seconds;
	long micros;

	seconds = (now.tv_sec - ini.tv_sec) * 1000;
	micros = (now.tv_usec - (ini.tv_usec)) / 1000;
	return (micros + seconds);
}

int		fork_priority_1(int n, int n_max)
{
	if (n_max % 2)
		return (n);
	else
	{
		if (!(n % 2))
		{
			if (n < n_max - 1)
				return (n + 1);
			else
				return (0);
		}
		else
		{
			return (n);
		}
	}
}

int		fork_priority_2(int n, int n_max)
{
	if (n_max % 2)
	{
		if (n < n_max - 1)
			return (n + 1);
		else
			return (0);
	}
	else
	{
		if (!(n % 2))
			return (n);
		else
		{
			if (n < n_max - 1)
				return (n + 1);
			else
				return (0);
		}
	}
}
