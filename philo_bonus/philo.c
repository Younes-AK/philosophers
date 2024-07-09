/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:59:06 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/04 11:06:48 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_args(char *s)
{
	int	i;

	i = 0;
	if (*s == '\0')
		return (false);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

bool	parssing(char **av, int ac)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		ft_error("Error\ninvalid number of arguments");
		return (false);
	}
	while (i < ac - 1)
	{
		if (!check_args(av[i]))
		{
			ft_error("Error\ninvalid argument");
			return (false);
		}
		if (ft_atol(av[i]) > INT_MAX || ft_strlen(av[i]) > 10)
		{
			ft_error("Error\narg value major than int max");
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parssing(av + 1, ac))
		return (1);
	data.philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!data.philos)
	{
		ft_error("Error\nmalloc failed allocate memory");
		return (1);
	}
	if (data_init(&data, av) != 0)
	{
		free (data.philos);
		return (1);
	}
	if (dinner_routine(&data))
		return (free(data.philos), 1);
	free(data.philos);
	return (0);
}
