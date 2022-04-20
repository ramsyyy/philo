/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/04/20 17:20:51 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	msg(t_philo *philo, char *msg)
{
	long int	time;

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
	write(1, msg, ft_strlen(msg));
	pthread_mutex_unlock(&philo->data->printf);
}

void	lock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->prev->fork);
		msg(philo, FORK);
		pthread_mutex_lock(&philo->fork);
		msg(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		msg(philo, FORK);
		pthread_mutex_lock(&philo->next->fork);
		msg(philo, FORK);
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->data->nb > 1)
	{
		lock_fork(philo);
		msg(philo, FORK);
		pthread_mutex_lock(&philo->change_var);
		philo->eattime = actual_time();
		philo->nb_each++;
		pthread_mutex_unlock(&philo->change_var);
		msg(philo, EAT);
		ft_usleep(philo->data->time_to_eat, philo, actual_time());
		sleeping(philo);
	}
	else
	{
		if (philo->forks == 0)
		{
			philo->forks = 1;
			msg(philo, FORK);
		}
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_unlock(&philo->prev->fork);
	else
		pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	msg(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep, philo, actual_time());
	msg(philo, THINK);
}
