/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:22:15 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/03 22:17:15 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	free_and_return_error(t_philosopher *philosophers, t_bool *dead)
{
	free(dead);
	free(philosophers);
	return (1);
}

static int	destroy_individual_mutexes(t_philosopher *philosophers, int i)
{
	i--;
	while (i >= 0)
	{   
		pthread_mutex_destroy(&philosophers[i].mutexes.full);
		pthread_mutex_destroy(&philosophers[i].mutexes.time_of_last_meal);
		i--;
	}
	return (1);
}

static int	initialize_philosophers(t_philosopher *philosophers, t_bool *dead,
	t_input data)
{
	pthread_mutex_t *shared_mutexes;
	int	i;

	if (initialize_shared_mutexes(&shared_mutexes, data.number_of_philosophers))
	{
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		if (initialize_individual_mutexes(&philosophers[i]))
		{
			free(shared_mutexes);
			return (destroy_individual_mutexes(philosophers, i));
		}
		philosophers[i].mutexes.fork.left = shared_mutexes[i + 2];
		if (i == data.number_of_philosophers - 1)
		{
			philosophers[i].mutexes.fork.right = shared_mutexes[0];
		}
		else
		{
			philosophers[i].mutexes.fork.right = shared_mutexes[i + 3];
		}
		philosophers[i].data = data;
		philosophers[i].dead = dead;
		philosophers[i].full = FALSE;
		philosophers[i].id = i + 1;
		philosophers[i].mutexes.dead = shared_mutexes[DEAD];
		philosophers[i].mutexes.print = shared_mutexes[PRINT];
		i++;
	}
	return (0);
}

int	setup_simulation(t_input data)
{
	t_bool			*dead;
	t_philosopher	*philosophers;

	dead = NULL;

	philosophers = malloc(sizeof(t_philosopher) * data.number_of_philosophers);
	if (!philosophers)
	{
		return (free_and_return_error(philosophers, dead));
	}
	dead = malloc(sizeof(t_bool));
	if (!dead)
	{
		return (free_and_return_error(philosophers, dead));
	}
	*dead = FALSE;
	if (initialize_philosophers(philosophers, dead, data))
	{
		return (free_and_return_error(philosophers, dead));
	}
	printf("%d %d %d %d %d\n", philosophers[0].data.number_of_philosophers,
	philosophers[0].data.time_until_death, philosophers[0].data.time_to_eat,
	philosophers[0].data.time_to_sleep, philosophers[0].data.number_of_meals);
	return (start_simulation(philosophers, data.number_of_philosophers));
}
