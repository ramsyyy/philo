/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/18 21:01:29 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int i, philo_t *philo, long int time)
{
	while (actual_time() - time < i)
	{
		if (check_stop(philo->data) == 1)
			break ;
		usleep(40);
	}
}

int check_stop(t_data *data)
{
	int ret;
	
	pthread_mutex_lock(&data->mutex);
	ret = data->dead;
	pthread_mutex_unlock(&data->mutex);
	return(ret);
}

void	*routine(void *philo)
{
	philo_t *filo;
	int	nb_each;

	filo = (philo_t *)philo;
	if (filo->id % 2 == 0)
		ft_usleep(50, filo, actual_time());
	while (check_stop(filo->data) == 0)
		take_forks(filo, filo->data->start_time);
	return (filo);
}


void	*mort(void *philo)
{
	philo_t *filo;
	long int time;
	int i;

	i = 1;
	filo = (philo_t *)philo;
	time = actual_time();
	while (check_stop(filo->data) == 0)
	{
		if (actual_time() - time >= filo->data->time_to_die)
		{	
			msg(philo, DEAD);
			pthread_mutex_lock(&filo->data->mutex);
			filo->data->dead = 1;
			pthread_mutex_unlock(&filo->data->mutex);
			return (NULL);		
		}
		pthread_mutex_lock(&filo->change_var);
		time = filo->eattime;
		pthread_mutex_unlock(&filo->change_var);
	}
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
	philo->data->dead = 0;
	philo->data->start = actual_time();
	while (i <= nb)
	{
		pthread_create(&philo->mortt, NULL, mort, philo);
		pthread_create(&philo->philo, NULL, routine , philo);
		philo = philo->next;
		i++;
	}
	i = 1;
	while (i <= nb)
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
		i++;
	}
}
