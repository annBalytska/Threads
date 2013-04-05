//
//  main.cpp
//  Queue
//
//  Created by Anna Balytska on 4/3/13.
//  Copyright (c) 2013 softserve. All rights reserved.
//

#include <iostream>
#include "MyQueue.h"
#include <pthread.h>
using namespace std;
MyQueue<int> newQueue;
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_pop (void* arg) {
    while (1)
    {
        int *i = reinterpret_cast<int*>(arg);
        pthread_mutex_lock (&Mutex);
        cout<<" "<<*i<<":";
        pthread_mutex_unlock (&Mutex);
        newQueue.getAndPop();
    }
    return NULL;
}

void* thread_push (void* arg) {
    while (1)
    {   int *i = reinterpret_cast<int*>(arg);
        newQueue.pushValue(*i);
    }
    return NULL;
}


int main(int argc, const char * argv[])
{
    
    pthread_t threadPop,threadPush;
    int n=1,m=2,k=3,l=4,z=5;
    
    pthread_create (&threadPush, NULL, &thread_push, &n);
    pthread_create (&threadPush, NULL, &thread_push, &m);
    pthread_create (&threadPush, NULL, &thread_push, &k);
    pthread_create (&threadPush, NULL, &thread_push, &l);
    pthread_create (&threadPush, NULL, &thread_push, &z);
    pthread_create (&threadPop, NULL, &thread_pop, &n);
    pthread_create (&threadPop, NULL, &thread_pop, &m);
    
    pthread_join (threadPush, NULL);
   // pthread_join (threadPop, NULL);
    

    
    return 0;
}

