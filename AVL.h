#pragma once

#ifndef AVL_H_
#define AVL_H_

#include<iostream>
#include<cstring>
using namespace std;

// Basic Structure of AVL Node
template<class T>
struct Node
{
    T key;
    int line_no;
    T file_name;
    int height;
    Node* left;
    Node* right;

    // Constructor to initialize key, line_no, file_name in Each AVL Node
    Node(T val, int line_data, T file)
    {
        key = val;
        line_no = line_data;
        file_name = file;
        height = 0;
        left = NULL;
        right = NULL;
    }
};


//Implementation of AVL tree using Node<T> *root
template<class T>
class AVL_Tree
{
private:
    Node<T>* root;

    // recursive function to insert data & also make AVL balance
    Node<T>* insert_data(Node<T>* root, T val, int line_data, T file)
    {
        if (root == NULL)
        {
            root = new Node<T>(val, line_data, file);
        }
        else if (val < root->key)
        {
            root->left = insert_data(root->left, val, line_data, file);
            if (height(root->left) - height(root->right) == 2)
            {
                if (val < root->left->key)
                {
                    root = Single_Right_Rotate(root);
                }
                else {
                    root = Double_Right_Rotate(root);
                }
            }
        }
        else if (val > root->key)
        {
            root->right = insert_data(root->right, val, line_data, file);
            if (height(root->right) - height(root->left) == 2)
            {
                if (val > root->right->key)
                {
                    root = Single_Left_Rotate(root);
                }
                else {
                    root = Double_Left_Rotate(root);
                }
            }
        }
        root->height = max(height(root->left), height(root->right)) + 1;
        return root;
    }

    // Get Height of AVL tree at any Node
    int height(Node<T>* root)
    {
        if (root == NULL)
        {
            return -1;
        }
        return root->height;
    }

    // Function for Single Right Rotation
    Node<T>* Single_Right_Rotate(Node<T>*& root)
    {
        Node<T>* temp = root->left;
        root->left = temp->right;
        temp->right = root;
        root->height = max(height(root->left), height(root->right)) + 1;
        temp->height = max(height(temp->left), root->height) + 1;
        return temp;
    }

    // Function for Single Left Rotation
    Node<T>* Single_Left_Rotate(Node<T>*& root)
    {
        Node<T>* temp = root->right;
        root->right = temp->left;
        temp->left = root;
        root->height = max(height(root->left), height(root->right)) + 1;
        temp->height = max(height(root->right), root->height) + 1;
        return temp;
    }

    // Function for Double_Left Rotation
    Node<T>* Double_Left_Rotate(Node<T>*& root)
    {
        root->right = Single_Right_Rotate(root->right);
        return Single_Left_Rotate(root);
    }

    // Function for  Double_Right_Rotation 
    Node<T>* Double_Right_Rotate(Node<T>*& root)
    {
        root->left = Single_Left_Rotate(root->left);
        return Single_Right_Rotate(root);
    }

    // Function to Print AVL Tree {Inorder Traversal}  Left-Root-Right
    void inorder(Node<T>* root)
    {
        if (root == NULL)
        {
            return;
        }
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

    // Function for Minimum Value Node in Left_Subtree
    Node<T>* MIN(Node<T>* root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else if (root->left == NULL) {
            return root;
        }
        return MIN(root->left);
    }

    // Function for Maximum Value Node in Right_Subtree
    Node<T>* MAX(Node<T>* root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else if (root->right == NULL) {
            return root;
        }
        return MAX(root->right);
    }

    // Recursive Function to remove Node & balance the AVL Tree
    Node<T>* remove(Node<T>* root, T val)
    {
        Node<T>* temp;
        if (root == NULL)
        {
            return NULL;
        }
        else if (val < root->key) {
            root->left = remove(root->left, val);
        }
        else if (val > root->key) {
            root->right = remove(root->right, val);
        }
        else if (root->left && root->right)
        {
            temp = MIN(root->right);
            root->key = temp->key;
            root->right = remove(root->right, root->key);
        }
        else {
            temp = root;
            if (root->left == NULL) {
                root = root->right;
            }
            else if (root->right == NULL) {
                root = root->left;
            }
            delete temp;
        }
        if (root == NULL)
        {
            return root;
        }
        root->height = max(height(root->left), height(root->right)) + 1;

        if (height(root->left) - height(root->right) == 2)
        {
            if (height(root->left->left) - height(root->left->right) == 1)
            {
                return Single_Left_Rotate(root);
            }
            else {
                return Double_Left_Rotate(root);
            }
        }
        else if (height(root->right) - height(root->left) == 2)
        {
            if (height(root->right->right) - height(root->right->left) == 1)
            {
                return Single_Right_Rotate(root);
            }
            else {
                return Double_Right_Rotate(root);
            }
        }
        return root;
    }

    // Function to Search Node using key & returning line_no on, which Data is Placed
    void Search(Node<T>* root, T val, int& data)
    {
        if (root == NULL)
        {
            return;
        }
        Search(root->left, val, data);
        if (val == root->key)
        {
            data = root->line_no;
        }
        Search(root->right, val, data);
    }

    // Function to Search Node using Key & returning file_name
    void Search_File(Node<T>* root, T val, T& data)
    {
        if (root == NULL)
        {
            return;
        }
        Search_File(root->left, val, data);
        if (val == root->key)
        {
            data = root->file_name;
        }
        Search_File(root->right, val, data);
    }

    // Function to shift AVL tree of machine into this AVL tree
    void shift_data(Node<T>* root)
    {
        if (root == NULL)
        {
            return;
        }
        shift_data(root->left);
        this->insert(root->key, root->line_no, root->file_name);
        shift_data(root->right);
    }

public:
    // Basic Function to call above Private Functions
    AVL_Tree()
    {
        root = NULL;
    }

    void insert(T val, int line_data, T file)
    {
        root = insert_data(root, val, line_data, file);
    }

    void remove_node(T val)
    {
        root = remove(root, val);
    }

    void display()
    {
        if (root != NULL)
        {
            cout << "Root : " << root->key << endl;
            inorder(root);
            cout << endl;
        }
        else {
            cout << "NO DATA Is Entered in this AVL Tree :)" << endl;
        }
    }

    int Find(T val)
    {
        int data = 0;
        Search(this->root, val, data);
        return data;
    }

    T Find_File(T val)
    {
        T data = "";
        Search_File(this->root, val, data);
        return data;
    }

    void shift_data_from_different_AVL_Tree(AVL_Tree<T> a)
    {
        shift_data(a.root);
    }

    ~AVL_Tree()
    {
        delete root;
    }
};

#endif