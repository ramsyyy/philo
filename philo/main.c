/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/10 20:49:27 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	philo_t *filo;
	struct timeval *start_time;
	struct timeval current_time;
	int	nb_each;
	int fork;
	long time;

	gettimeofday(start_time, NULL);
	filo->eat_time = start_time;
	//gettimeofday(&filo->eat_time, NULL);
	/*time = get_time(start_time);
	nb_each = 0;
	filo = (philo_t *)philo;
	fork = take_forks(filo, time, start_time);
	if (fork == 1)
		time = get_time(start_time);
	eat(filo, fork, time);
	time = get_time(start_time);
	sleeping(filo, fork, time);
	think(filo, start_time);*/
	return (philo);
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
