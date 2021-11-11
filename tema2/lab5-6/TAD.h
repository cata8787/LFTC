#pragma once
#include"TS.h"
#include<vector>
#include<iostream>
#include<string>
using namespace std;

class BST {

    struct node {
        TS* data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if (t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(TS* x, node* t)
    {
        if (t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if (x->getSimbol().compare(t->data->getSimbol()) < 0)
            t->left = insert(x, t->left);
        else if (x->getSimbol().compare(t->data->getSimbol()) > 0)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(string x, node* t) {
        node* temp;
        if (t == NULL)
            return NULL;
        else if (x.compare(t->data->getSimbol()) < 0)
            t->left = remove(x, t->left);
        else if (x.compare(t->data->getSimbol()) > 0)
            t->right = remove(x, t->right);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data->getSimbol(), t->right);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data->getSimbol() << "(" << t->data->getCodTS() << ")" << " ";
        inorder(t->right);
    }

    node* find(node* t, string x) {
        if (t == NULL)
            return NULL;
        else if (x.compare(t->data->getSimbol()) < 0)
            return find(t->left, x);
        else if (x.compare(t->data->getSimbol()) > 0)
            return find(t->right, x);
        else
            return t;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(TS* x) {
        root = insert(x, root);
    }

    void remove(string x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    int search(string x) {
        node* var;
        var = find(root, x);
        if (var == NULL)
            return -1;
        return var->data->getCodTS();
    }
};
