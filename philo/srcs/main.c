/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 11:43:33 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/24 15:53:18 by tevan-de      ########   odam.nl         */
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
	parser(argument_count, arguments, &input);
	if (check_final_input(argument_count, input) == INVALID)
	{
		return (1);
	}
	return (setup_simulation(input, input.number_of_philosophers));
}
