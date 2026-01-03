#include "../include/philo.h"

static inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static const char *valid_input(const char *str, bool *error)
{
	int len;
	const char *number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
	{
		error_msg("Feed me only positive values");
		*error = true;
		return (NULL);
	}
	if (!is_digit(*str))
	{
		error_msg("The input is not a digit");
		*error = true;
		return (NULL);
	}
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
	{
		error_msg("The value is too big");
		*error = true;
		return (NULL);
	}
	return (number);
}

static long ft_atol(const char *str, bool *error)
{
	long num;

	num = 0;
	str = valid_input(str, error);
	if (*error)
		return (-1);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
	{
		error_msg("The value is too big");
		*error = true;
		return (-1);
	}
	return (num);
}

bool parse_input(t_table *table, char **av)
{
	bool error;

	error = false;
	table->philo_nbr = ft_atol(av[1], &error);
	if (error || table->philo_nbr <= 0)
	{
		if (!error)
			error_msg("Invalid number of philosophers");
		return (false);
	}
	table->time_to_die = ft_atol(av[2], &error) * 1e3;
	if (error)
		return (false);
	table->time_to_eat = ft_atol(av[3], &error) * 1e3;
	if (error)
		return (false);
	table->time_to_sleep = ft_atol(av[4], &error) * 1e3;
	if (error)
		return (false);
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
	{
		error_msg("Use more than 60ms");
		return (false);
	}
	if (av[5])
		table->nbr_limits_meals = ft_atol(av[5], &error);
	else
		table->nbr_limits_meals = -1;
	if (error)
		return (false);
	return (true);
}
