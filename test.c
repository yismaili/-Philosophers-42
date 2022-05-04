#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

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
long int git_time()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return(current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
int main() {
  printf("seconds : %ld\n", git_time());

  return 0;
}