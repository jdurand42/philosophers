/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:35:36 by jeromedu          #+#    #+#             */
/*   Updated: 2020/05/10 18:36:55 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void	ft_print(t_ph *ph)
{
	struct timeval	now;
	char			*b;

	if (ph->data->over == 1)
		return ;
	gettimeofday(&now, NULL);
	sem_wait(ph->data->output);
	b = ft_itoa(get_time(ph->data->time, now));
	ft_putstr(b);
	free(b);
	ft_putstr(" ms: ");
	b = ft_itoa(ph->n + 1);
	ft_putstr(b);
	free(b);
	if (ph->activity == THINKING && ph->fork == 0)
		ft_putstr(" is THINKING\n");
	else if (ph->activity == EATING)
		ft_putstr(" is EATING\n");
	else if (ph->activity == SLEEPING)
		ft_putstr(" is SLEEPING\n");
	else if (ph->activity == DEAD)
		ft_putstr(" has died\n");
	else if (ph->activity == THINKING && ph->fork == 1)
		ft_putstr(" has taken a fork\n");
	sem_post(ph->data->output);
}

long	get_time(struct timeval ini, struct timeval now)
{
	long seconds;
	long micros;

	seconds = (now.tv_sec - ini.tv_sec) * 1000;
	micros = (now.tv_usec - (ini.tv_usec)) / 1000;
	return (micros + seconds);
}
