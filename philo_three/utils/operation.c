/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/18 12:22:00 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(philo_t *philo, struct timeval start_time)
{
	long int	time;


	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->data->printf);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d has taken a fork\n", time ,philo->id);
	pthread_mutex_unlock(&philo->data->printf);

	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->data->printf);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d has taken a fork\n", time ,philo->id);
	ft_printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf);
}

void	eat(philo_t *philo, struct timeval start_time)
{
	pthread_mutex_lock(&philo->change_var);
	philo->eattime = actual_time();
	pthread_mutex_unlock(&philo->change_var);
	ft_usleep(philo->data->time_to_eat, philo, actual_time());
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);

}

void	sleeping(philo_t *philo, struct timeval start_time)
{
	long int time;

	pthread_mutex_lock(&philo->data->printf);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	ft_usleep(philo->data->time_to_sleep, philo, actual_time());
}

void	think(philo_t *philo, struct timeval start_time)
{
	long int time;

	pthread_mutex_lock(&philo->data->printf);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d is thinking\n", time , philo->id);
	pthread_mutex_unlock(&philo->data->printf);
}