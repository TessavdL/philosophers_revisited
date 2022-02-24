/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 12:14:03 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/02/24 16:29:54 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static t_bool	check_if_phil_is_dead(t_philosopher *phil)
{
	const long int	current_time = get_time_ms() - phil->time_start;
	const long int	time_of_last_meal = get_set_time_of_last_meal(GET,
			&phil->mutexes.time_of_last_meal, &phil->time_of_last_meal, -1)
		- phil->time_start;

	if (current_time - time_of_last_meal >= phil->data.time_until_death)
	{
		return (TRUE);
	}
	return (FALSE);
}

void	*monitoring(void *ptr)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)ptr;
	while (1)
	{
		if (phil->data.number_of_meals != UNINITIALIZED
			&& get_set_status(GET, &phil->mutexes.full, &phil->full, -1)
			== TRUE)
		{
			break ;
		}
		if (check_if_phil_is_dead(phil) == TRUE)
		{
			print_message(phil, "has died");
			get_set_status(SET, phil->mutexes.dead, phil->dead, TRUE);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
