#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct philo_s philo_t;
struct philo_s{
	int id;
	pthread_t philo;
	int eat;
	int time_die;
	int time_eat;
	int time_sleep;
	int forks;
	pthread_mutex_t fork;
	philo_t *next;
	philo_t *prev;
};

typedef struct s_data t_data;
struct s_data{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_to_each;
	int philo_die;
};

philo_t *philo_init(char **argv);

#endif