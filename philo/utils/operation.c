/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/11 21:19:34 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int	take_forks(philo_t *philo, long time, struct timeval start_time)
{
	long time2;

	if (pthread_mutex_lock(&philo->fork) == 0)
	{
		time = get_time(start_time);
		time2 = get_time(philo->eat_time);
		if (time2 >= philo->data->time_to_die)
		{
			printf("%ld %d died\n", time, philo->id);
			exit(0);
		}
		printf("%ld %d has taken a fork\n", time ,philo->id);
			if (pthread_mutex_lock(&philo->next->fork) == 0)
			{
				time2 = get_time(philo->eat_time);
				if (time2 >= philo->data->time_to_die)
				{
					printf("%ld %d died\n", time, philo->id);
					exit(0);
				}
				printf("%ld %d has taken a 2fork\n", time ,philo->id);
			}
			else
				exit (1);
			return (1);
	}
	return (0);
}

int	send_forks(philo_t *philo, int fork)
{
	if (fork == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	return (0);
}

int	eat(philo_t *philo, int fork, long time)
{
	if (fork == 1)
	{
		printf("%ld %d is eating\n", time, philo->id);
		usleep(philo->data->time_to_eat * 1000);
		send_forks(philo, fork);
		return (1);
	}
	return (0);
}

int	sleeping(philo_t *philo, int fork, long time)
{
	printf("%ld %d is sleeping\n", time, philo->id);
	philo->sleep = 1;
	usleep(philo->data->time_to_sleep * 1000);
	return (1);
}

void	think(philo_t *philo, struct timeval start_time)
{
	long time;
	long time2;

	time = get_time(start_time);
	time2 = get_time(philo->eat_time);
	if (time2 >= philo->data->time_to_die)
	{
		printf("%ld %d died\n", time, philo->id);
		exit(0);
	}
	printf("%ld %d is thinking\n", time , philo->id);
}