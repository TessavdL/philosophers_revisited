/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/30 18:48:28 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/28 17:33:19 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	eat(t_philosopher *phil)
{
	if (sem_wait(phil->semaphores.forks))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	print_message(phil, "has taken a fork", 1);
	if (sem_wait(phil->semaphores.forks))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	print_message(phil, "is eating", 1);
	get_set_time_of_last_meal(SET, phil->semaphores.time_of_last_meal,
		&phil->time_of_last_meal, get_time_ms() - phil->time_start);
	phil->data.number_of_meals--;
	let_time_pass(phil->data.time_to_eat * 1000);
	if (sem_post(phil->semaphores.forks))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
	if (sem_post(phil->semaphores.forks))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
}

static int	eat_sleep_think(t_philosopher *phil)
{
	eat(phil);
	if (phil->data.number_of_meals != UNINITIALIZED && phil->data.number_of_meals == 0)
	{
		get_set_status(SET, phil->semaphores.full, &phil->full, TRUE);
		return (1);
	}
	print_message(phil, "is sleeping 💤", 1);
	let_time_pass(phil->data.time_to_sleep * 1000);
	print_message(phil, "is thinking 💡", 1);
	return (0);
}

void	eat_sleep_think_repeat(t_philosopher *phil)
{
	pthread_t	dead_thread;

	if (pthread_create(&dead_thread, NULL, &monitoring, phil))
		exit(ERROR_FAILED_TO_CREATE_THREAD);
	if (pthread_detach(dead_thread))
		exit(ERROR_FAILED_TO_DETACH_THREAD);
	while (1)
	{
		if (eat_sleep_think(phil))
			exit(0);
	}
}