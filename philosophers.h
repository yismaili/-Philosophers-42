/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:52:48 by yismaili          #+#    #+#             */
/*   Updated: 2022/04/23 18:53:18 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_philo
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_must_eat;
    int philo_position;
    int lift_fork;
    int right_fork;
    pthread_mutex_t  mutex_philo;
    pthread_t        *th_philo;
    
}   t_philo;
typedef struct s_data
{
    int         number_of_philo;
    t_philo     *philo;
    pthread_mutex_t *mfork;
}   t_data;

int     ft_atoi(const char *str);
t_data  *init_args( int ac, char **av);
void    create_pthread(t_data *data);