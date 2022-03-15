/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/15 22:06:51 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int i)
{
	struct timeval usleep;

	gettimeofday(&usleep, NULL);
	while (i/1000 > get_time(usleep))
	{}
}

void	*routine(void *philo)
{
	philo_t *filo;
	struct timeval start_time;
	struct timeval current_time;
	int	nb_each;
	int fork;
	long time;

	filo = (philo_t *)philo;
	gettimeofday(&start_time, NULL);
	nb_each = 0;
	while (1)
	{
		time = get_time(start_time);
		fork = take_forks(filo, time, start_time);
		time = get_time(start_time);
		eat(filo, fork, start_time);
		time = get_time(start_time);
		sleeping(filo, fork, start_time);
		think(filo, start_time);
	}
}

void	*mort(void *philo)
{
	philo_t *filo;
	struct timeval start;

	int time;
	int time2;

	filo = (philo_t *)philo;
	gettimeofday(&start, NULL);
	while (1)
	{
			time += get_time(filo->eat_time);

		time2 = get_time(start);
		if (time >= filo->data->time_to_die)
		{
			pthread_mutex_lock(&filo->data->printf);
			ft_printf("%d %d died\n", time2, filo->id);
			exit(0);
			pthread_mutex_unlock(&filo->data->printf);
		}
		else
		{
			time = 0;
			filo = filo->next;
		}
	}
}


int main(int argc, char **argv)
{

	philo_t *philo;
	pthread_t mortt;
	int i;

	if (argc < 5 || argc > 6)
		return (0);
	i = atoi(argv[1]);
	if (i <= 0 || i > 200)
		return (0);
	philo = philo_init(argc, argv);
	while (i > 0)
	{
		pthread_create(&philo->philo, NULL, routine , philo);
		ft_usleep(500);
		i--;
		philo = philo->next;
	}
	pthread_create(&mortt, NULL, mort, philo);
	while (++i <= atoi(argv[1]))
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
	}
	pthread_join(mortt, NULL);
	return (0);
}
