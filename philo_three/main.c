/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/03/18 17:07:33 by raaga            ###   ########.fr       */
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
		ft_usleep(100, filo, actual_time());
//	nb_each = 0;
	while (check_stop(filo->data) == 0)
	{
		if (take_forks(filo, filo->data->start_time) == 1)
		{
			if (eat(filo, filo->data->start_time) == 1)
			{
				if (sleeping(filo, filo->data->start_time) == 1)
				{
					if (think(filo, filo->data->start_time) == 1)
					{
						if (check_stop(filo->data) == 1)
							return (philo);
					}
					else
						return (philo);
				}
				else
					return (philo);
			}
			else
				return (philo);
		}
		else
			return (philo);
	}
	return (philo);
}

void	destroy(philo_t *philo)
{
	int i;

	i = 1;
	pthread_mutex_destroy(&philo->data->printf);
	while (i <= philo->data->nb)
	{
		pthread_detach(philo->philo);
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		i++;
	}
}

void	*mort(void *philo)
{
	philo_t *filo;
	long int time;
	long int time2;
	int i;

	i = 1;
	filo = (philo_t *)philo;
	time = actual_time();
	while (check_stop(filo->data) == 0)
	{
		if (check_stop(filo->data) == 1)
				break ;
		if (actual_time() - time >= filo->data->time_to_die)
		{	
			pthread_mutex_lock(&filo->data->printf);
			if (check_stop(filo->data) == 1)
				break ;
			time2 = actual_time() - filo->data->start;
			ft_printf("%d %d died\n", time2, filo->id);
			pthread_mutex_lock(&filo->data->mutex);
			filo->data->dead = 1;
			pthread_mutex_unlock(&filo->data->mutex);
			pthread_mutex_unlock(&filo->data->printf);
			return (NULL);		
		}
		usleep(10);
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
	philo->data->start = actual_time();
	philo->data->dead = 0;
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
