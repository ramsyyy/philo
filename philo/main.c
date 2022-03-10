/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/10 15:02:35 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	philo_t *filo;
	int	nb_each;

	nb_each = 0;
	filo = (philo_t *)philo;
	
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


	struct timeval current_time;
	long time;
	gettimeofday(&current_time, NULL);
	printf("%ld \n",current_time.tv_sec);
	usleep(2000 * 1000);
	time = get_time(current_time);
	printf("%ld \n", time);

	return (0);
}