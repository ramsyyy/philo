/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:15:47 by raaga             #+#    #+#             */
/*   Updated: 2022/04/21 19:34:13 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *philo)
{
	t_philo	*filo;

	filo = (t_philo *)philo;
	if (filo->id % 2 == 0)
		ft_usleep(filo->data->time_to_eat / 2, filo, actual_time());
	pthread_create(&filo->mortt, NULL, mort, philo);
	while (check_stop(filo->data) == 0)
	{
		if (check_each(filo) >= filo->data->nb_to_each)
			break ;
		take_forks(filo);
	}
	pthread_join(filo->mortt, NULL);
	return (NULL);
}

int	stop_thread(t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&philo->data->printf);
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->dead == 0)
	{
		philo->data->dead = 1;
		time = (actual_time() - philo->data->start);
		ft_putnbr(time);
		write(1, " ", 1);
		ft_putnbr(philo->id);
		write(1, DEAD, ft_strlen(DEAD));
	}
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_unlock(&philo->data->printf);
	return (1);
}

void	*mort(void *philo)
{
	t_philo		*filo;
	long int	time;

	filo = (t_philo *)philo;
	time = actual_time();
	while (check_stop(filo->data) == 0)
	{
		if (check_each(filo) >= filo->data->nb_to_each)
			return (NULL);
		if (actual_time() - time >= filo->data->time_to_die)
		{	
			if (stop_thread(filo) == 1)
				return (NULL);
		}
		usleep(50);
		pthread_mutex_lock(&filo->change_var);
		time = filo->eattime;
		pthread_mutex_unlock(&filo->change_var);
		
	}
	printf("GGGGGGGGGGG\n");
	return (NULL);
}

void	ft_free(t_philo *philo)
{
	int		i;
	int		nb;
	t_philo	*tmp;

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

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	if (parser(argc, argv) == 0)
		return (0);
	i = 0;
	philo = philo_init(argc, argv);
	philo->data->start = actual_time();
	while (++i <= philo->data->nb)
	{
		philo->eattime = actual_time();
		pthread_create(&philo->philo, NULL, routine, philo);
		if (philo->next)
			philo = philo->next;
	}
	while (--i > 0)
	{
		pthread_join(philo->philo, NULL);
		if (philo->next)
			philo = philo->next;
	}
	pthread_mutex_destroy(&philo->data->printf);
	pthread_mutex_destroy(&philo->data->mutex);
	ft_free(philo);
	return (0);
}
