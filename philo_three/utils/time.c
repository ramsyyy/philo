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

long int actual_time()
{
    struct timeval tt;
    
    if (gettimeofday(&tt, NULL) == -1)
        return (-1);
    return ((tt.tv_sec * 1000) + (tt.tv_usec / 1000));
}

long int get_time(struct timeval previous_time)
{
    long int time;

    time = actual_time() - ((previous_time.tv_sec * 1000) + (previous_time.tv_usec / 1000));
    return(time);
}