//
//  queue.h
//  Queue
//
//  Created by Anna Balytska on 4/3/13.
//  Copyright (c) 2013 softserve. All rights reserved.
//

#ifndef __Queue__queue__
#define __Queue__queue__

#include <iostream>
#include <queue>
#include <pthread.h>

using namespace std;

template <class T>
class MyQueue
{
    queue<T> myQueue;
    pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
public:
    void pushValue (T const& value);
    void getAndPop ();
};

template <class T>
void MyQueue<T>::pushValue (T const& value)
{
    pthread_mutex_lock (&queueMutex);
    myQueue.push(value);
    pthread_cond_signal( &cond );
    pthread_mutex_unlock (&queueMutex);
};


template <class T>
void MyQueue<T>::getAndPop ()
{
    pthread_mutex_lock (&queueMutex);
    while(myQueue.empty())
        pthread_cond_wait( &cond, &queueMutex );
    T returnValue=myQueue.front();
    myQueue.pop();
    cout<<returnValue;
    pthread_mutex_unlock (&queueMutex);
};

#endif /* defined(__Queue__queue__) */
