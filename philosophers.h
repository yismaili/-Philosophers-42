/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:52:48 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/11 21:47:14 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef struct s_data
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_must_eat;
    unsigned int get_t;
    pthread_mutex_t mut_write;
    int             st;
    int             count_philo;
  
}   t_data;

typedef struct s_philo
{
    int             philo_id;
    pthread_mutex_t *right_fork;
    pthread_mutex_t fork;
    pthread_t		th_philo;
    t_data          *data;
    int             count_eat;
   unsigned int             time_to_kill;
    
}   t_philo;

int     ft_atoi(const char *str);
t_philo   *init_args(int ac, char **av, t_data *data);
void	init_philo(t_philo *philo, t_data *data);
void	take_forks(t_philo *philo);
void	get_message(char *s, int id, t_data *data, char *clor);
unsigned int get_time();
void	clean_forks(t_philo *philo);
void	philo_activities(t_philo *philo);
 int	ft_die(char *str);
 void *ft_check(void *ptr);
 
#endif