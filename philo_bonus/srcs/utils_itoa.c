/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_itoa.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 15:35:22 by tevan-de      #+#    #+#                 */
/*   Updated: 2022/02/28 15:35:44 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static char	*inttostr(char *str, int n_digits, long n, int sign)
{
	if (sign == 1)
	{
		n_digits++;
		str[0] = '-';
	}
	str[n_digits] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[n_digits - 1] = n % 10 + '0';
		n = n / 10;
		n_digits--;
	}
	return (str);
}

static int	count_digits(long n, int count)
{
	if (n / 10 == 0)
		return (count);
	else
	{
		count++;
		return (count_digits(n / 10, count));
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		n_digits;
	int		sign;
	long	n1;

	n1 = n;
	sign = 0;
	n_digits = count_digits(n1, 1);
	if (n < 0)
	{
		sign = 1;
		n1 = n1 * -1;
	}
	str = malloc(sizeof(char) * (n_digits + sign + 1));
	if (!str)
		return (NULL);
	str = inttostr(str, n_digits, n1, sign);
	return (str);
}
