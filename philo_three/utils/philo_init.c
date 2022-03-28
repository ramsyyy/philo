/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:55 by raaga             #+#    #+#             */
/*   Updated: 2022/03/23 18:39:44 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

philo_t *philo_new(int nb, t_data *data)
{
	philo_t	*new;

	new = malloc(sizeof(philo_t));
	if (!new)
		return (NULL);
	new->id = nb;
	new->time_eat = 0;
	new->forks = 0;
	new->sleep = 0;
	new->next = NULL;
	new->prev = NULL;
	new->data = data;
	new->nb_each = 0;
	new->data->start_time = (struct timeval){ 0 };
	pthread_mutex_init(&new->change_var, NULL);
	pthread_mutex_init(&new->fork, NULL);
	return (new);
}

philo_t *philo_init(int argc, char **argv)
{
	pthread_t t1[atoi(argv[1])];
	t_data  *data;
	philo_t *philo;
	philo_t *tmp;
	philo_t *tmp2;
	int	nb_philo;
	int	i;

	i = 1;
	nb_philo = atoi(argv[1]);
	data = malloc(sizeof(t_data));
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->nb_to_each = atoi(argv[5]);
	data->dead = 0;
	data->nb = atoi(argv[1]);
	pthread_mutex_init(&data->printf, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->each, NULL);
	if(argc == 6)
		data->nb_to_each = atoi(argv[5]);
	while (i <= nb_philo)
	{
		philo = philo_new(i, data);
		if (nb_philo == 1)
			return (philo);
		if (nb_philo == 2)
		{
			tmp2 = philo;
			philo = philo->next;
			philo = philo_new(nb_philo, data);
			philo->prev = tmp2;
			tmp2->next = philo;
			tmp2->prev = philo;
			philo->next = tmp2;
			return (philo);
		}
		if (i == 1)
		{
			philo->prev = philo_new(nb_philo, data);
			tmp2 = philo->prev;
			philo->prev->next = philo;
		}
		else
		{
			philo->prev = tmp;
			philo->prev->next = philo;
			if (i == nb_philo - 1)
			{
				philo->next = tmp2;
				philo->next->prev = philo;
				break ;
			}
		}
		tmp = philo;
		philo = philo->next;
		i++;
	}
	philo = philo->next->next;
	return (philo);
}

