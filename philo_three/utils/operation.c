/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramsy <ramsy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/17 01:15:35 by ramsy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mortel(philo_t *philo)
{
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->printf);
		usleep(10000);
	}
}

void	take_forks(philo_t *philo, struct timeval start_time)
{
	long int	time;

	
	pthread_mutex_lock(&philo->fork);
	
	pthread_mutex_lock(&philo->data->printf);
	mortel(philo);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d has taken a fork\n", time ,philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	pthread_mutex_lock(&philo->next->fork);
	
	pthread_mutex_lock(&philo->data->printf);
	mortel(philo);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d has taken a fork\n", time ,philo->id);
	pthread_mutex_unlock(&philo->data->printf);
}

void	send_forks(philo_t *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	mortel(philo);
}

void	eat(philo_t *philo, struct timeval start_time)
{
	long int time;


	pthread_mutex_lock(&philo->data->printf);
	mortel(philo);
	philo->eat = 1;
	philo->eattime = actual_time();
	time = actual_time() - philo->data->start;
	ft_printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	philo->eattime = actual_time();
}

void	sleeping(philo_t *philo, struct timeval start_time)
{
	long int time;

	philo->eat = 0;
	
	pthread_mutex_lock(&philo->data->printf);
	mortel(philo);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	think(philo_t *philo, struct timeval start_time)
{
	long int time;

	
	pthread_mutex_lock(&philo->data->printf);
	mortel(philo);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d is thinking\n", time , philo->id);
	pthread_mutex_unlock(&philo->data->printf);
}