#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct node {
    char data[40];
    struct node *left, *right;
} node;


int priority(char c) {
    switch (c) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 100;
    }
}


int power(int a, int b) {
    int ans = 1;
    for (int i = 0; i < b; i++) {
        ans *= a;
    }
    return ans;
}


int op(char data[40]) {
    if (data[0] == '+' || data[0] == '-' ||
     data[0] == '*' || data[0] == '/' || data[0] == '^') {
        return 1;
    }
    else {
        return 0;
    }
}


node *make_tree(char expr[], int first, int last) {
    int min_priority, k, prior, nest = 0;
    node *tree = (node*)malloc(sizeof(node));
    min_priority = 100;
    for (int i = first; i <= last; i++) {
        if (expr[i] == '(') {
            nest++;
        }
        else if (expr[i] == ')') {
            nest--;
        }
        if (nest > 0) {
            continue;
        }
        prior = priority(expr[i]);
        if (prior <= min_priority) {
            min_priority = prior;
            k = i;
        }
    }
    if (nest != 0) {
        printf("Wrong expression\n");
        exit(1);
    }
    if (min_priority == 100) {
        if (expr[first] == '(' && expr[last] == ')') {
            free(tree);
            return make_tree(expr, first + 1, last - 1);
        }
        else {
            k = last - first + 1;
            for (int i = 0; i < k; i++) {
                tree->data[i] = expr[first + i];
            }
            tree->data[k] = '\n';
            tree->left = NULL;
            tree->right = NULL;
            return tree;
        }
    }
    tree->data[0] = expr[k];
    tree->data[1] = '\n';
    tree->left = make_tree(expr, first, k-1);
    tree->right = make_tree(expr, k+1, last);
    return tree;
}


node *parent(node *tree, node *son) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->left == son || tree->right == son) {
        return tree;
    }
    node *left = parent(tree->left, son);
    node *right = parent(tree->right, son);
    return (left == NULL) ? right : left;
}


int is_num(node *nd) { 
    /*
    0, если операция
    1, если х
    2, если число
    */
    int n = 0;
    while(nd->data[n] != '\n') {
        if (!isdigit(nd->data[n])) {
            if (nd->data[n] == '+' || nd->data[n] == '-' || nd->data[n] == '*'
             || nd->data[n] == '/' || nd->data[n] == '^') {
                return 0;
            }
            else {
                return 1;
            }
        }
        n++;
    }
    return 2;
}


void transform(node *tree) {
    if (tree == NULL) {
        return;
    }


    if(tree->data[0] == '^') {
        if (is_num(tree->left) == 2 && is_num(tree->right) == 2) {
            int num1 = atoi(tree->left->data);
            int num2 = atoi(tree->right->data);


            int ans = power(num1, num2);
            itoa(ans, tree->data, 10);
            int n = 0;
            while (ans > 0) {
                ans /= 10;
                n++;
            }
            tree->data[n] = '\n';
            //tree->data[0] = power(num1, num2);


            free(tree->left->left);
            free(tree->left->right);
            free(tree->right->left);
            free(tree->right->right);
            tree->left = NULL;
            tree->right = NULL;
        }
        else if (is_num(tree->left) == 0 && is_num(tree->right) == 2) {
            transform(tree->left);
            transform(tree);
        }
        else if (is_num(tree->left) == 2 && is_num(tree->right) == 0) {
            transform(tree->right);
            transform(tree);
        }
        else if (is_num(tree->left) == 0 && is_num(tree->right) == 0) {
            transform(tree->left);
            transform(tree->right);
            transform(tree);
        }
        else if (is_num(tree->left) == 1 || is_num(tree->right) == 1) {
            return;
        }
    }
    transform(tree->left);
    transform(tree->right);
}


void print_expression(node *tree) {
    if (tree == NULL) {
        return;
    }
    if (op(tree->data) && op(tree->left->data) && 
    (priority(tree->left->data[0]) < priority(tree->data[0]) || 
    tree->left->data[0] == '^' && tree->data[0] == '^')) {
        printf("(");
        print_expression(tree->left);
        printf(")");
    }
    else {
        print_expression(tree->left);
    }
    for (int i = 0; i <= 40; i++) {
        if (tree->data[i] != '\n') {
            printf("%c", tree->data[i]);
            continue;
        }
        break;
    }
    if (op(tree->data) && op(tree->right->data) && 
    (priority(tree->right->data[0]) < priority(tree->data[0]) || 
    tree->right->data[0] == '^' && tree->data[0] == '^')) {
        printf("(");
        print_expression(tree->right);
        printf(")");
    }
    else {
        print_expression(tree->right);
    }
}


void print_tree(node* root, int n) {
    if (root != NULL) {
        print_tree(root->right, n + 1);
        for (int i = 0; i < n; i++) printf("\t");
        printf("%s\n", root->data);
        print_tree(root->left, n + 1);
    }
}


void print_menu() {
    printf("Input your command:\n");
    printf("1. Create tree.\n");
    printf("2. Print tree.\n");
    printf("3. Transform an expression.\n");
    printf("4. Print expression.\n");
    printf("5. Exit.\n");
    printf("________________________________\n");
}


int main() {
    FILE *inp, *out;
    inp = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    print_menu();
    node *t = NULL;
    while(1) {
        int q;
        //fscanf(inp, "%d", &q);
        scanf("%d", &q);
        if (q == 1) {
            char expr[1000];
            printf("Input your expression\n");
            //fscanf(inp, "%s", &expr);
            scanf("%s", &expr);
            int n = 0;
            while (expr[n] != '\0'){
                n++;
            }
            t = make_tree(expr, 0, n-1);
        }
        else if (q == 2) {
            print_tree(t, 0);
        }
        else if (q == 3) {
            transform(t);
        }
        else if (q == 4) {
            print_expression(t);
            printf("\n");
        }
        else if (q == 5) {
            return 0;
        }
    }
}
