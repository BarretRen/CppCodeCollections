#include "../include/apue.h"
#include <pthread.h>

void cleanup(void* arg)
{
    printf("cleanup: %s\n", (char*)arg);
}

void* thr_fn1(void* arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler");
    pthread_cleanup_push(cleanup, "thread 1 second handler");
    printf("thread 1 push complete\n");

    if (arg)
    {
        return((void*)1);//return不会触发清理程序
    }
    pthread_cleanup_pop(0);//将注册过的清理函数一个一个pop出来
    pthread_cleanup_pop(0);
    return((void*)1);
}

void* thr_fn2(void* arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler");
    pthread_cleanup_push(cleanup, "thread 2 second handler");
    printf("thread 2 push complete\n");

    if (arg)
    {
		pthread_exit((void *)2);//pthread_exit会触发清理程序
    }
    pthread_cleanup_pop(0);//将注册过的清理函数一个一个pop出来
    pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int main()
{
    int err;
    pthread_t tid1, tid2;
    void* ret;

    err = pthread_create(&tid1, NULL, thr_fn1, (void*)1);
    if (err != 0)
        err_exit(err, "can't crreate thread 1");
    err = pthread_create(&tid2, NULL, thr_fn2, (void*)1);
    if (err != 0)
        err_exit(err, "can't crreate thread 2");

    if (pthread_join(tid1, &ret) != 0)
        err_exit(err, "can't join thread 1");
    printf("thread 1 exit code: %ld\n", (long)ret);
    
    if (pthread_join(tid2, &ret) != 0)
        err_exit(err, "can't join thread 2");
    printf("thread 2 exit code: %ld\n", (long)ret);

    return 0;

}
