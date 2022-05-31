/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:52:32 by yismaili          #+#    #+#             */
/*   Updated: 2022/05/31 18:55:13 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <signal.h>
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct s_data
{
    int             number_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_must_eat;
    unsigned int    get_t;
    sem_t           *eaten;
    sem_t           *mut_write;
    sem_t           *fork;
    sem_t           *dead;
    sem_t           *ext;
    
}   t_data;

typedef struct s_philo
{
    t_data  *data;
    int     philo_id;
    int     time_to_kill;
    int     count_eat;
}   t_philo;

t_data    *init_data(int ac, char **av, t_data	*data);
void	        get_message(char *s, int philo_id, t_data *data, char *clor);
void	        init_philo(t_data *data);
unsigned int    get_time();
int             ft_die(char *str);
void	philo_activities(t_philo *philo);
void *start_philo(void *ptr);
int	ft_atoi(const char *str);
void	ft_kill(t_data *data, int **pid, t_philo *philo);
void	init_sem(t_data *data);
void	ft_kill(t_data *data, int **pid, t_philo *philo);
void	*check_eat(void *ptr);
#endif