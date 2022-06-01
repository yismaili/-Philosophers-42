/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/01 21:00:11 by yismaili         ###   ########.fr       */
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
}

void	init_args(int ac, char **av, t_data	*data)
{
	t_philo		*philo;
	int			i;

	data->get_t = get_time();
	data->st = 0;
	data->eaten = 0;
	data->number_of_philo = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!philo)
		return ;
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		i++;
	}
	init_data(data, philo, av, ac);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		return (1);
	memset(&data, 0, sizeof(data));
	pthread_mutex_init(&data.mut_write, NULL);
	init_args(ac, av, &data);
	return (0);
}
