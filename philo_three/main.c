/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/23 18:43:29 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int i, philo_t *philo, long int time)
{
	while (actual_time() - time < i)
	{
		if (check_stop(philo->data) == 1)
			return ;
		usleep(25);
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
		ft_usleep(filo->data->time_to_eat, filo, actual_time());
	pthread_create(&filo->mortt, NULL, mort, philo);
	while (check_stop(filo->data) == 0)
		take_forks(filo, filo->data->start_time);
	pthread_join(filo->mortt, NULL);
	return (NULL);
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
			pthread_mutex_lock(&filo->data->printf);
			pthread_mutex_lock(&filo->data->mutex);
			if (filo->data->dead == 0)
			{
				filo->data->dead = 1;
				time = (actual_time() - filo->data->start);
				ft_putnbr(time);
				write(1, " ", 1);
				ft_putnbr(filo->id);
				ft_putstr(DEAD);
				
			}
			pthread_mutex_unlock(&filo->data->mutex);
			pthread_mutex_unlock(&filo->data->printf);
			return (NULL);		
		}
		usleep(100);
		pthread_mutex_lock(&filo->change_var);
		time = filo->eattime;
		pthread_mutex_unlock(&filo->change_var);
	}
	return (NULL);
}

void	ft_free(philo_t *philo)
{
	int i;
	int nb;
	philo_t *tmp;

	i = 1;
	nb = philo->data->nb;
	free(philo->data);
	while (i <= nb)
	{
		philo->data = NULL;
		tmp = philo;
		if (philo->next)
			philo = philo->next;
		free(tmp);
		i++;
	}
}

void	ft_destroy(philo_t *philo)
{
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&philo->change_var);
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
		philo->eattime = actual_time();
		pthread_create(&philo->philo, NULL, routine , philo);
		if(philo->next)
			philo = philo->next;
		i++;
	}
	i = 1;
	while (i <= nb)
	{
		pthread_join(philo->philo, NULL);
		if (philo->next)
			philo = philo->next;
		i++;
	}
	pthread_mutex_destroy(&philo->data->printf);
	pthread_mutex_destroy(&philo->data->mutex);
	ft_free(philo);
	return (0);
}
