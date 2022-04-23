/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 23:54:48 by yismaili          #+#    #+#             */
/*   Updated: 2022/04/16 23:54:55 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// int x = 0;
// pthread_mutex_t mutex;
// void* routine()
// {
//     int i = 0;
//     while (i < 1000000)
//     {
//         pthread_mutex_lock(&mutex);
//          x++;
//         pthread_mutex_unlock(&mutex);
//          i++;
//     }
    
//     // printf("Test from threads\n");
//      //sleep(2);
//     // printf("Ending thread\n");
//      //printf("process id %d\n", getpid());
// }
// int main (int argc, char* argv[])
// {
//     pthread_t   th[4];
//     int i = 0;
//     pthread_mutex_init(&mutex, NULL);
//     while (i < 4)
//     {
//         pthread_create(&th[i], NULL, &routine, NULL);
//         pthread_join(th[i], NULL);
//         i++;
//     }
//      pthread_mutex_destroy(&mutex);
//      printf("value of x : %d\n", x);
//     return 0;
// }


// int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void* routine(void* arg) {
//     int index = *(int*)arg;
//     int sum = 0;
//     int j = 0;
//     while (j < 5) {
//         sum += primes[index + j];
//         j++;
//     }
//     printf("Local sum: %d\n", sum);
//     *(int*)arg = sum;
//     return arg;
// }

// int main(int argc, char* argv[]) {
//     pthread_t th[2];
//     int i = 0;
//     while (i < 2){
//         int* a = malloc(sizeof(int));
//         *a = i * 5;
//         if (pthread_create(&th[i], NULL, &routine, a) != 0) {
//             perror("Failed to create thread");
//         }
//         i++;
//     }
//     int globalSum = 0;
//     i = 0;
//     while (i < 2) {
//         int* r;
//         if (pthread_join(th[i], (void**) &r) != 0) {
//             perror("Failed to join thread");
//         }
//         globalSum += *r;
//         free(r);
//         i++;
//     }
//     printf("Global sum: %d\n", globalSum);
//     return 0;
// }
// pthread_mutex_t mutex;

// void* routine(void* arg)
// {
//    if(pthread_mutex_trylock(&mutex) == 0)
//    {
//         printf("Got luck\n");
//         sleep(1);
//         pthread_mutex_unlock(&mutex);
//    }
//    else{
//        printf("Didn't get lock\n");
//    }
// }

// int main(int argc, char **argv)
// {
//     int i = 0;
//     pthread_t th[4];
//     pthread_mutex_init(&mutex, NULL);
//     while (i < 4)
//     {
//         if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
//         {
//             perror("Error at creating thread");
//         }
//         i++;
//     }
//     i = 0;
//     while (i <  4)
//     {
//         if (pthread_join(th[i], NULL) != 0)
//         {
//             perror("Error at joining thread");
//         }
//         i++;
//     }
    
    
// }
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast (&condFuel);
        sleep(1);
    }
}

void* car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main(int argc, char* argv[]) {
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    int i = 0;
    while(i < 2) {
        if (i == 1) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
        i++;
    }
i = 0;
    while (i < 2) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
        i++;
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}