/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:00:31 by raaga             #+#    #+#             */
/*   Updated: 2022/03/15 18:09:10 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int get_time(struct timeval previous_time)
{
    struct timeval current_time;
    //long time;


    gettimeofday(&current_time, NULL);
    return((current_time.tv_sec - previous_time.tv_sec) * 1000 + ((current_time.tv_usec / 1000) - (previous_time.tv_usec / 1000)));
}