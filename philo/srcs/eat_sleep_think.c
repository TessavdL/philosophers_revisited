/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/30 18:48:28 by tessa         #+#    #+#                 */
/*   Updated: 2022/03/01 13:31:19 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*one_philosopher_edge_case(t_philosopher *phil)
{
	if (phil->data.number_of_philosophers == 1)
	{
		print_message(phil, "has taken a fork");
		let_time_pass(phil, phil->data.time_until_death);
		print_message(phil, "died");
	}
	return (NULL);
}

static int	update_number_of_meals_eaten(t_philosopher *phil)
{
	if (phil->data.number_of_meals != UNINITIALIZED)
	{
		phil->data.number_of_meals--;
		if (phil->data.number_of_meals == 0)
		{
			get_set_status(SET, &phil->mutexes.full, &phil->full, TRUE);
			return (unlock_forks(phil->mutexes.fork, 1));
		}
	}
	return (0);
}

static int	eat(t_philosopher *phil)
{
	pthread_mutex_lock(phil->mutexes.fork.left);
	if (print_message(phil, "has taken a fork"))
	{
		pthread_mutex_unlock(phil->mutexes.fork.left);
		return (1);
	}
	pthread_mutex_lock(phil->mutexes.fork.right);
	if (print_message(phil, "is eating"))
	{
		return (unlock_forks(phil->mutexes.fork, 1));
	}
	get_set_time_of_last_meal(SET, &phil->mutexes.time_of_last_meal,
		&phil->time_of_last_meal, get_time_ms());
	if (let_time_pass(phil, phil->data.time_to_eat))
	{
		return (unlock_forks(phil->mutexes.fork, 1));
	}
	if (update_number_of_meals_eaten(phil))
	{
		return (unlock_forks(phil->mutexes.fork, 1));
	}
	return (unlock_forks(phil->mutexes.fork, 0));
}

void	*eat_sleep_think(void *ptr)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)ptr;
	if (phil->data.number_of_philosophers == 1)
	{
		return (one_philosopher_edge_case(phil));
	}
	while (1)
	{
		if (eat(phil))
			break ;
		if (print_message(phil, "is sleeping"))
			break ;
		if (let_time_pass(phil, phil->data.time_to_sleep))
			break ;
		if (print_message(phil, "is thinking"))
			break ;
	}
	return (NULL);
}
