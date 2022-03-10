/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/09 19:38:19 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo, void  *data)
{
	philo_t *filo;

	filo = (philo_t *)philo;
	printf("philo %d\n", filo->id);
}

int main(int argc, char **argv)
{
	t_data  *data;
	philo_t *philo;
	int i;

	i = atoi(argv[1]);
	if (i <= 0 || i > 200)
		return (0);
	if (argc < 5 || argc > 6)
		return (0);

	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if(argc == 6)
		data->nb_to_each = atoi(argv[5]);

		
	philo = philo_init(argv);
	while (i > 0)
	{
		pthread_create(&philo->philo, NULL, &routine , philo, data);
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