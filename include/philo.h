#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

// STRUCTURE

typedef struct s_table	t_table;
typedef	pthread_mutex_t	t_mtx;

// fork

typedef	struct s_fork
{
	t_mtx	fork;
	int		fork_id;

}			t_fork;

// philo

typedef struct s_philo
{
	int			id;
	long		meal_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;

}				t_philo;

// table

typedef	struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_spleep;
	long	nbr_limits_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
}			t_table;

// utils

void error_exit(const char *error);