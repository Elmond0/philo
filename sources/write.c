/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:15:33 by elmondo           #+#    #+#             */
/*   Updated: 2026/01/10 11:16:03 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (!simulation_finished(philo->table))
	{
		if (TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status)
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status)
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status)
			printf("%ld %d is thinking\n", elapsed, philo->id);
	}
	if (DIED == status)
		printf("%ld %d died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
