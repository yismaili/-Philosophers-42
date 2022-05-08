/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:52:48 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/08 18:01:30 by yismaili         ###   ########.fr       */
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
    int             stut;
    int             nb;
  
}   t_data;

typedef struct s_philo
{
    int             philo_id;
    pthread_mutex_t *right_fork;
    pthread_mutex_t fork;
    pthread_t			th_philo;
    t_data          *data;
    int             eat_count;
    int             last_time;
}   t_philo;

int     ft_atoi(const char *str);
t_philo   *init_args(int ac, char **av, t_data *data);
void	init_philo(t_philo *philo, t_data *data);
void	take_forks(t_philo *philo);
void	get_message(char *s, int id, t_data *data);
long int get_time();
void	clean_forks(t_philo *philo);
void	philo_activities(t_philo *philo);
 void	ft_die(char *str , t_philo *philo);
 void *ft_check(void *ptr);