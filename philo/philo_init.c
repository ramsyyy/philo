/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:55 by raaga             #+#    #+#             */
/*   Updated: 2022/03/09 19:37:10 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

philo_t *philo_new(int nb)
{
	philo_t	*new;

	new = malloc(sizeof(philo_t));
	if (!new)
		return (NULL);
	new->id = nb;
	new->time_die = 0;
	new->time_eat = 0;
	new->time_sleep = 0;
	new->forks = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

philo_t *philo_init(char **argv)
{
	pthread_t t1[atoi(argv[1])];
	philo_t *philo;
	philo_t *tmp;
	philo_t *tmp2;
	int	nb_philo;
	int	i;
	
	i = 1;
	nb_philo = atoi(argv[1]);
	
	while (i <= nb_philo)
	{
		philo = philo_new(i);
		if (i == 1)
		{
			philo->prev = philo_new(nb_philo);
			tmp2 = philo->prev;
			philo->prev->next = philo;
			if (nb_philo == 2)
			{
				philo->prev->prev = philo;
				philo->next = philo->prev;
			}
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

