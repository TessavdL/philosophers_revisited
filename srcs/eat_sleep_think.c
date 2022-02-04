/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/30 18:48:28 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/04 11:59:40 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	think(t_philosopher *phil)
{
	print_message(&phil->mutexes.print, phil->id, get_time(),
		"is thinking");
}

static void	slep(t_philosopher *phil)
{
	print_message(&phil->mutexes.print, phil->id, get_time(),
		"is sleeping");
	usleep(phil->data.time_to_sleep);
}

static void	eat(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->mutexes.fork.left);
	print_message(&phil->mutexes.print, phil->id, get_time(),
		"has taken a fork");
	pthread_mutex_lock(&phil->mutexes.fork.right);
	print_message(&phil->mutexes.print, phil->id, get_time(),
		"is eating");
	set_time_of_last_meal(&phil->mutexes.time_of_last_meal,
		&phil->time_of_last_meal, get_time());
	usleep(phil->data.time_to_eat);
	if (phil->data.number_of_meals != UNINITIALIZED)
	{
		phil->data.number_of_meals--;
		if (phil->data.number_of_meals == 0)
		{
			set_status(&phil->mutexes.full, &phil->full, TRUE);
		}
	}
	pthread_mutex_unlock(&phil->mutexes.fork.left);
	pthread_mutex_unlock(&phil->mutexes.fork.right);
}

void	*eat_sleep_think(void *ptr)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)ptr;
	while (1)
	{
		eat(phil);
		if (get_status(&phil->mutexes.dead, *phil->dead) == TRUE)
		{
			break ;
		}
		if (phil->data.number_of_meals != UNINITIALIZED
			&& get_status(&phil->mutexes.full, phil->full) == TRUE)
		{
			break ;
		}
		slep(phil);
		think(phil);
	}
	return (phil);
}
