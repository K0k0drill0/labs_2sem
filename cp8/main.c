#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// #include "list.h"


typedef struct {
    int real;
    int imaginary;
} complex;


complex cmplx(int r, int im) {
    complex c;
    c.real = r;
    c.imaginary = im;
    return c;
}


void cmplx_print(complex elem) {
    if (elem.imaginary < 0) {
        printf("%d%di", elem.real, elem.imaginary);
    }
    else {
        printf("%d+%di", elem.real, elem.imaginary);
    }
}


typedef struct node{
    complex key;
    struct node *ptr_next;
} node;


typedef struct {
    int size;
    node *ptr_last;
} list;


list *lst_init(list *l, complex elem) {
    l = (list*)malloc(sizeof(list));
    l->size = 1;
    node *new_node;
    new_node = (node*)malloc(sizeof(node));
    new_node->key = elem;
    new_node->ptr_next = new_node;
    l->ptr_last = new_node;
    //return l;
}


node *lst_ptrwind(list *l, int ind) { //выдает указатель на элемент с введенным индексом
    node *nd = l->ptr_last;
    int sz = l->size;
    if (ind >= sz) {
        printf("Элемента с таким индексом нет\n");
        return NULL;
    }
    for (int i = 0; i <= ind; i++) {
        nd = nd->ptr_next;
    }
    return nd;
}


int lst_size(list *lst){
    return lst->size;
}


bool lst_isempty(list *lst) {
    return (lst->size == 0) ? true : false;
}



void lst_addelem(list *lst, int ind, complex elem) { // осуществляет вставку элемента после того, чей индекс указан
    node *new_node;
    new_node = (node*)malloc(sizeof(node));
    new_node->key = elem;
    node *after = lst_ptrwind(lst, ind);
    node *tmp = after->ptr_next;
    after->ptr_next = new_node;
    new_node->ptr_next = tmp;
    lst->size++;
}


void lst_pushback(list *lst, complex elem) {
    node *new_node;
    new_node = (node*)malloc(sizeof(node));
    new_node->key = elem;
    if (lst->size == 0) {
        lst->ptr_last = new_node;
        new_node->ptr_next = new_node;
        lst->size++;
    }
    node *tmp = lst->ptr_last->ptr_next;
    lst->ptr_last->ptr_next = new_node;
    new_node->ptr_next = tmp;
    lst->ptr_last = new_node;
    lst->size++;
}


void lst_delelem(list *lst, int ind) { // удаляет элемент под заданным индексом
    if (lst->size == 1) {
        node *del_elem;
        del_elem = lst->ptr_last;
        del_elem = NULL;
        lst->size--;
        lst->ptr_last = del_elem;
        return;
    }
    node *del_ptr;
    del_ptr = lst_ptrwind(lst, ind);
    node *tmp = del_ptr;
    while (tmp->ptr_next != del_ptr) {
        tmp = tmp->ptr_next;
    }
    tmp->ptr_next = del_ptr->ptr_next;
    free(del_ptr);
    lst->size--;
}


void lst_delall(list *lst) {
    int sz = lst->size;
    node *tmp1 = lst->ptr_last;
    node *tmp2; 
    node *tmp3;
    for (int i = 1; i < sz; i++) {
        tmp2 = tmp1->ptr_next;
        tmp3 = tmp1;
        free(tmp3);
        tmp1 = tmp2;
    }
    tmp1 = NULL;
    lst->ptr_last = tmp1;
    //tmp1->ptr_next = NULL;
    lst->size = 0;
}


void lst_custom(list *lst, complex elem) { // функция удаляет весь список, если в нем есть заданный элемент
    int sz = lst->size;
    node *tmp = lst->ptr_last;
    for (int i = 0; i <= sz; i++) {
        tmp = tmp->ptr_next;
        if (tmp->key.real == elem.real && tmp->key.imaginary == elem.imaginary) {
            lst_delall(lst);
        }
    }
}


void lst_print(list *lst) {
    int sz = lst->size;
    if (sz == 0) {
        printf("List is empty!\n");
        return;
    }
    node *tmp = lst->ptr_last;
    for (int i = 0; i < sz; i++) {
        tmp = tmp->ptr_next;
        cmplx_print(tmp->key);
        printf("; ");
    }
    printf("\n");
}


void pr_menu() {
    printf("Input your command\n");
    printf("Create list: 1 r i (r is real part, i is complex)\n");
    printf("Add elem after another elem, with inputed index: 2 ind r i\n");
    printf("Push back an elem: 3 r i\n");
    printf("Del elem, that has inputed index: 4 ind\n");
    printf("Length of list: 5\n");
    printf("Clear list, if in contains inputed number: 6 r i\n");
    printf("Print list: 7\n");
    printf("Exit: 0\n");
}


int main() {
    list *lst;
    pr_menu();
    int q;
    while(1) {
        scanf("%d", &q);
        if (q == 1) {
            int r, i;
            scanf("%d%d", &r, &i);
            complex elem = cmplx(r, i);
            lst = lst_init(lst, elem);
        }
        if (q == 2) {
            int ind, r, i;
            scanf("%d%d%d", &ind, &r, &i);
            complex elem = cmplx(r, i);
            lst_addelem(lst, ind, elem);
        }
        if (q == 3) {
            int r, i;
            scanf("%d%d", &r, &i);
            complex elem = cmplx(r, i);
            lst_pushback(lst, elem);
        }
        if (q == 4) {
            int ind;
            scanf("%d", &ind);
            lst_delelem(lst, ind);
        }
        if (q == 5) {
            int ans = lst_size(lst);
            printf("The size of an elem is %d\n", ans);
        }
        if (q == 6) {
            int r, i;
            scanf("%d%d", &r, &i);
            complex elem = cmplx(r, i);
            lst_custom(lst, elem);
        }
        if (q == 7) {
            lst_print(lst);
        }
        if (q == 0) {
            return 0;
        }
    }
    return 0;
}
