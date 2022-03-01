/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 17:12:33 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/28 17:25:09 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	parser(const int argument_count, char **arguments, t_input *input)
{
	input->number_of_philosophers = a_to_i(arguments[1]);
	input->time_until_death = a_to_i(arguments[2]);
	input->time_to_eat = a_to_i(arguments[3]);
	input->time_to_sleep = a_to_i(arguments[4]);
	if (argument_count == 6)
	{
		input->number_of_meals = a_to_i(arguments[5]);
	}
	else
	{
		input->number_of_meals = UNINITIALIZED;
	}
}
