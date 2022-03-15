/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/15 18:07:00 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int i)
{
	int time;
	struct timeval usleep;

	time = 0;
	gettimeofday(&usleep, NULL);
	while (i/1000 > time)
	{
		time = get_time(usleep);
	}
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
		//printf ("gfds %d\n", fork);
		if (fork == 1 || fork == 2)
		{
			time = get_time(start_time);
			eat(filo, fork, start_time);
			time = get_time(start_time);
			sleeping(filo, fork, start_time);
			think(filo, start_time);
		}
	}
}

int main(int argc, char **argv)
{

	philo_t *philo;
	int i;
	//struct timeval test;

	/*gettimeofday(&test, NULL);
	printf("%ld  \n", test.tv_sec);
	ft_usleep(1000 * 1000);


	gettimeofday(&test, NULL);
	printf("%ld  \n", test.tv_sec);*/
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
	while (++i <= atoi(argv[1]))
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
	}
	return (0);
}
