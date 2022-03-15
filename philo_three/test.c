/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:33:04 by raaga             #+#    #+#             */
/*   Updated: 2022/03/10 14:15:10 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
	struct timeval current_time;


	gettimeofday(&current_time, NULL);
	printf("%ld  \n", current_time.tv_sec);
	//usleep(1000 * (1000));


	gettimeofday(&current_time, NULL);
	printf("%ld  \n", current_time.tv_sec);
	return (0);
}