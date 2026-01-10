/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:36:34 by elmondo           #+#    #+#             */
/*   Updated: 2026/01/10 11:02:32 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static const char	*valid_input(const char *str, bool *error)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (*error = true, error_msg("Only positive values"), NULL);
	if (!is_digit(*str))
		return (*error = true, error_msg("Input is not a digit"), NULL);
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		return (*error = true, error_msg("Value is too big"), NULL);
	return (number);
}

static long	ft_atol(const char *str, bool *error)
{
	long	num;

	num = 0;
	str = valid_input(str, error);
	if (*error)
		return (-1);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		return (*error = true, error_msg("Value is too big"), -1);
	return (num);
}

bool	parse_input(t_table *table, char **av)
{
	bool	error;

	error = false;
	table->philo_nbr = ft_atol(av[1], &error);
	if (error || table->philo_nbr <= 0)
		return (error_msg("Invalid number of philosophers"), false);
	table->time_to_die = ft_atol(av[2], &error) * 1e3;
	if (error)
		return (false);
	table->time_to_eat = ft_atol(av[3], &error) * 1e3;
	if (error)
		return (false);
	table->time_to_sleep = ft_atol(av[4], &error) * 1e3;
	if (error || table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		return (error_msg("Use more than 60ms"), false);
	if (av[5])
		table->nbr_limits_meals = ft_atol(av[5], &error);
	else
		table->nbr_limits_meals = -1;
	return (!error);
}
