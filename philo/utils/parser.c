/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:41:10 by ramsy             #+#    #+#             */
/*   Updated: 2022/04/20 15:46:21 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_nb(char **argv)
{
	int	i;
	int	j;

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

int	parser(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (0);
	if (ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60 || ft_atoi(argv[2]) < 60)
		return (0);
	if (check_nb(argv) == 0)
		return (0);
	return (1);
}
