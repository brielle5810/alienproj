//
// project 3b for COP3520 Ana Garcia Andrea Mueller and Brielle Stokes
//

#ifndef PROJECT3_REDBLACKTREE_H
#define PROJECT3_REDBLACKTREE_H

#endif //PROJECT3_REDBLACKTREE_H

#include <iostream>
#include <string>
#include <vector>
#include "ufo.h"
#include <cmath>


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
    UFOSighting sighting;
    bool color;
    Node* left;
    Node* right;
    Node* parent;
    Node(UFOSighting sighting) : sighting(sighting), color(RED), left(nullptr), right(nullptr), parent(nullptr){}
};

class RedBlackTree{
private:
    Node *root;
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertion(Node *&);
    Node* insertHelp(Node *&, Node*&);
    void closestSightingByStateHelper(Node *node, const string &state, const string &city, UFOSighting &closest) const;
    Node* mostRecentSightingHelper(Node *) const;
    void sightingsInStateHelper(Node *, const string &, vector<UFOSighting> &) const;

public:
    RedBlackTree() : root(nullptr){}
    void insert(UFOSighting sighting);
    UFOSighting closestSighting(string &city, string &state);
    UFOSighting mostRecentSighting();
    vector<UFOSighting> sightingsInState(string &state);



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
    //sorted based on date
    if (root == nullptr) {
        return node;
    }

    // Assuming UFOSighting has an operator< defined based on its date
    if (node->sighting < root->sighting) {
        root->left = insertHelp(root->left, node);
        root->left->parent = root;
    } else {
        root->right = insertHelp(root->right, node);
        root->right->parent = root;
    }

    return root;
}

void RedBlackTree::insert(UFOSighting sighting) {
    Node *node = new Node(sighting);
    root = insertHelp(root, node);
    fixInsertion(node);

}


Node *RedBlackTree::mostRecentSightingHelper(Node *node) const {
    if (node == nullptr) return nullptr;
    Node *current = node;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

void RedBlackTree::sightingsInStateHelper(Node *node, const string &state, vector<UFOSighting> &sightings) const {
    if (node == nullptr) return;
    if (node->sighting.state == state) sightings.push_back(node->sighting);
    sightingsInStateHelper(node->left, state, sightings);
    sightingsInStateHelper(node->right, state, sightings);

}


UFOSighting RedBlackTree::mostRecentSighting() {
    return mostRecentSightingHelper(root)->sighting;
}

vector<UFOSighting> RedBlackTree::sightingsInState(string &state) {
    vector<UFOSighting> sightings;
    sightingsInStateHelper(root, state, sightings);
    return sightings;
}

UFOSighting RedBlackTree::closestSighting(string &city, string &state) {
    UFOSighting closest;
    closest.date.year = 0;  // Initialize with a default value indicating no sighting found yet

    closestSightingByStateHelper(root, state, city, closest);
    return closest;
}

void RedBlackTree::closestSightingByStateHelper(Node *node, const string &state, const string &city, UFOSighting &closest) const {
    if (node == nullptr) return;

    // Check if the node's sighting is in the target state and more recent than the current closest
    if (node->sighting.state == state && node->sighting.city == city ) {
        if (closest.date.year == 0 || node->sighting.date > closest.date) {
            closest = node->sighting;
        }
    }
        // If no sighting found in the specified city, check for the closest sighting in the state
    else if (node->sighting.state == state) {
        if (closest.city != city && (closest.date.year == 0 || node->sighting.date > closest.date)) {
            closest = node->sighting;
        }
    }

    // Recursively check the left and right subtrees
    closestSightingByStateHelper(node->left, state, city, closest);
    closestSightingByStateHelper(node->right, state, city, closest);
}

