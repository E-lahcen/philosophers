#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int sem = 0;

void    my_wait(void *arg)
{
    int *sem = (int *)arg;
    printf("In my_wait before sem = %d\n", *sem);
    if (!*sem)
        while (1);
    *(sem)-=1;
    printf("In my_wait after sem = %d\n", *sem);
    sleep(5);
}

void    my_post(void *arg)
{
    int *sem = (int *)arg;
    printf("In my_post before sem = %d\n", *sem);
    *(sem)+=1;
    printf("In my_post after sem = %d\n", *sem);
    sleep(5);
}

int main()
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, (void *)&my_wait, (void *)&sem);
    sleep(5);
    pthread_create(&th2, NULL, (void *)&my_post, (void *)&sem);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("In main sem = %d\n", sem);
    return 0;
}