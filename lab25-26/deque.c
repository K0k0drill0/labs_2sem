#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "deque.h"


deque *deque_create(deque *d) {
    d = (deque*)malloc(sizeof(deque));
    d->size = 0;
}


bool deque_isempty(deque *d) {
    if (d->size == 0) {
        return true;
    }
    else {
        return false;
    }
}


void deque_push_back(deque *d, int elem) {
    if (d->size == MAXSIZE) {
        printf("Deque is full.\n");
        return;
    }
    d->arr[d->size] = elem;
    d->size++; 
}


void deque_push_front(deque *d, int elem) {
    if (d->size == MAXSIZE) {
        printf("Deque is full.\n");
        return;
    }
    for (int i = d->size; i >= 1; i--) {
        d->arr[i] = d->arr[i-1];
    }
    d->arr[0] = elem;
    d->size++;
}


void deque_pop_front(deque *d) {
    if (d->size == 0) {
        printf("Дек пуст.\n");
        return;
    }
    for (int i = 1; i < d->size; i++) {
        d->arr[i-1] = d->arr[i];
    }
    d->size--;
}


void deque_pop_back(deque *d) {
    if (d->size == 0) {
        printf("Дек пуст.\n");
        return;
    }
    d->size--;
}


int deque_sizeof(deque *d) {
    return d->size;
}


int deque_front(deque *d) {
    return d->arr[0];
}


int deque_back(deque *d) {
    return d->arr[d->size-1];
}


void deque_print(const deque *d) {
    for (int i = 0; i < d->size; i++) {
        printf("%d ", d->arr[i]);
    }
    printf("\n");
}
