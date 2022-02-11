/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes_destruction.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 12:21:15 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/02/11 16:29:46 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	destroy_all_shared_mutexes(pthread_mutex_t *mutexes,
	const int number_of_philosophers)
{
	const int	total_number_of_mutexes = 2 + number_of_philosophers;
	int	i;

	i = 0;
	while (i < total_number_of_mutexes)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

void	destroy_part_shared_mutexes(pthread_mutex_t **mutexes, int i)
{
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(&((*mutexes)[i]));
		i--;
	}
}

void	destroy_all_individual_mutexes(t_philosopher *philosophers,
	const int number_of_philosophers)
{
	int	i;
	
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&philosophers[i].mutexes.full);
		pthread_mutex_destroy(&philosophers[i].mutexes.time_of_last_meal);
		i++;
	}
}

void	destroy_part_individual_mutexes(t_philosopher *philosophers, int i)
{
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(&philosophers[i].mutexes.full);
		pthread_mutex_destroy(&philosophers[i].mutexes.time_of_last_meal);
		i--;
	}
}
