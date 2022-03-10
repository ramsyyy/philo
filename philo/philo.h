#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_data t_data;
struct s_data{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_to_each;
	int philo_die;
};

typedef struct philo_s philo_t;
struct philo_s{
	int id;
	pthread_t philo;
	int eat;
	int time_eat;
	int forks;
	pthread_mutex_t fork;
	philo_t *next;
	philo_t *prev;
	t_data *data;
};

philo_t *philo_init(int argc, char **argv);
long get_time(struct timeval previous_time);

#endif