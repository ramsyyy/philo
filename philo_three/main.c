/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/18 12:30:04 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int i, philo_t *philo, long int time)
{
	while (actual_time() - time < i)
	{
	}
}

int check_stop(t_data *data)
{
/*	int ret;

	pthread_mutex_lock(&filo->data->printf);

	pthread_mutex_unlock(&filo->data->printf);*/
	return(data->dead);
}

void	*routine(void *philo)
{
	philo_t *filo;
	int	nb_each;

	filo = (philo_t *)philo;
	if (filo->id % 2 == 0)
		ft_usleep(5, filo, actual_time());
	nb_each = 0;
	while (check_stop(filo->data) == 0)
	{
		take_forks(filo, filo->data->start_time);
		eat(filo, filo->data->start_time);
		sleeping(filo, filo->data->start_time);
		think(filo, filo->data->start_time);
	}
	//free((philo_t *) philo);
	return (philo);
}

/*
void	free_philo(philo_t *philo)
{
	while (philo && philo->next)
	{
		//pthread_detach(philo->philo);
		if (philo->next)
		{
			philo = philo->next;
			free(philo->prev);
		}
		if (!philo->next)
			free(philo);
	}

}*/



void	*mort(void *philo)
{
	philo_t *filo;
	long int time;
	int time2;

	filo = (philo_t *)philo;
	time = actual_time();
	while (check_stop(filo->data) == 0)
	{
		if (actual_time() - time >= filo->data->time_to_die)
		{
			time2 = actual_time() - filo->data->start;
			printf("%ld %d died\n", actual_time() - time, filo->id);
			//free((philo_t *) philo);
			filo->data->dead = 1;
			pthread_mutex_unlock(&filo->data->printf);
			return (filo);
		}
		usleep(800);
		pthread_mutex_lock(&filo->change_var);
		time = filo->eattime;
		pthread_mutex_unlock(&filo->change_var);
	}
	//free((philo_t *) philo);
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
		pthread_create(&philo->mortt, NULL, mort, philo);
		pthread_create(&philo->philo, NULL, routine , philo);
		philo = philo->next;
		i++;
	}
	while (--i > 0)
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
	}
	return (0);
}
