/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeromedu <jeromedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:35:36 by jeromedu          #+#    #+#             */
/*   Updated: 2020/06/02 19:34:50 by jeromedurand     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo_two.h"

void	ft_print(t_ph *ph, int activity)
{
	t_output	*output;

	if (!(output = (t_output*)malloc(sizeof(t_output))))
		return ;
	output->n = ph->n;
	output->activity = activity;
	output->over = ph->data->over;
	output->time_output = get_time(ph->data->time, ph->end);
	output->output = ph->data->output;
	if (ph->data->over == 1)
		return ;
	if ((pthread_create(&ph->output, NULL, ft_print_thread,
	(void*)output)) != 0)
		return ;
}

void	*ft_print_thread(void *output)
{
	char	*b;

	sem_wait(((t_output*)(output))->output);
	b = ft_itoa(((t_output*)(output))->time_output);
	ft_putstr(b);
	free(b);
	ft_putstr(" ms: ");
	b = ft_itoa(((t_output*)(output))->n + 1);
	ft_putstr(b);
	free(b);
	if (((t_output*)(output))->activity == THINKING)
		ft_putstr(" is THINKING\n");
	else if (((t_output*)(output))->activity == EATING)
		ft_putstr(" is EATING\n");
	else if (((t_output*)(output))->activity == SLEEPING)
		ft_putstr(" is SLEEPING\n");
	else if (((t_output*)(output))->activity == DEAD)
		ft_putstr(" has died\n");
	else if (((t_output*)(output))->activity == FORK)
		ft_putstr(" has taken a fork\n");
	sem_post(((t_output*)(output))->output);
	free(output);
	return (NULL);
}
/*
void	ft_print(t_ph *ph, int activity)
{
	t_output	*output;

	if (ph->data->over == 1)
		return ;
	if (!(output = (t_output*)malloc(sizeof(t_output))))
		return ;
	output->activity = activity;
	output->ph = ph;
	output->time_output = get_time(ph->data->time, ph->end);
	if ((pthread_create(&ph->output, NULL, ft_print_thread,
	(void*)output)) != 0)
		return ;
}

void	*ft_print_thread(void *output)
{
	char		*b;
	t_output 	*out;

	out = (t_output*)output;
	sem_wait(out->ph->data->output);
	b = ft_itoa(out->time_output);
	ft_putstr(b);
	free(b);
	ft_putstr(" ms: ");
	b = ft_itoa(out->ph->n + 1);
	ft_putstr(b);
	free(b);
	if (out->activity == THINKING)
		ft_putstr(" is THINKING\n");
	else if (out->activity == EATING)
		ft_putstr(" is EATING\n");
	else if (out->activity == SLEEPING)
		ft_putstr(" is SLEEPING\n");
	else if (out->activity == DEAD)
		ft_putstr(" has died\n");
	else if (out->activity == FORK)
		ft_putstr(" has taken a fork\n");
	sem_post(out->ph->data->output);
	free(output);
	return (NULL);
}*/

long	get_time(struct timeval ini, struct timeval now)
{
	/*long seconds;
	long micros;

	seconds = (now.tv_sec - ini.tv_sec) * 1000;
	micros = (now.tv_usec - (ini.tv_usec)) / 1000;*/
	return (((now.tv_sec - ini.tv_sec) * 1000) +
	((now.tv_usec - (ini.tv_usec)) / 1000));
}
