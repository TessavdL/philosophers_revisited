/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:22:15 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/11 17:09:58 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int free_and_return(t_bool *dead, t_philosopher *philosophers,
	pthread_mutex_t *shared_mutexes,
	const int ret)
{
	free(dead);
	free(philosophers);
	destroy_all_shared_mutexes(shared_mutexes,
		philosophers[0].data.number_of_philosophers);
	free(shared_mutexes);
	return (ret);
}

static int	initialize_philosophers(t_bool *dead, t_philosopher **philosophers,
	pthread_mutex_t **shared_mutexes, t_input data)
{
	int	i;

	*philosophers = ft_calloc(sizeof(t_philosopher), data.number_of_philosophers);
	if (!(*philosophers))
	{
		return (1);
	}
	if (initialize_individual_mutexes(philosophers,
		data.number_of_philosophers))
	{
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		((*philosophers)[i]).data = data;
		((*philosophers)[i]).dead = dead;
		((*philosophers)[i]).full = FALSE;
		((*philosophers)[i]).id = i + 1;
		i++;
	}
	assign_shared_mutexes(philosophers, shared_mutexes,
		data.number_of_philosophers);
	return (0);
}

int	setup_simulation(t_input data, const int number_of_philosophers)
{
	int				ret;
	pthread_mutex_t	*shared_mutexes;
	t_bool			*dead;
	t_philosopher	*philosophers;

	ret = 1;
	if (initialize_shared_mutexes(&shared_mutexes, number_of_philosophers))
	{
		return (ret);
	}
	philosophers = NULL;
	dead = ft_calloc(sizeof(t_bool), 1);
	if (!dead)
	{
		return (free_and_return(dead, philosophers, shared_mutexes, ret));
	}
	if (initialize_philosophers(dead, &philosophers, &shared_mutexes, data))
	{
		return (free_and_return(dead, philosophers, shared_mutexes, ret));
	}
	if (!start_simulation(philosophers, number_of_philosophers))
	{
		ret = 0;
	}
	destroy_all_individual_mutexes(philosophers, number_of_philosophers);
	return (free_and_return(dead, philosophers, shared_mutexes, ret));
}
