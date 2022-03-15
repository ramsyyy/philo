/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramsy <ramsy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/14 19:56:19 by ramsy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		//printf ("gfds %d\n", fork);
		if (fork == 1)
		{
			time = get_time(start_time);
			eat(filo, fork, time);
			time = get_time(start_time);
			sleeping(filo, fork, time);
			think(filo, start_time);
		}
	}
}

int main(int argc, char **argv)
{

	philo_t *philo;
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
		usleep(500);
		i--;
		philo = philo->next;
	}
	while (++i <= atoi(argv[1]))
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
	}
	return (0);
}
