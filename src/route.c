#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../include/route.h"

struct route* insert(struct route* node, char* key, char* value) {
    if (node == NULL) {
        struct route* new_node = (struct route*)malloc(sizeof(struct route));
        new_node->key_  = key;
        new_node->value_= value;
        new_node->left_ = NULL;
        new_node->right_= NULL;
        return new_node;
    }
    
    int cmp = strcmp(key, node->key_);

    if (cmp == 0) {
        printf("key will be overwritten!\n");
    }
    else if (cmp > 0) {
        node->right_ = insert(node->right_, key, value);
    }
    else {
        node->left_ = insert(node->left_, key, value);
    }

    return node;
}

struct route* find(struct route* node, char* key) {
    if (node == NULL)
        return NULL;
    
    int cmp = strcmp(key, node->key_);

    if (cmp == 0)
        return node;
    else if (cmp > 0)
        return find(node->right_, key);
    else
        return find(node->left_ , key);
}
