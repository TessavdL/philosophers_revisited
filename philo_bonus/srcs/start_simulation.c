/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 15:41:00 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/28 17:34:32 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	wait_for_simulation_to_terminate(t_philosopher *philosophers,
	const int number_of_philosophers)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < number_of_philosophers)
	{
		waitpid(philosophers[i].pid, &wstatus, 0);
		i++;
	}
}

void	start_simulation(t_philosopher *philosophers,
	const int number_of_philosophers)
{
	int			i;
	long int	time;

	i = 0;
	time = get_time_ms();
	while (i < number_of_philosophers)
	{
		philosophers[i].time_start = time;
		philosophers[i].time_of_last_meal = time;
		philosophers[i].pid = fork();
		if (philosophers[i].pid == -1)
			exit(ERROR_FAILED_TO_FORK_THE_PROCESS);
		else if (philosophers[i].pid == CHILD)
			eat_sleep_think_repeat(&philosophers[i]);
		i++;
	}
	wait_for_simulation_to_terminate(philosophers, number_of_philosophers);
}
