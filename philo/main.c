/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/05 14:10:28 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_message(char *s, int philo_id, t_data *data, char *clor)
{
	pthread_mutex_lock(&data->mut_write);
	printf("%s %u %d %s\n", clor, get_time() - data->get_t, philo_id, s);
	pthread_mutex_unlock(&data->mut_write);
}

void	print_error(char *s, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->mut_write);
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	data->st = 1;
}

void	init_args(t_data	*data, t_philo *philo)
{
	int			i;

	data->get_t = get_time();
	data->st = 0;
	data->eaten = 0;
	philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!philo)
		ft_die("no space left");
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&philo[i].fork, NULL))
			ft_die("Failed to init this mutex");
		i++;
	}
	if (pthread_mutex_init(&data->mut_write, NULL))
		ft_die("Failed to init this mutex");
	init_philo(philo, data);
	create_thread(philo, data);
}

void	ft_free(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&philo[i].fork);
		i++;
	}
	free(philo);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;

	if (ac < 5)
		return (0);
	memset(&data, 0, sizeof(data));
	init_data(&data, av, ac);
	if (data.number_of_philo <= 0 || data.number_must_eat == 0
		|| data.time_to_die <= 0 || data.time_to_eat <= 0
		|| data.time_to_sleep <= 0)
		return (0);
	init_args(&data, &philo);
	return (0);
}
