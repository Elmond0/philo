#include "../include/philo.h"

static void thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static	void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meal_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limits_meals > 0
		&& philo->meal_counter == philo->table->nbr_limits_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);

	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_all_threads(philo->table);

	while(!simulation_finished(philo->table))
	{
		if (philo->full)
			break;
		eat(philo);

		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);

		thinkingk(philo);
	}

	return (NULL);
}

void	dinner_start(t_table *table)
{
	int		i;

	i = -1;
	if (0 == table->nbr_limits_meals)
		return ;
	else if (1 == table->philo_nbr)
		;
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE);
	}
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_thread_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
}

