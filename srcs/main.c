/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 11:43:33 by tessa         #+#    #+#                 */
/*   Updated: 2022/01/27 15:45:27 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argument_count, char **arguments)
{
	t_input	input;
	
	if (check_initial_input(argument_count, arguments) == INVALID)
	{
		printf("invalid\n");
		return (1);
	}
	else
	{
		printf("valid\n");
		parser(argument_count, arguments, &input);
		if (check_final_input(argument_count, input) == INVALID)
		{
			printf("invalid\n");
			return (1);
		}
		if (setup_simulation(input))
		{
			printf("error\n");
			return (1);
		}
		return (0);
	}
}
