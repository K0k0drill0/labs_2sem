#include <stdio.h>
#include <stdlib.h>
#include "deque.h"


deque *concatenation(deque *d1, deque *d2) {
    deque *d = (deque*)malloc(sizeof(deque));
    *d = *d1; 
    int s1 = deque_sizeof(d1);
    int s2 = deque_sizeof(d2);
    if (s1 + s2 > MAXSIZE) {
        printf("Произойдет переполнение.\n");
        return NULL;
    }
    for (int i = 0; i < s2; i++) {
        int f2 = deque_front(d2);
        deque_push_back(d, f2);
        deque_pop_front(d2);
        deque_push_back(d2, f2);
    }
    return d;
}


deque *mass_to_deque(int *numbers, int l, int r) {
    deque *d;
    d = deque_create(d);
    for (int i = l; i <= r; i++) {
        deque_push_back(d, numbers[i]);
    }
    return d;
}


deque *qs(deque *d, int left, int right) {
    deque *d1_c;
    d1_c = deque_create(d1_c);
    deque *d2_c;
    d2_c = deque_create(d2_c);


    int numbers[MAXSIZE];
    int sz = deque_sizeof(d);
    for (int i = 0; i < sz; i++) {
        numbers[i] = deque_back(d);
        deque_pop_back(d);
    }


    deque *res;
    res = deque_create(res);
    if (left == right) {
        deque_push_back(res, numbers[0]);
        return res;
    }


    int base;
    int l = left;
    int r = right;
    base = numbers[left];
    while (left < right) {
        while ((numbers[right] >= base) && (left < right)) {
            right--;
        }
        if (left != right) {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] <= base) && (left < right)) {
            left++;
        }
        if (left != right) {
            numbers[right] = numbers[left];
            right--;
        }
    }
    numbers[left] = base;
    base = left;
    left = l;
    right = r;
    if (left < base) {
        deque *d1;
        d1 = deque_create(d1);
        d1 = mass_to_deque(numbers, left, base-1);
        
        //deque_print(d1);
        d1_c = qs(d1, 0, base-1 - left);
        //deque_print(d1_c);
    }
    if (right > base) {
        deque *d2;
        d2 = deque_create(d2);
        d2 = mass_to_deque(numbers, base + 1, right);
        
        d2_c = qs(d2, 0, right - base - 1);
    }
    deque *tmp;
    tmp = deque_create(tmp);
    deque_push_back(tmp, numbers[base]);
    res = concatenation(d1_c, tmp);
    res = concatenation(res, d2_c);
    return res;
} 


void pr_interface() {
    printf("Input your command:\n");
    printf("1. Create deq\n2. Empty\n3. Size\n4. Push back\n5. Push front\n6. Top left\n7. Top right\n8.Pop back\n9. Pop front\n10.Print\n11. Sort\n0. Exit\n");
}


int main() {
    deque *d;
    pr_interface();
    while(true) {
        int q;
        scanf("%d", &q);
        if (q == 1) {
            d = deque_create(d);
        }
        if (q == 2) {
            bool ans = deque_isempty(d);
            if (ans) {
                printf("Yes, the deque is empty.\n");
            }
            else {
                printf("No, the deque is not empty.\n");
            }
        }
        if (q == 3) {
            int ans = deque_sizeof(d);
            printf("The size of deque is equal to %d.\n", ans);
        }
        if (q == 4) {
            printf("Input num, that is going to be pushed\n");
            int n;
            scanf("%d", &n);
            deque_push_back(d, n);
        }
        if (q == 5) {
            printf("Input num, that is going to be pushed\n");
            int n;
            scanf("%d", &n);
            deque_push_front(d, n);
        }
        if (q == 6) {
            int ans = deque_front(d);
            printf("The front elem is %d\n", ans);
        }
        if (q == 7) {
            int ans = deque_back(d);
            printf("The back elem is %d\n", ans);
        }
        if (q == 8) {
            deque_pop_back(d);
        }
        if (q == 9) {
            deque_pop_front(d);
        }
        if (q == 10) {
            deque_print(d);
        }
        if (q == 11) {
            d = qs(d, 0, deque_sizeof(d)-1);
        } 
        if (q == 0) {
            return 0;
        }
    }
}
