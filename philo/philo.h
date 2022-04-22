/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:32:57 by raaga             #+#    #+#             */
/*   Updated: 2022/04/20 16:25:32 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

# define EAT " is eating\n"
# define FORK " has taken a fork\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define DEAD " died\n"
# define DROP " dropped forks\n"

typedef struct s_data	t_data;
struct s_data{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	printf;
	pthread_mutex_t	mutex;
	pthread_mutex_t	each;
	struct timeval	start_time;
	int				philo_eat;
	int				nb_to_each;
	long int		start;
	int				dead;
	int				nb;
};

typedef struct s_philo	t_philo;
struct s_philo{
	int				id;
	pthread_t		philo;
	pthread_t		mortt;
	int				eat;
	int				time_eat;
	int				forks;
	int				sleep;
	int				nb_each;
	pthread_mutex_t	fork;
	pthread_mutex_t	change_var;
	t_philo			*next;
	t_philo			*prev;
	long int		eattime;
	t_data			*data;
};

t_philo		*philo_init(int argc, char **argv);
void		*mort(void *philo);
long int	get_time(struct timeval previous_time);
void		take_forks(t_philo *philo);
void		sleeping(t_philo *philo);
void		ft_usleep(long int i, t_philo *philo, long int time);
long int	actual_time(void);
int			check_stop(t_data *data);
void		msg(t_philo *philo, char *msg);
void		ft_destroy(t_philo *philo);
int			parser(int argc, char **argv);
int			check_each(t_philo *philo);
int			ft_atoi(const char *str);

void		ft_putnbr(int n);
size_t		ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);

#endif