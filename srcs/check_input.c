/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/22 13:00:00 by tessa         #+#    #+#                 */
/*   Updated: 2022/01/27 12:54:21 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static t_validity	check_arguments_validity(char **arguments)
{
	int	i;
	int	j;

	i = 1;
	while (arguments[i])
	{
		j = 0;
		while (arguments[i][j])
		{
			if (character_is_digit(arguments[i][j]) == FALSE)
			{
				return (INVALID);
			}
			j++;
		}
		i++;
	}
	return (VALID);
}

static t_validity	check_argument_count_validity(int argument_count)
{
	if (argument_count != 5 && argument_count != 6)
	{
		return (INVALID);
	}
	return (VALID);
}

t_validity	check_initial_input(int argument_count, char **arguments)
{
	if (check_argument_count_validity(argument_count) == INVALID)
	{
		return (INVALID);
	}
	if (check_arguments_validity(arguments) == INVALID)
	{
		return (INVALID);
	}
	return (VALID);
}

t_validity	check_final_input(int argument_count, t_input input)
{
	if (input.number_of_philosophers > 200)
	{
		return (INVALID);
	}
	if (input.time_until_death < 50)
	{
		return (INVALID);
	}
	if (input.time_to_eat < 50)
	{
		return (INVALID);
	}
	if (input.time_to_sleep < 50)
	{
		return (INVALID);
	}
	if (argument_count == 6 && input.number_of_meals < 0)
	{
		return (INVALID);
	}
	return (VALID);
}
