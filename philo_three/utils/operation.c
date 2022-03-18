/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/18 17:09:27 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(philo_t *philo, struct timeval start_time)
{
	long int	time;

	if (check_stop(philo->data) == 0 && pthread_mutex_lock(&philo->fork) == 0)
	{
		if (pthread_mutex_lock(&philo->data->printf) == 0)
		{
			if (check_stop(philo->data) == 1)
					return(0);
			time = actual_time() - philo->data->start;
			ft_printf("%d %d has taken a fork\n", time ,philo->id);
			pthread_mutex_unlock(&philo->data->printf);
		}
		else
			return (0);
		if (check_stop(philo->data) == 0 && pthread_mutex_lock(&philo->next->fork) == 0)
		{
			if (check_stop(philo->data) == 0 && pthread_mutex_lock(&philo->data->printf) == 0)
			{
				time = actual_time() - philo->data->start;
				ft_printf("%d %d has taken a fork\n", time ,philo->id);
				ft_printf("%d %d is eating\n", time, philo->id);		
				pthread_mutex_unlock(&philo->data->printf);
				if (check_stop(philo->data) == 0)
					return(1);
			}
			else
				return (0);
		}
	}
	else
		return (0);
}

int	eat(philo_t *philo, struct timeval start_time)
{
		pthread_mutex_lock(&philo->change_var);
		philo->eattime = actual_time();
		pthread_mutex_unlock(&philo->change_var);
		ft_usleep(philo->data->time_to_eat, philo, actual_time());
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return (1);
}

int	sleeping(philo_t *philo, struct timeval start_time)
{
	long int time;

	if (check_stop(philo->data) == 0 && pthread_mutex_lock(&philo->data->printf) == 0)
	{
		time = actual_time() - philo->data->start;
		ft_printf("%d %d is sleeping\n", time, philo->id);
		pthread_mutex_unlock(&philo->data->printf);
		ft_usleep(philo->data->time_to_sleep, philo, actual_time());
		return (1);
	}
	else
		return (0);
}

int	think(philo_t *philo, struct timeval start_time)
{
	long int time;

	if (check_stop(philo->data) == 0 && pthread_mutex_lock(&philo->data->printf) == 0)
	{
		time = actual_time() - philo->data->start;
		ft_printf("%d %d is thinking\n", time , philo->id);
		pthread_mutex_unlock(&philo->data->printf);
		return (1);
	}
	else
		return (0);
}
