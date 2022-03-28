/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:55 by raaga             #+#    #+#             */
/*   Updated: 2022/03/28 17:27:45 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*philo_new(int nb, t_data *data)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
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
	pthread_mutex_init(&new->change_var, NULL);
	pthread_mutex_init(&new->fork, NULL);
	return (new);
}

t_data	*datainit(t_data *data, int argc, char **argv)
{
	data = malloc(sizeof(t_data));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (argc > 5)
		data->nb_to_each = ft_atoi(argv[5]);
	else
		data->nb_to_each = 2147483647;
	data->dead = 0;
	data->nb = ft_atoi(argv[1]);
	pthread_mutex_init(&data->printf, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	return (data);
}

t_philo	*philo_onetwo(t_philo *philo, t_data *data)
{
	t_philo	*tmp2;

	if (data->nb == 1)
		return (philo);
	if (data->nb == 2)
	{
		tmp2 = philo;
		philo = philo->next;
		philo = philo_new(data->nb, data);
		philo->prev = tmp2;
		tmp2->next = philo;
		tmp2->prev = philo;
		philo->next = tmp2;
		return (philo);
	}
}

int	initing(t_philo **philo, t_data *data, int i)
{
	t_philo		*tmp;
	t_philo		*tmp2;

	*philo = philo_new(i, data);
	if (i == 1)
	{
		(*philo)->prev = philo_new(data->nb, data);
		tmp2 = (*philo)->prev;
		(*philo)->prev->next = *philo;
	}
	else
	{
		(*philo)->prev = tmp;
		(*philo)->prev->next = *philo;
		if (i == data->nb - 1)
		{
			(*philo)->next = tmp2;
			(*philo)->next->prev = *philo;
			return (0);
		}
	}
	tmp = *philo;
	*philo = (*philo)->next;
	return (1);
}

t_philo	*philo_init(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philo;
	int			i;

	i = 0;
	data = datainit(data, argc, argv);
	if (argc == 6)
		data->nb_to_each = ft_atoi(argv[5]);
	if (data->nb == 1 || data->nb == 2)
		return (philo_onetwo(philo, data));
	while (++i <= data->nb)
	{
		if (initing(&philo, data, i) == 0)
			break ;
	}
	philo = philo->next->next;
	return (philo);
}
