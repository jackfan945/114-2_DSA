#include <stdio.h>
#include <stdlib.h>

typedef enum {R, B} Color;

typedef struct AppNode {
    long long val;
    struct AppNode* left;
    struct AppNode* right;
    struct AppNode* p;
    Color color;
} AppNode;

typedef struct {
    AppNode* root;
    AppNode* app_nil;
    long long total_app_val;
} AppTree;

typedef struct MainNode {
    int id;
    int size;
    AppTree* app_list;
    Color color;
    struct MainNode* left;
    struct MainNode* right;
    struct MainNode* p;
} MainNode;

typedef struct {
    MainNode* root;
    MainNode* nil;
} MainTree;

AppNode* createAppNode(long long val, AppNode* app_nil) {
    AppNode* self = (AppNode*)malloc(sizeof(AppNode));
    self->val = val;
    self->left = self->right = app_nil;
    self->p = app_nil;
    self->color = R;
    return self;
}

AppTree* createAppTree(AppNode* app_nil) {
    AppTree* self = (AppTree*)malloc(sizeof(AppTree));
    self->root = NULL;
    self->app_nil = app_nil;
    self->total_app_val = 0;
    return self;
}

MainNode* createMainNode(int id, MainNode* nil) {
    MainNode* self = (MainNode*)malloc(sizeof(MainNode));
    self->id = id;
    self->size = 1;
    self->app_list = NULL;
    self->color = R;
    self->left = self->right = nil;
    self->p = nil;
    return self;
}

MainTree* createMainTree(MainNode* nil) {
    MainTree* self = (MainTree*)malloc(sizeof(MainTree));
    self->root = NULL;
    self->nil = nil;
    return self;
}

AppNode* app_nil_init() {
    AppNode* self = createAppNode(-1, NULL);
    self->left = self->right = self;
    self->color = B;
    return self;
}

MainNode* nil_init() {
    MainNode* self = createMainNode(-1, NULL);
    self->left = self->right = self;
    self->size = 0;
    self->color = B;
    return self;
}

void main_left_rotate(MainTree* tree, MainNode* x) {
    MainNode* y = x->right;
    x->right = y->left;
    if(y->left != tree->nil) y->left->p = x;
    y->p = x->p;
    if(x->p == tree->nil) tree->root = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->left = x;
    x->p = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    return;
}

void main_right_rotate(MainTree* tree, MainNode* x) {
    MainNode* y = x->left;
    x->left = y->right;
    if(y->right != tree->nil) y->right->p = x;
    y->p = x->p;
    if(x->p == tree->nil) tree->root = y;
    else if(x == x->p->left)x->p->left = y;
    else x->p->right = y;
    y->right = x;
    x->p = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    return;
}

void main_insert_fixup(MainTree* tree, MainNode* curr) {
    while(curr->p->color == R) {
        if(curr->p->p == tree->nil) {
            //printf("your Dad's root\n");
            break;
        }
        else if(curr->p == curr->p->p->left){// if curr's Dad is Pop's left child, Unc is right child.
            MainNode* unc = curr->p->p->right;
            if(unc->color == R){ // case 1: Unc is red
                curr->p->color = unc->color = B;
                unc->p->color = R;
                curr = unc->p; // switch curr to its Pop
            }
            else {
                if(curr == curr->p->right) { // case 2-1: Unc is black and curr is Dad's right child
                    curr = curr->p;
                    main_left_rotate(tree, curr);
                }
                curr->p->color = B;
                curr->p->p->color = R;
                main_right_rotate(tree, curr->p->p);
            }
        }
        else { // if curr's Dad is Pop's right child, Unc is left
            MainNode* unc = curr->p->p->left;
            if(unc->color == R){
                curr->p->color = unc->color = B;
                unc->p->color = R;
                curr = unc->p;
            }
            else {
                if(curr == curr->p->left) {
                    curr = curr->p;
                    main_right_rotate(tree, curr);
                }
                curr->p->color = B;
                curr->p->p->color = R;
                main_left_rotate(tree, curr->p->p);
            }
        }
    }
    tree->root->color = B;
    return;
}

void main_insert(MainTree* tree, MainNode* new) {
    int left = 0;
    long long new_sum = new->app_list->total_app_val;
    MainNode* curr = tree->root;
    MainNode* prev;
    if(tree->root == NULL) {
        tree->root = new;
        new->p = tree->nil;
        return;
    }
    while(curr != tree->nil) {
        prev = curr;
        curr->size++;
        if(new_sum < curr->app_list->total_app_val || (new_sum == curr->app_list->total_app_val && new->id >     curr->id)) {
            curr = curr->right;
            left = 1;
        }
        else {
            curr = curr->left;
            left = 0;          
        }
    }
    if(left == 0) prev->left = new;
    else prev->right = new;
    new->p = prev;
    main_insert_fixup(tree, new);
    return;
}

