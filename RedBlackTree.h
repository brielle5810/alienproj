//
// project 3b for COP3520 Ana Garcia Andrea Mueller and Brielle Stokes
//

#ifndef PROJECT3_REDBLACKTREE_H
#define PROJECT3_REDBLACKTREE_H

#endif //PROJECT3_REDBLACKTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * Red Black Trees are a type of balanced binary search tree that use a specific
 * set of riles to ensure that the tree is always balanced.
 * -Red Black Trees are self-balancing, meaning that the tree adijusts itself automatically
 * after each insertion or deletion operation
 *
 * Properties:
 * 1. Root is always black
 * 2. Every Leaf is black
 * 3. Children of a red node are black, no 2 consecutive red nodes
 * 4. The number of black nodes in any path from root to leaf is the same
 */
enum Color{RED, BLACK};

struct Node{
    string ufo;
    int data;
    bool color;
    Node* left;
    Node* right;
    Node* parent;
    Node(string ufo, int data) : ufo(ufo), data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr){}
};

class RedBlackTree{
private:
    Node *root;
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertion(Node *&);
    Node* insertHelp(Node *&, Node*&);
    void inorderHelper(Node *&, vector<string>&);

public:
    RedBlackTree() : root(nullptr){}
    void insert(string ufo, int data);
    vector<string> inorderTraversal();
};

void RedBlackTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;

}

void RedBlackTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;

}

void RedBlackTree::fixInsertion(Node *&node) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = node->parent->parent;

        /*  Case : A
            Parent of node is left child of Grand-parent of node */
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;

            /* Case : 1
               The uncle of node is also red
               Only Recoloring required */
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                /* Case : 2
                   node is right child of its parent
                   Left-rotation required */
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }

                /* Case : 3
                   node is left child of its parent
                   Right-rotation required */
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }

            /* Case : B
               Parent of node is right child of Grand-parent of node */
        else {
            Node *uncle = grandparent->left;

            /*  Case : 1
                The uncle of node is also red
                Only Recoloring required */
            if ((uncle != nullptr) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                /* Case : 2
                   node is left child of its parent
                   Right-rotation required */
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }

                /* Case : 3
                   node is right child of its parent
                   Left-rotation required */
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    root->color = BLACK;

}

Node *RedBlackTree::insertHelp(Node *&root, Node *&node) {
    if (root == nullptr){
        return node;
    }
    if(node -> data < root -> data){
        root-> left = insertHelp(root-> left, node);
        root -> left -> parent = root;
    } else if (node -> data > root -> data){
        root -> right = insertHelp(root->right, node);
        root -> right -> parent = root;
    }
    return root;
}

void RedBlackTree::insert(string ufo, int data) {
    Node *node = new Node(ufo, data);
    root = insertHelp(root, node);
    fixInsertion(node);

}

void RedBlackTree::inorderHelper(Node *&node, vector<string> &UFOs) {
    if (node == nullptr){
        return;
    }
    inorderHelper(node->left, UFOs);
    UFOs.push_back(node->ufo);
    inorderHelper(node-> right, UFOs);
}

vector<string> RedBlackTree::inorderTraversal() {
    vector<string> UFOs;
    inorderHelper(root, UFOs);
    return UFOs;

}
