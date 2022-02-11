/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 11:43:33 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/11 15:52:45 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argument_count, char **arguments)
{
	t_input	input;

	if (check_initial_input(argument_count, arguments) == INVALID)
	{
		return (1);
	}
	else
	{
		parser(argument_count, arguments, &input);
		if (check_final_input(argument_count, input) == INVALID)
		{
			return (1);
		}
		if (setup_simulation(input, input.number_of_philosophers))
		{
			return (1);
		}
		return (0);
	}
}
