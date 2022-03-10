/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:33:04 by raaga             #+#    #+#             */
/*   Updated: 2022/03/09 17:14:57 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void	*routine()
{
	printf("test\n");
	usleep(10000 * 1000);
	printf("fin\n");
}

philo_t	*ft_philo_new(int nb_philo)
{
	philo_t philo;
	
	philo = malloc(sizeof(philo_t));
	philo->id = nb_philo;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

int main(int argc, char **argv)
{
	struct timeval current_time;
	pthread_t t1[atoi(argv[1])];
	philo_t *philo;
	int	nb_philo;
	int	i;
	
	i = 1;
	nb_philo = atoi(argv[1]);
	
	while (i < nb_philo)
	{
		philo = ft_philo_new(&philo, i);	
	}
	gettimeofday(&current_time, NULL);
	printf("%ld  \n", current_time.tv_sec);
	//usleep(1000 * (1000));
	
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	gettimeofday(&current_time, NULL);
	printf("%ld  \n", current_time.tv_sec);
	return (0);
}