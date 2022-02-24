/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tessa <tessa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 11:47:42 by tessa         #+#    #+#                 */
/*   Updated: 2022/02/11 16:10:04 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static long int	a_to_i_continued(const char *str, unsigned long int res,
	int sign)
{
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((res > 922337203685477580 || (res == 922337203685477580
					&& (*str - '0') > 7)) && sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580
					&& (*str - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int	a_to_i(const char *str)
{
	unsigned long int	res;
	int					sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
	if (*str == '-')
	{
			sign = -1;
			str++;
	}
	else if (*str == '+')
			str++;
	res = a_to_i_continued(str, res, sign);
	return (res * sign);
}

t_bool	character_is_digit(const char c)
{
	if (c >= '0' && c <= '9')
	{
		return (TRUE);
	}
	return (FALSE);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;

	p = malloc(count * size);
	if (!p)
	{
		return (NULL);
	}
	i = 0;
	while (i < (count * size))
	{
			p[i] = '\0';
			i++;
	}
	return (p);
}

int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
	{
		i++;
	}
	return (i);
}
