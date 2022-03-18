/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramsy <ramsy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/18 10:26:24 by ramsy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int i, philo_t *philo)
{
	long int time;

	//gettimeofday(&usleep, NULL);
	time = actual_time();
	while (actual_time() - time < i)
	{
	}
}

void	*routine(void *philo)
{
	philo_t *filo;
	int	nb_each;
	long time;

	filo = (philo_t *)philo;
	if (filo->id % 2 == 0)
		ft_usleep(100, filo);
	nb_each = 0;
	while (1)
	{
		pthread_mutex_lock(&filo->data->mutex);			
			if (filo->data->dead == 1)
				break ;
		pthread_mutex_unlock(&filo->data->mutex);
		take_forks(filo, filo->data->start_time);
		eat(filo, filo->data->start_time);
		sleeping(filo, filo->data->start_time);
		think(filo, filo->data->start_time);
	}
	free((philo_t *) philo);
	return (philo);
}

void	free_philo(philo_t *philo)
{
	while (philo && philo->next)
	{
		//pthread_detach(philo->philo);
		/*if (philo->next)
		{
			philo = philo->next;
			free(philo->prev);
		}
		if (!philo->next)*/
			free(philo);
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
		time = filo->eattime;
		pthread_mutex_lock(&filo->data->mutex);			
			if (filo->data->dead == 1)
				break ;
		pthread_mutex_unlock(&filo->data->mutex);
		if (actual_time() - time >= filo->data->time_to_die)
		{	
			pthread_mutex_lock(&filo->data->printf);
				pthread_mutex_lock(&filo->data->mutex);			
				if (filo->data->dead == 1)
					break ;
				else
					filo->data->dead = 1;
			pthread_mutex_unlock(&filo->data->mutex);
			time2 = actual_time() - filo->data->start;
			printf("%d %d died\n", time2, filo->id);
			free((philo_t *) philo);
			pthread_mutex_unlock(&filo->data->printf);
			return (filo);
		}
	}
	free((philo_t *) philo);
	pthread_mutex_unlock(&filo->data->mutex);
	pthread_mutex_unlock(&filo->data->printf);
	return (filo);
}


int main(int argc, char **argv)
{

	philo_t *philo;
	
	int i;
	int nb;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	if (i <= 0 || i > 200)
		return (0);
	nb = atoi(argv[1]);
	philo = philo_init(argc, argv);
	philo->data->start = actual_time();
	philo->data->dead = 0;
	while (i <= nb)
	{
		//
		pthread_create(&philo->philo, NULL, routine , philo);
		
		philo = philo->next;
		i++;
	}
	i = 1;
	while (i <= nb)
	{
		pthread_create(&philo->mortt, NULL, mort, philo);
		philo = philo->next;
		pthread_join(philo->mortt, NULL);
		i++;
	}
	i = 1;
	while (i <= nb)
	{
		pthread_join(philo->philo, NULL);
		//pthread_join(philo->mortt, NULL);
		philo = philo->next;
		i++;
	}
	return (0);
}
