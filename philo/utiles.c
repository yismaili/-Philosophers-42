/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:08:53 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/05 14:07:26 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sgn;
	int	i;

	res = 0;
	sgn = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+' ))
	{
		if (str[i] == '-')
			sgn *= -1;
		if (str[i + 1] == '\0')
			exit(0);
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i++] - '0');
		else
			exit(0);
	}
	return (res * sgn);
}

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		if (i == (data->number_of_philo - 1))
			philo[i].right_fork = &philo[0].fork;
		else
			philo[i].right_fork = &philo[i + 1].fork;
		i++;
	}
}

int	ft_die(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	init_data(t_data *data, char **av, int ac)
{
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->number_must_eat = ft_atoi(av[5]);
	}
	else
		data->number_must_eat = -1;
}
