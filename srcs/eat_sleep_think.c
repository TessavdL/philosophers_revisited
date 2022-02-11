/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/30 18:48:28 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/11 17:14:42 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	think(t_philosopher *phil)
{
	print_message(phil, get_time() - phil->time_start, "is thinking");
}

static void	slep(t_philosopher *phil)
{
	if (print_message(phil, get_time() - phil->time_start, "is sleeping"))
		return ;
	usleep(phil->data.time_to_sleep * 1000);
}

static void	eat(t_philosopher *phil)
{
	pthread_mutex_lock(phil->mutexes.fork.left);
	if (print_message(phil, get_time() - phil->time_start, "has taken a fork"))
	{
		pthread_mutex_unlock(phil->mutexes.fork.left);
		return ;
	}
	pthread_mutex_lock(phil->mutexes.fork.right);
	if (print_message(phil, get_time() - phil->time_start, "is eating"))
	{
		pthread_mutex_unlock(phil->mutexes.fork.right);
		pthread_mutex_unlock(phil->mutexes.fork.left);
		return ;
	}
	set_time_of_last_meal(&phil->mutexes.time_of_last_meal,
		&phil->time_of_last_meal, get_time());
	usleep(phil->data.time_to_eat * 1000);
	if (phil->data.number_of_meals != UNINITIALIZED)
	{
		phil->data.number_of_meals--;
	}
	pthread_mutex_unlock(phil->mutexes.fork.right);
	pthread_mutex_unlock(phil->mutexes.fork.left);
}

void	*eat_sleep_think(void *ptr)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)ptr;
	while (1)
	{
		eat(phil);
		if (get_status(phil->mutexes.dead, *phil->dead) == TRUE)
		{
			break ;
		}
		if (phil->data.number_of_meals == 0)
		{
			set_status(&phil->mutexes.full, &phil->full, TRUE);
			break ;
		}
		slep(phil);
		think(phil);
	}
	return (phil);
}
