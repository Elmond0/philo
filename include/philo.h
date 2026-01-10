/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:44:40 by elmondo           #+#    #+#             */
/*   Updated: 2026/01/03 18:00:26 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

#define DEBUG_MODE 0

// PHILO STATES

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

// OPCODE for mutex

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

// STRUCTURE

typedef	struct				s_table t_table;
typedef pthread_mutex_t		t_mtx;

// fork

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;

}	t_fork;

// philo

typedef struct s_philo
{
	int			id;
	long		meal_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;

}	t_philo;

// table

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limits_meals;
	long		start_simulation;
	long		threads_running_nbr;
	bool		end_simulation;
	bool		all_thread_ready;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

// utils

long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
void	error_msg(const char *error);

// parsing

bool	parse_input(t_table *table, char **av);

// safe_function

int		safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
int		safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void	*data, t_opcode opcode);
void	*safe_malloc(size_t bytes);

// data_init

bool	data_init(t_table *table);

// dinner

void	*dinner_simulation(void *data);
void	dinner_start(t_table *table);

// getter_setter

void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

// synchro_utils

void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	de_synchronize_philos(t_philo *philo);
void	thinking(t_philo *philo, bool pre_simulation);

// write

void	write_status(t_philo_status status, t_philo *philo);

// monitoring

void	*monitor_dinner(void *data);