/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramsy <ramsy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/14 20:24:48 by ramsy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int	take_forks(philo_t *philo, long time, struct timeval start_time)
{
	int i;
	if (philo->next->forks == 0 || philo->prev->forks == 0)
	{
		i = pthread_mutex_lock(&philo->fork);
			if (i == 0)
			{
				time = get_time(start_time);
				philo->time2 = get_time(philo->eat_time);
				if (philo->time2 >= philo->data->time_to_die)
				{
					printf("%ld %d died\n", time, philo->id);
					exit(0);
				}
				philo->forks = 1;
				printf("%ld %d has taken a fork\n", time ,philo->id);
				while (1)
				{
					philo->time2 = get_time(start_time);
					//printf("philo id = %d next = %d prev = %d time2 = %ld time->next = %ld\n", philo->id,  philo->next->forks, philo->prev->forks, philo->time2, philo->time2);
					if (philo->next->forks == 0)
					{
						i = pthread_mutex_lock(&philo->next->fork);
						//printf("philo id = %d next = %d prev = %d time2 = %ld time->next = %ld      QWQWQWQ %d\n", philo->id,  philo->next->forks, philo->prev->forks, philo->time2, philo->time2, i);
						if (i == 0)
						{
							philo->time2 = get_time(philo->eat_time);
							if (philo->time2 >= philo->data->time_to_die)
							{
								printf("%ld %d died\n", time, philo->id);
								exit(0);
							}
							printf("%ld %d has taken a 2fork\n", time ,philo->id);
							return (1);
						}	
					}
					else if (philo->prev->forks == 0 && philo->next->forks != 0)
					{
						i = pthread_mutex_lock(&philo->prev->fork);
							if (i == 0)
							{
								philo->time2 = get_time(philo->eat_time);
								if (philo->time2 >= philo->data->time_to_die)
								{
									printf("%ld %d died\n", philo->time2, philo->id);
									exit(0);
								}
								printf("%ld %d has taken a 3fork\n", philo->time2 ,philo->id);
								return (1);
							}
					}
				}
			}
	}
	return (0);
}

int	send_forks(philo_t *philo, int fork)
{
	if (fork == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		philo->forks = 0;
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
		gettimeofday(&philo->eat_time, NULL);
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

	time = get_time(start_time);
	philo->time2 = get_time(philo->eat_time);
	if (philo->time2 >= philo->data->time_to_die)
	{
		printf("%ld %d died\n", time, philo->id);
		exit(0);
	}
	printf("%ld %d is thinking\n", time , philo->id);
	usleep(600);
}