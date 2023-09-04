#ifndef DEQUE_H
#define DEQUE_H


#include <stdbool.h>
#define MAXSIZE 5


typedef struct deque {
    int size;
    int arr[MAXSIZE];
} deque;


deque *deque_create(deque *); 


bool deque_isempty(deque *);


void deque_push_back(deque *, int);


void deque_push_front(deque *, int);


void deque_pop_front(deque *);


void deque_pop_back(deque *);


int deque_sizeof(deque *);


int deque_front(deque *);


int deque_back(deque *);


void deque_print(const deque *);


#endif
