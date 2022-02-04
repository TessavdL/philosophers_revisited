/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 15:41:00 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/04 16:48:16 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	start_monitoring_threads(t_philosopher *philosophers,
	int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_create(&philosophers[i].thread.monitoring, NULL,
				&monitoring, &philosophers[i]))
		{
			return (1);
		}
		if (pthread_detach(philosophers[i].thread.monitoring))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	join_simulation_threads(t_philosopher *philosophers,
	int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_join(philosophers[i].thread.simulation, NULL))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	start_threads(t_philosopher *philosophers,
	int number_of_philosophers)
{
	int			i;
	long int	time;

	i = 0;
	time = get_time();
	while (i < number_of_philosophers)
	{
		philosophers[i].time_start = time;
		philosophers[i].time_of_last_meal = time;
		if (pthread_create(&philosophers[i].thread.simulation, NULL,
				&eat_sleep_think, &philosophers[i]))
		{
			return (1);
		}
		i++;
	}
	start_monitoring_threads(philosophers, number_of_philosophers);
	return (join_simulation_threads(philosophers, number_of_philosophers));
}

int	start_simulation(t_philosopher *philosophers, int number_of_philosophers)
{
	if (start_threads(philosophers, number_of_philosophers))
	{
		return (1);
	}
	return (0);
}
