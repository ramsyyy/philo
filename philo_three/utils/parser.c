/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramsy <ramsy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:41:10 by ramsy             #+#    #+#             */
/*   Updated: 2022/03/25 20:50:10 by ramsy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_nb(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int parser(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
		return (0);
    if (atoi(argv[1]) <= 0 || atoi(argv[1]) > 200)
		return (0);
    if (atoi(argv[3]) < 60 || atoi(argv[4]) < 60)
        return (0);
    if (check_nb(argc, argv) == 0)
        return (0);
    return (1);    
}