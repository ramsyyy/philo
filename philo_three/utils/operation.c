/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramsy <ramsy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/22 15:24:54 by ramsy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void msg(philo_t *philo, char *msg)
{
	long int time;
	
	pthread_mutex_lock(&philo->data->printf);
	if (check_stop(philo->data) == 1)
	{
		pthread_mutex_unlock(&philo->data->printf);
		return ;
	}
	time = (actual_time() - philo->data->start);
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	ft_putstr(msg);
	pthread_mutex_unlock(&philo->data->printf);
}


void	take_forks(philo_t *philo, struct timeval start_time)
{
	long int	time;

	pthread_mutex_lock(&philo->fork);
	msg(philo, FORK);
	pthread_mutex_lock(&philo->next->fork);
	msg(philo, FORK);
	msg(philo, EAT);
	pthread_mutex_lock(&philo->change_var);
	philo->eattime = actual_time();
	pthread_mutex_unlock(&philo->change_var);
	ft_usleep(philo->data->time_to_eat, philo, actual_time());
	pthread_mutex_unlock(&philo->fork);
	ft_usleep(2, philo, actual_time());
	pthread_mutex_unlock(&philo->next->fork);
	ft_usleep(2, philo, actual_time());
	sleeping(philo);
	
}

void	sleeping(philo_t *philo)
{
	msg(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep, philo, actual_time());
	msg(philo, THINK);
}
