#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include "./ft_printf/ft_printf.h"

# define EAT " is eating\n"
# define FORK " has taken a fork\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define DEAD " died\n"
# define DROP " dropped forks\n"

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
	pthread_t philo;
	pthread_t mortt;
	int eat;
	int time_eat;
	int forks;
	int sleep;
	pthread_mutex_t fork;
	pthread_mutex_t change_var;
	philo_t *next;
	philo_t *prev;
	long int eattime;
	t_data *data;
};

philo_t *philo_init(int argc, char **argv);
void	*mort(void *philo);
long int	get_time(struct timeval previous_time);
void	take_forks(philo_t *philo, struct timeval start_time);
void	sleeping(philo_t *philo);
void	ft_usleep(long int i, philo_t *philo, long int time);
long int actual_time();
int check_stop(t_data *data);
void msg(philo_t *philo, char *msg);
void	ft_destroy(philo_t *philo);

#endif