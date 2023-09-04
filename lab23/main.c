#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct  tree {
    int key;
    int lvl;
    struct tree *left;
    struct tree *right;
    struct tree *parent;    
} node;


node *init(node *root, int key) {
    node *tmp;
    tmp = (node*)malloc(sizeof(node));
    tmp->key = key;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;
    tmp->lvl = 0;
    root = tmp;
    return(root);
}


void *add(node *root, int key) {
    node *elem;
    elem = (node*)malloc(sizeof(node));
    elem->left = NULL;
    elem->right = NULL;
    elem->key = key;


    int tmp_key = root->key;
    node *next_node;
    node *par;
    if (tmp_key > elem->key) {
        par = root;
        next_node = root->left;
    }
    else if (tmp_key < elem->key){
        par = root;
        next_node = root->right;
    }
    else {
        printf("Такой элемент уже есть в дереве");
        free(elem);
    }


    while (next_node != NULL) {
        if (next_node->key > elem->key) {
            par = next_node;
            next_node = next_node->left;
        }
        else if (next_node->key < elem->key) {
            par = next_node;
            next_node = next_node->right;
        }
        else {
            printf("Такой элемент уже есть в дереве");
            free(elem);
        }
    }


    next_node = elem;
    next_node->parent = par;
    next_node->lvl = -1;
    if (par->key > next_node->key) {
        par->left = next_node;
    }
    else {
        par->right = next_node;
    }
}


void print_tree(node* root, int n) {
    if (root != NULL) {
        print_tree(root->right, n + 1);
        for (int i = 0; i < n; i++) printf("\t");
        printf("%d\n", root->key);
        print_tree(root->left, n + 1);
    }
}


node *find(node *root, int n) {
    node *tmp;
    tmp = root;
    while (1) {
        if (tmp == NULL) {
            printf("Такого элемента в узле нет\n");
            break;
        }
        if (tmp->key > n) {
            tmp = tmp->left;
        }
        else if (tmp->key < n) {
            tmp = tmp->right;
        }
        else {
            return tmp;
        }
    }
}


node *succ(node *root, int n) {
    node *tmp;
    tmp = root->right;
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }
    return(tmp);
}


void delete(node *root, int key) {
    node *l = find(root, key);
    node *par;
    node *new_nd;
    if ((l->left) == NULL && (l->right) == NULL) {
        par = l->parent;
        if (l == par->right) par->right = NULL;
        else par->left = NULL;
        free(l);
    }
    else if ((l->left) != NULL && (l->right) == NULL) {
        par = l->parent;
        if (l == par->right) {
            par->right = l->left;
            par->right->parent = par;
        } 
        else {
            par->left = l->left;
            par->left->parent = par;
        }
        free(l);
    }
    else if ((l->left) == NULL && (l->right) != NULL) {
        par = l->parent;
        if (l == par->right) {
            par->right = l->right;
            par->right->parent = par;
        } 
        else {
            par->left = l->right;
            par->left->parent = par;
        }
        free(l);
    }
    else if ((l->left) != NULL && (l->right) != NULL) {
        new_nd = succ(l, key);
        l->key = new_nd->key;
        if (new_nd->right == NULL) {
            if (new_nd->parent->left == new_nd) {
                new_nd->parent->left = NULL;
            }
            else {
                new_nd->parent->right = NULL;
            }
        }
        else {
            if (new_nd->parent->left == new_nd) {
                new_nd->parent->left = new_nd->right;
            }
            else {
                new_nd->parent->left = new_nd->right;
            }   
        }
        free(new_nd);
    }
}




void custom(node *root, int lvl_prev, int *min_lvl, int *ans) {
    if (root->lvl == -1) {
        root->lvl = lvl_prev + 1;
    }
    if (root->left != NULL && root->right != NULL) {
        custom(root->left, lvl_prev+1, min_lvl, ans);
        custom(root->right, lvl_prev+1, min_lvl, ans);
    }
    else if (root->left != NULL && root->right == NULL) {
        custom(root->left, lvl_prev+1, min_lvl, ans);
    }
    else if (root->left == NULL && root->right != NULL) {
        custom(root->right, lvl_prev+1, min_lvl, ans);
    }
    else {
        if (root->lvl < *min_lvl) {
            *min_lvl = root->lvl;
            *ans = root->key;
        }
    }
}


void print_interface() {
    printf("Введите одну из комманд:\n");
    printf("Инициализация дерева: 1 n\n");
    printf("Добавление нового узла: 2 n\n");
    printf("Текстовая визуализация дерева: 3\n");
    printf("Удаление узла: 4 n\n");
    printf("Определить значение листа дерева, имеющего минимальную глубину: 5\n");
    printf("Выход из программы: 0\n");
}


int main() {
    //FILE *f;
    //f = fopen("input.txt", "r");
    print_interface();
    while (true) {
        int c;
        node *root;
        //fscanf(f, "%d", &c);
        scanf("%d", &c);
        if (c == 1) {
            int n;
            //fscanf(f, "%d", &n);
            scanf("%d", &n);
            root = init(root, n);
        }
        else if (c == 2) {
            int n;
            //fscanf(f, "%d", &n);
            scanf("%d", &n);
            add(root, n);
        }
        else if (c == 3) {
            print_tree(root, 0);
        }
        else if (c == 4) {
            int n;
            //fscanf(f, "%d", &n);
            scanf("%d", &n);
            delete(root, n);
        }
        else if (c == 5) {
            int min_lvl = 1e9;
            int ans = root->key;
            int *m_l = &min_lvl;
            int *an = &ans;
            custom(root, 0, m_l, an);
            printf("%d\n", ans);
        }
        else if (c == 0) {
            return 0;
        }
    }
    
}
