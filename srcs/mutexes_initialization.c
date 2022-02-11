/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes_initialization.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 14:34:58 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/11 17:23:00 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	assign_shared_mutexes(t_philosopher **philosophers, 
	pthread_mutex_t **shared_mutexes,
	const int number_of_philosophers)
{
	int i;

	i = 0;
	while (i < number_of_philosophers)
	{
		((*philosophers)[i]).mutexes.dead = &((*shared_mutexes)[DEAD]);
		((*philosophers)[i]).mutexes.print = &((*shared_mutexes)[PRINT]);
		((*philosophers)[i]).mutexes.fork.left = &((*shared_mutexes)[i + 2]);
		if (i == number_of_philosophers - 1)
		{
			((*philosophers)[i]).mutexes.fork.right = &((*shared_mutexes)[2]);
		}
		else
		{
			((*philosophers)[i]).mutexes.fork.right = &((*shared_mutexes)[i + 3]);
		}
		i++;
	}
}

int	initialize_individual_mutexes(t_philosopher **philosophers,
	const int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&((*philosophers)[i]).mutexes.full, NULL))
		{
			destroy_part_individual_mutexes(*philosophers, i);
			return (1);
		}
		if (pthread_mutex_init(&((*philosophers)[i]).mutexes.time_of_last_meal,
			NULL))
		{
			pthread_mutex_destroy(&((*philosophers)[i]).mutexes.full);
			destroy_part_individual_mutexes(*philosophers, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	initialize_shared_mutexes(pthread_mutex_t **mutexes,
	const int number_of_philosophers)
{
	const int	total_number_of_mutexes = 2 + number_of_philosophers;
	int			i;

	*mutexes = ft_calloc(sizeof(pthread_mutex_t), total_number_of_mutexes);
	if (!(*mutexes))
	{
		return (1);
	}
	i = 0;
	while (i < total_number_of_mutexes)
	{
		if (pthread_mutex_init(&((*mutexes)[i]), NULL))
		{
			destroy_part_shared_mutexes(mutexes, i);
			return (1);
		}
		i++;
	}
	return (0);
}
