/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_mutexes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:51:42 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/04 12:04:32 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_message(pthread_mutex_t *print, int id, unsigned long time,
	char *message)
{
	pthread_mutex_lock(print);
	printf("[%10lu] Philosopher %d %s\n", time, id, message);
	pthread_mutex_unlock(print);
}

long int	get_time_of_last_meal(pthread_mutex_t *mutex,
	long int time_of_last_meal)
{
	long int	time;

	pthread_mutex_lock(mutex);
	time = time_of_last_meal;
	pthread_mutex_unlock(mutex);
	return (time);
}

void	set_time_of_last_meal(pthread_mutex_t *mutex,
	long int *time_of_last_meal, long int new_time_of_last_meal)
{
	pthread_mutex_lock(mutex);
	*time_of_last_meal = new_time_of_last_meal;
	pthread_mutex_unlock(mutex);
}

t_bool	get_status(pthread_mutex_t *mutex, t_bool status)
{
	t_bool	stat;

	pthread_mutex_lock(mutex);
	stat = status;
	pthread_mutex_unlock(mutex);
	return (stat);
}

void	set_status(pthread_mutex_t *mutex, t_bool *status, t_bool new_status)
{
	pthread_mutex_lock(mutex);
	*status = new_status;
	pthread_mutex_unlock(mutex);
}
