/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/04/26 20:16:28 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->lift_fork);
	get_message(3);
	pthread_mutex_lock(&philo->right_fork);
	get_message(1);
}

void	clean_forks(t_philo *philo, t_data *data)
{
	get_message(2);
	pthread_mutex_unlock(&philo->lift_fork);
	pthread_mutex_unlock(&philo->right_fork);
	usleep(data->time_to_sleep * 1000);
}
void	get_message(int type)
{
	t_data data;
	pthread_mutex_lock(&data.mut_write);
	if (type == 1)
	{
		printf(" is eating\n");
		return ;
	}
	else if (type == 2)
	{
		printf("  is sleeping\n");
		return ;
	}
	else if (type == 3)
	{
		printf(" has taken a fork\n");
		return ;
	}
	else if (type == 4)
	{
		printf("  is thinking\n");
		return ;
	}
	else
	{
		printf("died\n");
		return ;
	}
	pthread_mutex_unlock(&data.mut_write);
}

int main(int ac, char **av)
{
	t_data	*data;
	if ( ac < 5)
		return(1);
	data = init_args(ac, av);
	create_pthread(data);
	return 0;
}
