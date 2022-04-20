/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:00:31 by raaga             #+#    #+#             */
/*   Updated: 2022/03/23 14:01:30 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long int	actual_time(void)
{
	struct timeval	tt;

	if (gettimeofday(&tt, NULL) == -1)
		return (-1);
	return ((tt.tv_sec * 1000) + (tt.tv_usec / 1000));
}

long int	get_time(struct timeval previous_time)
{
	long int	time;

	time = actual_time() - ((previous_time.tv_sec * 1000)
			+ (previous_time.tv_usec / 1000));
	return (time);
}

void	ft_usleep(long int i, t_philo *philo, long int time)
{
	while (actual_time() - time < i)
	{
		if (check_stop(philo->data) == 1)
			return ;
		usleep(1);
	}
}

int	check_stop(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->mutex);
	ret = data->dead;
	pthread_mutex_unlock(&data->mutex);
	return (ret);
}

int	check_each(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->change_var);
	ret = philo->nb_each;
	pthread_mutex_unlock(&philo->change_var);
	return (ret);
}
