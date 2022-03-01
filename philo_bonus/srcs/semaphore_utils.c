/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 14:49:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/02/28 16:44:51 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	print_message(t_philosopher *phil, char *message, int mode)
{
	if (sem_wait(phil->semaphores.print))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	if (mode != DEAD
		&& get_set_status(GET, phil->semaphores.dead, phil->dead, -1) == TRUE)
	{
		if (sem_post(phil->semaphores.print))
			exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
		return (1);
	}
	printf("%ld %d %s\n", get_time_ms() - phil->time_start, phil->id, message);
	if (sem_post(phil->semaphores.print))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
	return (0);
}

t_bool	get_set_status(int mode, sem_t *semaphore, t_bool *status,
	t_bool new_status)
{
	t_bool	ret;

	ret = new_status;
	if (sem_wait(semaphore))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	if (mode == GET)
	{
		ret = *status;
	}
	else if (mode == SET)
	{
		*status = new_status;
	}
	if (sem_post(semaphore))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
	return (ret);
}

long int	get_set_time_of_last_meal(int mode, sem_t *semaphore,
	long int *time_of_last_meal, long int new_time_of_last_meal)
{
	long int	ret;

	ret = new_time_of_last_meal;
	if (sem_wait(semaphore))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	if (mode == GET)
	{
		ret = *time_of_last_meal;
	}
	else if (mode == SET)
	{
		*time_of_last_meal = new_time_of_last_meal;
	}
	if (sem_post(semaphore))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
	return (ret);
}
