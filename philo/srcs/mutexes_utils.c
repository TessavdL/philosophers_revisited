/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:51:42 by tessa         #+#    #+#                 */
/*   Updated: 2022/03/01 13:29:15 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	print_message(t_philosopher *phil, char *message)
{
	pthread_mutex_lock(phil->mutexes.print);
	if (get_set_status(GET, phil->mutexes.dead, phil->dead, -1) == TRUE)
	{
		pthread_mutex_unlock(phil->mutexes.print);
		return (1);
	}
	printf("%ld %d %s\n", get_time_ms() - phil->time_start, phil->id, message);
	pthread_mutex_unlock(phil->mutexes.print);
	return (0);
}

long int	get_set_time_of_last_meal(int mode, pthread_mutex_t *mutex,
	long int *time_of_last_meal, long int new_time_of_last_meal)
{
	long int	ret;

	ret = new_time_of_last_meal;
	pthread_mutex_lock(mutex);
	if (mode == GET)
	{
		ret = *time_of_last_meal;
	}
	else if (mode == SET)
	{
		*time_of_last_meal = new_time_of_last_meal;
	}
	pthread_mutex_unlock(mutex);
	return (ret);
}

t_bool	get_set_status(int mode, pthread_mutex_t *mutex, t_bool *status,
	t_bool new_status)
{
	t_bool	ret;

	ret = new_status;
	pthread_mutex_lock(mutex);
	if (mode == GET)
	{
		ret = *status;
	}
	else if (mode == SET)
	{
		*status = new_status;
	}
	pthread_mutex_unlock(mutex);
	return (ret);
}

int	unlock_forks(t_fork fork, int ret)
{
	pthread_mutex_unlock(fork.right);
	pthread_mutex_unlock(fork.left);
	return (ret);
}