void main_delete_fixup(MainTree* tree, MainNode* x) {
    MainNode* w;
    while(x != tree->root && x->color == B) {
        if(x == x->p->left) {
            w = x->p->right;
            if(w->color == R) { // case 1: x's brother is red
                w->color = B;
                x->p->color = R;
                main_left_rotate(tree, x->p);
                w = x->p->right; // assign a new brother
            }
            if(w->left->color == B && w->right->color == B) {// case 2: both nephews are black
                w->color = R;
                x = x->p;
            }
            else {
                if(w->right->color == B) { // case 3: left nephew red, right nephew black
                w->color = R;
                w->left->color = B;
                main_right_rotate(tree, w);
                w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = B;
                w->right->color = B;
                main_left_rotate(tree, x->p);
                x = tree->root;
            }
        }
        else {
            w = x->p->left;
            if(w->color == R) {
                w->color = B;
                x->p->color = R;
                main_right_rotate(tree, x->p);
                w = x->p->left;
            }
            if(w->left->color == B && w->right->color == B) {
                w->color = R;
                x = x->p;
            }
            else {
                if(w->left->color == B) {
                    w->color = R;
                    w->right->color = B;
                    main_left_rotate(tree, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = B;
                w->left->color = B;
                main_right_rotate(tree, x->p);
                x = tree->root;
            }
        }
    }
    x->color = B;
}

MainNode* main_delete(MainTree* tree, MainNode* x) {
    if(tree->root == NULL) return NULL;
    MainNode* y = x;
    MainNode* x_replacement, *x_parent;
    Color y_original_col = y->color;
    if(x->left == tree->nil) { // case 1: no left child
        x_replacement = x->right;
        x_parent = x->p;
        if(x->p == tree->nil || x->p == NULL) tree->root = x->right;
        else if(x == x->p->left) x->p->left = x->right;
        else x->p->right = x->right;
        x->right->p = x->p;
    }
    else if(x->right == tree->nil) { // case 2: no right child
        x_replacement = x->left;
        x_parent = x->p;
        if(x->p == tree->nil || x->p == NULL) tree->root = x->left;
        else if(x == x->p->left) x->p->left = x->left;
        else x->p->right = x->left;
        x->left->p = x->p;
    }
    else { // case 3: two children
        y = x->right;
        while(y->left != tree->nil) y = y->left;
        y_original_col = y->color;
        x_replacement = y->right;
        x_parent = y->p;
        if(y->p == x) y->right->p = y; // written for case y->right
        else {
            y->p->left = y->right;
            y->right->p = y->p;
            y->right = x->right;
            y->right->p = y;
        }
        if (x->p == tree->nil || x->p == NULL) tree->root = y;
        else if (x == x->p->left) x->p->left = y;
        else x->p->right = y;
        y->p = x->p;
        y->left = x->left;
        y->left->p = y;
        y->color = x->color;
        y->size = x->size;
        if(x_parent == x) x_parent = y;
    }

    MainNode* curr;
    while(x_parent != tree->nil) {
        x_parent->size--;
        x_parent = x_parent->p;
    }
    if(y_original_col == B) {
        main_delete_fixup(tree, x_replacement);
    }
    x->left = x->right = tree->nil;
    x->size = 1;
    x->color = R;
    return x;
}

void app_left_rotate(AppTree* tree, AppNode* x) {
    AppNode* y = x->right;
    x->right = y->left;
    if(y->left != tree->app_nil) y->left->p = x;
    y->p = x->p;
    if(x->p == tree->app_nil) tree->root = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->left = x;
    x->p = y->p;
    return;
}

void app_right_rotate(AppTree* tree, AppNode* x) {
    AppNode* y = x->left;
    x->left = y->right;
    if(y->right != tree->app_nil) y->right->p = x;
    y->p = x->p;
    if(x->p == tree->app_nil) tree->root = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->right = x;
    x->p = y;
    return;
}

void app_insert_fixup(AppTree* tree, AppNode* curr) {
    //printf("entered fixup\n");
    while(curr->p->color == R) {
        //printf("needs to be fixed\n");
        if(curr->p->p == tree->app_nil) {
            //printf("your Dad's root\n");
            break;
        }
        else if(curr->p == curr->p->p->left) {
            //printf("Dad's a left child\n");
            AppNode* unc = curr->p->p->right;
            if(unc->color == R) {
                //printf("case 1\n");
                curr->p->color = unc->color = B;
                unc->p->color = R;
                curr = curr->p->p;
            }
            else {
                if(curr == curr->p->right) {
                    //printf("case 2\n");
                    curr = curr->p;
                    app_left_rotate(tree, curr);
                }
                //printf("case 3\n");
                curr->p->color = B;
                curr->p->p->color = R;
                app_right_rotate(tree, curr->p->p);
            }
        }
        else {
            //printf("Dad's a right child\n");
            AppNode* unc = curr->p->p->left;
            if(unc->color == R) {
                //printf("case 1\n");
                curr->p->color = unc->color = B;
                curr->p->p->color = R;
                curr = curr->p->p;
            }
            else {
                if(curr == curr->p->left) {
                    //printf("case 2\n");
                    curr = curr->p;
                    app_right_rotate(tree, curr);
                }
                //printf("case 3\n");
                curr->p->color = B;
                curr->p->p->color = R;
                app_left_rotate(tree, curr->p->p);
            }
        }        
    }
    tree->root->color = B;
    //printf("Fixed up succesfully\n");
    return;
}

void app_insert(AppTree* tree, AppNode* new) {
    //printf("start inserting\n");
    int left = 0;
    AppNode* curr = tree->root;
    AppNode* prev = curr;
    if(tree->root == NULL) {
        //printf("tree->root == NULL\n");
        tree->root = new;
        new->p = tree->app_nil;
        tree->total_app_val += new->val;
        //printf("inserted successfully\n");
        return;
    }
    while(curr != tree->app_nil) {
        //printf("curr->val = %lld\n", curr->val);
        prev = curr;
        if(new->val >= curr->val) {
            curr = curr->right;
            left = 1;
        }
        else {
            curr = curr->left;
            left = 0;
        }
    }
    //printf("outta while loop\n");
    if(left == 0) prev->left = new;
    else prev->right = new;
    new->p = prev;
    app_insert_fixup(tree, new);
    tree->total_app_val += new->val;
    //printf("inserted successfully\n");
    return;
}

void app_delete_fixup(AppTree* tree, AppNode* x) {
    AppNode* w;
    while(x != tree->root && x->color == B) {
        if(x == x->p->left) {
            w = x->p->right;
            if(w->color == R) {
                w->color = B;
                x->p->color = R;
                app_left_rotate(tree, x->p);
                w = x->p->right;
            }
            if(w->left->color == B && w->right->color == B) {
                w->color = R;
                x = x->p;
            }
            else {
                if(w->right->color == B) {
                w->color = R;
                w->left->color = B;
                app_right_rotate(tree, w);
                w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = B;
                w->right->color = B;
                app_left_rotate(tree, x->p);
                x = tree->root;
            }
        }
        else {
            w = x->p->left;
            if(w->color == R) {
                w->color = B;
                x->p->color = R;
                app_right_rotate(tree, w);
                w = x->p->left;
            }
            if(w->left->color == B && w->right->color == B) {
                w->color = R;
                x = x->p;
            }
            else {
                if(w->left->color == B) {
                    w->right->color = B;
                    w->color = R;
                    app_left_rotate(tree, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = B;
                w->left->color = B;
                app_right_rotate(tree, x->p);
                x = tree->root;
            }
        }
    }
}

AppNode* app_delete(AppTree* tree, AppNode* x) {
    if(tree->root == NULL) return NULL;
    AppNode* y = x;
    AppNode* x_replacement;
    Color y_original_color = y->color;
    if(x->left == tree->app_nil) {
        x_replacement = x->right;
        if(x->p == tree->app_nil || x->p == NULL) tree->root = x->right;
        else if(x == x->p->left) x->p->left = x->right;
        else x->p->right = x->right;
        x->right->p = x->p;
    }
    else if(x->right == tree->app_nil) {
        x_replacement = x->left;
        if(x->p == tree->app_nil || x->p == NULL) tree->root = x->left;
        else if(x == x->p->left) x->p->left = x->left;
        else x->p->right = x->left;
        if(x->left != tree->app_nil) x->left->p = x->p;
    }
    else {
        y = x->right;
        while(y->left != tree->app_nil) y = y->left;
        y_original_color = y->color;
        x_replacement = y->right;
        if(y->p == x) y->right->p = y;
        else {
            y->p->left = y->right;
            y->right->p = y->p;
            y->right = x->right;
            y->right->p = y;
        }
        if(x->p == tree->app_nil || x->p == NULL) tree->root = y;
        else if(x == x->p->left) x->p->left = y;
        else x->p->right = y;
        y->p = x->p;
        y->left = x->left;
        y->left->p = y;
        y->color = x->color;
    }

    if(y_original_color == B) app_delete_fixup(tree, x_replacement);
    x->left = x->right = NULL;
    return x;
}

MainNode* search_club(MainTree* tree, int rank) {
    int curr_size = 0;
    MainNode* curr = tree->root;
    while(curr != tree->nil) {
        if(rank == curr_size + curr->left->size + 1) {
            return curr;
        }
        else if(rank > curr_size + curr->left->size + 1) {
            curr_size += curr->left->size + 1;
            curr = curr->right;
        }
        else curr = curr->left;
    }
    return NULL;
}

long long search_app(MainNode* target, long long budget) {
    AppNode* curr = target->app_list->root;
    AppNode* best = NULL;
    long long best_val = 0;
    if(curr == NULL) return 0;
    while(curr != target->app_list->app_nil) {
        if(curr->val <= budget) {
            if(best == NULL || curr->val > best->val) best = curr;
            curr = curr->right;
        }
        else curr = curr->left;
    }
    if(best != NULL) {
        best_val = best->val;
        app_delete(target->app_list, best);
    }
    target->app_list->total_app_val -= best_val;    
    return best_val;
}

int main() {
    AppNode* app_nil = app_nil_init();
    MainNode* nil = nil_init();
    MainTree* main_tree = createMainTree(nil);

    int q, n;
    long long m;
    if(scanf("%d %d %lld", &q, &n, &m) != 3) {
        fprintf(stderr, "Error: input format incorrect for q, n, m\n");
        return EXIT_FAILURE;
    }
    MainNode** node_list = (MainNode**)malloc(n * sizeof(MainNode*));

    int init_app_num, app_val;
    MainNode* new_main_node;
    AppNode* new_app_node;
    for(int i = 0; i < n; i++) {
        new_main_node = createMainNode(i + 1, nil);
        node_list[i] = new_main_node;
        new_main_node->app_list = createAppTree(app_nil);
        if(scanf("%d", &init_app_num) != 1) {
            fprintf(stderr, "Error: input format incorrect for init_app_num\n");
            return EXIT_FAILURE;
        }
        for(int j = 0; j < init_app_num; j++) {
            if(scanf("%d", &app_val) != 1) {
                fprintf(stderr, "Error: input format incorrect for app_val\n");
                return EXIT_FAILURE;
            }
            new_app_node = createAppNode(app_val, app_nil);
            //printf("app_val = %lld\n", new_app_node->val);
            app_insert(new_main_node->app_list, new_app_node);
            //printf("Node %d: total_app_val = %lld\n", new_main_node->id, new_main_node->app_list->total_app_val);
        }
        main_insert(main_tree, new_main_node);
    }


    MainNode* curr;
    /*for(int i = 0 ; i < n; i++) {
        curr = node_list[i];
        //printf("Node id: %d\nsize: %d\ntotal_app_val = %lld\n\n", curr->id, curr->size, curr->app_list->total_app_val);
    }*/

    int op, target_club_id, rank;
    long long amount;
    MainNode* target_club;
    for(int i = 0; i < q; i++) {
        if(scanf("%d", &op) != 1) {
            fprintf(stderr, "Error: input format incorrect for op");
            return EXIT_FAILURE;
        }
        switch (op)
        {
        case 1:
            if(scanf("%d %lld", &target_club_id, &amount) != 2) {
                fprintf(stderr, "Error: input format incorrect\n");
                return EXIT_FAILURE;
            }
            target_club = node_list[target_club_id - 1];
            if(target_club == NULL) {
                target_club = createMainNode(target_club_id, nil);
                node_list[target_club_id - 1] = target_club;
                target_club->app_list = createAppTree(app_nil);
            }
            new_app_node = createAppNode(amount, app_nil);
            app_insert(target_club->app_list, new_app_node);
            new_main_node = main_delete(main_tree, target_club);
            main_insert(main_tree, new_main_node);
            printf("%lld", target_club->app_list->total_app_val);
            break;

        case 2:
            if(scanf("%lld", &amount) != 1) {
                return EXIT_FAILURE;
            }
            m += amount;
            printf("%lld", m);
            break;

        case 3:
            if(scanf("%d", &rank) != 1) return EXIT_FAILURE;
            target_club = search_club(main_tree, rank);
            amount = search_app(target_club, m);
            new_main_node = main_delete(main_tree, target_club);
            main_insert(main_tree, new_main_node);
            m -= amount;
            printf("%d %lld", target_club->id, amount);
            break;
        
        default:
            break;
        }
        if(i != q - 1) printf("\n");
    }

    return 0;
}