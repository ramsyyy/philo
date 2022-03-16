/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/16 21:04:10 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	take_forks(philo_t *philo, struct timeval start_time)
{
	int i;
	long int	time;

	i = pthread_mutex_lock(&philo->fork);
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

void	send_forks(philo_t *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	philo->forks = 0;
}

void	eat(philo_t *philo, struct timeval start_time)
{
	philo->eattime = actual_time();
	philo->eat = 1;
	ft_usleep(philo->data->time_to_eat);
	send_forks(philo);
	philo->eattime = actual_time();

}

void	sleeping(philo_t *philo, struct timeval start_time)
{
	int time;

	philo->eat = 0;
	pthread_mutex_lock(&philo->data->printf);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	ft_usleep(philo->data->time_to_sleep);

}

void	think(philo_t *philo, struct timeval start_time)
{
	long time;

	pthread_mutex_lock(&philo->data->printf);
	time = actual_time() - philo->data->start;
	ft_printf("%d %d is thinking\n", time , philo->id);
	pthread_mutex_unlock(&philo->data->printf);
}