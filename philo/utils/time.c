/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:00:31 by raaga             #+#    #+#             */
/*   Updated: 2022/03/10 19:53:39 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long get_time(struct timeval previous_time)
{
    struct timeval current_time;
    long time;


    gettimeofday(&current_time, NULL);
    time = (current_time.tv_sec - previous_time.tv_sec) * 1000;
    //time += (current_time.tv_usec / 1000) - (previous_time.tv_usec / 1000);
    return (time);
}