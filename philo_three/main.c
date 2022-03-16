/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/16 21:05:44 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int i)
{
	long int time;

	//gettimeofday(&usleep, NULL);
	time = actual_time();
	while (actual_time() - time < i)
	{}
}

void	*routine(void *philo)
{
	philo_t *filo;
	int	nb_each;
	long time;

	filo = (philo_t *)philo;
	if (filo->id % 2 == 0)
		usleep(100);
	nb_each = 0;
	while (1)
	{
		take_forks(filo, filo->data->start_time);
		eat(filo, filo->data->start_time);
		sleeping(filo, filo->data->start_time);
		think(filo, filo->data->start_time);
	}
}

void	*mort(void *philo)
{
	philo_t *filo;
	long int time;
	int time2;

	filo = (philo_t *)philo;
	time = actual_time();
	while (1)
	{
		if (actual_time() - time >= filo->data->time_to_die)
		{
			pthread_mutex_lock(&filo->data->printf);
			time2 = actual_time() - filo->data->start;
			printf("%d %d died\n", time2, filo->id);
			exit(0);
			pthread_mutex_unlock(&filo->data->printf);
		}
		else
		{
			if (filo->eattime > 0)
				time = filo->eattime;
		}
	}
}


int main(int argc, char **argv)
{

	philo_t *philo;
	pthread_t mortt;
	int i;
	int nb;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	if (i <= 0 || i > 200)
		return (0);

	/*printf("QWE %ld\n", actual_time());
	ft_usleep(1000);
	//usleep(1000000);
	printf("QWE %ld\n", actual_time());*/

	nb = atoi(argv[1]);
	philo = philo_init(argc, argv);
	//gettimeofday(&philo->data->start_time, NULL);
	philo->data->start = actual_time();
	while (i <= nb)
	{
		pthread_create(&philo->philo, NULL, routine , philo);
		pthread_create(&mortt, NULL, mort, philo);
		philo = philo->next;
		i++;
	}
	i--;
	while (i > 0)
	{

		pthread_join(philo->philo, NULL);
		pthread_join(mortt, NULL);
		philo = philo->next;
		i--;
	}

	return (0);
}
