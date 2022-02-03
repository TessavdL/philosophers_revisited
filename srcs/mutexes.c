/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 14:34:58 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/03 22:21:52 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	initialize_individual_mutexes(t_philosopher *phil)
{
	printf("%p\n", &phil->mutexes.fork.left);
	if (pthread_mutex_init(&phil->mutexes.full, NULL))
	{
		return (1);
	}
	if (pthread_mutex_init(&phil->mutexes.time_of_last_meal, NULL))
	{
		pthread_mutex_destroy(&phil->mutexes.full);
		return (1);
	}
	return (0);
}

int	initialize_shared_mutexes(pthread_mutex_t **mutexes, int number_of_philosophers)
{
	int	i;

	*mutexes = malloc(sizeof(pthread_mutex_t) * (2 + number_of_philosophers));
	if (!(*mutexes))
	{
		return (1);
	}
	i = 0;
	while (i < (2 + number_of_philosophers))
	{
		if (pthread_mutex_init(&((*mutexes)[i]), NULL))
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&((*mutexes)[i]));
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
