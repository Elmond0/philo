#include "../include/philo.h"

int main(int ac, char **av)
{
	t_table table;

	if (ac == 5 || ac == 6)
	{
		if (!parse_input(&table, av))
			return (1);
		if (!data_init(&table))
			return (1);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_msg("Wrong input:\nCorrect is ./philo 5 800 200 200 [5]");
		return (1);
	}
	return (0);
}