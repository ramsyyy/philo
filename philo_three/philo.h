#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include "./ft_printf/ft_printf.h"

typedef struct s_data t_data;
struct s_data{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_to_each;
	pthread_mutex_t printf;
	pthread_mutex_t mutex;
	struct timeval start_time;
	long int start;
	int dead;
	int nb;
};

typedef struct philo_s philo_t;
struct philo_s{
	int id;
	int time2;
	pthread_t philo;
	pthread_t mortt;
	pthread_mutex_t change_var;
	int eat;
	int time_eat;
	int forks;
	int sleep;
	pthread_mutex_t fork;
	philo_t *next;
	philo_t *prev;
	struct timeval eat_time;
	long int eattime;
	t_data *data;

};

philo_t *philo_init(int argc, char **argv);
long int	get_time(struct timeval previous_time);
int	take_forks(philo_t *philo, struct timeval start_time);
int	eat(philo_t *philo, struct timeval start_time);
int	sleeping(philo_t *philo, struct timeval start_time);
int	think(philo_t *philo, struct timeval time);
void	ft_usleep(long int i, philo_t *philo, long int time);
long int actual_time();
int check_stop(t_data *data);

#endif