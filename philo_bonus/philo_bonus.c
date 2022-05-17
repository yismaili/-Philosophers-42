/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:39:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/16 23:15:37 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data    *init_data(int ac, char **av, t_data	*data)
{
	int		i;
	pthread_t temp;
	
	if (!data)
		return (0);
	data->number_of_philo =  ft_atoi(av[1]); 
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->number_must_eat = ft_atoi(av[5]);
	}
	else
		data->number_must_eat = -1;
	if (data->number_of_philo <= 0 || data->number_of_philo > 200 || data->number_must_eat == 0)
	// 	ft_die("ArgumentError\n");
    // while (i < data->number_of_philo)
    // {
	//     philo->pid = fork();
    //     if (philo->pid < 0)
    //         ft_die("fork");
    //     if (philo->pid == 0)
    //     {
    //         child_process(philo);  
    //     }
    //     else
    //     {
    //         wait(0);
    //         //parent_process(f2, end, av, a_env);
    //     } 
    //     i++;
    // }
	return (data);
}

void	init_philo(t_data *data, t_philo	*philo)
{
	int	i;
	i = 0;

	philo = malloc(sizeof(t_philo) * data->number_of_philo);
	philo->pid = malloc(sizeof(pid_t) * data->number_of_philo);
	while (i < data->number_of_philo)
	 {
		data->pid[i] = fork();
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		philo[i].fork = i;
		 if (i == (data->number_of_philo - 1))
	 	 	philo[i].right_fork = &philo[0].fork;
		 else
		 	philo[i].right_fork = &philo[i + 1].fork;
		if (data->pid[i] == 0)
			start(philo[i]);
		i++;
	}
		
}

void	create_process(t_data *data)
{
	t_philo	*philo;
	int	i;

	philo = malloc(sizeof(t_philo) * data->number_of_philo);
	philo->pid = malloc(sizeof(pid_t) * data->number_of_philo);
	
	
}