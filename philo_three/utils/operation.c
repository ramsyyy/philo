/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:11:01 by raaga             #+#    #+#             */
/*   Updated: 2022/03/15 18:54:03 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int	take_forks(philo_t *philo, int time, struct timeval start_time)
{
	int i;


		i = pthread_mutex_lock(&philo->fork);
			if (i == 0)
			{
				time = get_time(start_time);
				philo->time2 = get_time(philo->eat_time);
				if (philo->time2 >= philo->data->time_to_die)
				{
					pthread_mutex_lock(&philo->data->printf);
					time = get_time(start_time);
					ft_printf("%d %d died\n", time, philo->id);
					exit(0);
					pthread_mutex_unlock(&philo->data->printf);

				}
				philo->forks = 1;
				/*pthread_mutex_lock(&philo->data->printf);
				time = get_time(start_time);
				ft_printf("%d %d has taken a fork\n", time ,philo->id);
				pthread_mutex_unlock(&philo->data->printf);*/
				while (philo->next->forks != 0 && philo->prev->forks != 0)
				{
					if (philo->eat > 0)
						philo->time2 = get_time(philo->eat_time);
					else
						philo->time2 = get_time(start_time);
					if (philo->time2 >= philo->data->time_to_die)
					{
						pthread_mutex_lock(&philo->data->printf);
						time = get_time(start_time);
						ft_printf("%d %d died\n", time, philo->id);
						exit(0);
						pthread_mutex_unlock(&philo->data->printf);
					}
				}
					if (philo->next->forks == 0 && (philo->prev->sleep == 0 || philo->prev->forks == 1))
					{
						i = pthread_mutex_lock(&philo->next->fork);


							if (philo->eat > 0)
								philo->time2 = get_time(philo->eat_time);
							else
								philo->time2 = get_time(start_time);
							if (philo->time2 >= philo->data->time_to_die)
							{
								pthread_mutex_lock(&philo->data->printf);
								time = get_time(start_time);
								ft_printf("%d %d died\n", time, philo->id);
								exit(0);
								pthread_mutex_unlock(&philo->data->printf);
							}

							if (i == 0)
							{
								pthread_mutex_lock(&philo->data->printf);
								time = get_time(start_time);
								ft_printf("%d %d has taken a fork\n", time ,philo->id);
								pthread_mutex_unlock(&philo->data->printf);
							}
							return (1);
					}
					else if (philo->prev->forks == 0 && (philo->next->sleep == 0 || philo->prev->forks == 1))
					{
						i = pthread_mutex_lock(&philo->prev->fork);

								if (philo->eat > 0)
									philo->time2 = get_time(philo->eat_time);
								else
									philo->time2 = get_time(start_time);
								if (philo->time2 >= philo->data->time_to_die)
								{
									pthread_mutex_lock(&philo->data->printf);
									time = get_time(start_time);
									ft_printf("%d %d died\n", time, philo->id);
									exit(0);
									pthread_mutex_unlock(&philo->data->printf);

								}
								if (i == 0)
								{
									pthread_mutex_lock(&philo->data->printf);
									time = get_time(start_time);
									ft_printf("%d %d has taken a fork\n", time ,philo->id);
									pthread_mutex_unlock(&philo->data->printf);
								}
								return (2);
					}

			}
	return (0);
}

int	send_forks(philo_t *philo, int fork)
{
	if (fork == 1 || fork == 2)
	{
		pthread_mutex_unlock(&philo->fork);
		if (fork == 1)
			pthread_mutex_unlock(&philo->next->fork);
		else if (fork == 2)
			pthread_mutex_unlock(&philo->prev->fork);
	}
	philo->forks = 0;
	return (0);
}

int	eat(philo_t *philo, int fork, struct timeval start_time)
{
	int time;

		pthread_mutex_lock(&philo->data->printf);
		time = get_time(start_time);
		ft_printf("%d %d is eating\n", time, philo->id);
		pthread_mutex_unlock(&philo->data->printf);
		ft_usleep(philo->data->time_to_eat * 1000);
		send_forks(philo, fork);
		gettimeofday(&philo->eat_time, NULL);
		philo->eat += 1;
		return (1);
}

int	sleeping(philo_t *philo, int fork, struct timeval start_time)
{
	int time;

	philo->time2 = get_time(philo->eat_time);
	if (philo->time2 >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->printf);
		time = get_time(start_time);
		ft_printf("%d %d died\n", time, philo->id);
		exit(0);
		pthread_mutex_unlock(&philo->data->printf);
	}
	pthread_mutex_lock(&philo->data->printf);
	time = get_time(start_time);
	ft_printf("%d %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf);
	philo->sleep = 1;
	ft_usleep(philo->data->time_to_sleep * 1000);
	return (1);
}

void	think(philo_t *philo, struct timeval start_time)
{
	long time;

	time = get_time(start_time);
	philo->time2 = get_time(philo->eat_time);
	if (philo->time2 >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->printf);
		time = get_time(start_time);
		ft_printf("%d %d died\n", time, philo->id);
		exit(0);
		pthread_mutex_unlock(&philo->data->printf);

	}
	philo->sleep = 0;
	pthread_mutex_lock(&philo->data->printf);
	time = get_time(start_time);
	ft_printf("%d %d is thinking\n", time , philo->id);
	pthread_mutex_unlock(&philo->data->printf);
}