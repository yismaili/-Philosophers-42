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
#include <sys/time.h>

typedef struct s_data
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_must_eat;
    	unsigned int get_t;
    pthread_mutex_t mut_write;
    pthread_mutex_t  mutex_philo;
  
}   t_data;

typedef struct s_philo
{
    int             philo_position;
    pthread_mutex_t lift_fork;
    pthread_mutex_t right_fork;
    pthread_mutex_t    fork;
    t_data              *data;
    int             eat_count;
    int             eating;
    int             last_time;
}   t_philo;
int     ft_atoi(const char *str);
t_data  *init_args( int ac, char **av);
void    create_pthread(t_data *data);
void	init_philo(t_philo *philo, t_data *data);
void	take_forks(t_philo *philo);
void	get_message(char *s, int id, t_data *data);
long int get_time();
void	clean_forks(t_philo *philo);
void	philo_activities(t_philo *philo);