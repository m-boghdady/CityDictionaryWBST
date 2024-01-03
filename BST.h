#pragma once
#include "Node.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename KeyType, typename DataType> class BST {
private:
  Node<KeyType, DataType> *root;

  void destroy(Node<KeyType, DataType> *node);
  Node<KeyType, DataType> *insert(Node<KeyType, DataType> *node, KeyType key,
                                  DataType data);
  Node<KeyType, DataType> *search(Node<KeyType, DataType> *node, KeyType key);
  Node<KeyType, DataType> *remove(Node<KeyType, DataType> *node, KeyType key);
  void inOrder(Node<KeyType, DataType> *node);
  void preOrder(Node<KeyType, DataType> *node);
  void levelOrder(Node<KeyType, DataType> *node);
  void save_inorder(Node<KeyType, DataType> *node, ofstream &file);

public:
  BST();
  ~BST();
  void insert(KeyType key, DataType data);
  Node<KeyType, DataType> *search(KeyType key);
  void retrieve(KeyType key, DataType &data);
  void traverse();
  void preorder();
  void levelorder();
  void remove(KeyType key);
  void save_to_file(const string &filename);
  bool empty();
};

//  constructor
template <typename KeyType, typename DataType> BST<KeyType, DataType>::BST() {
  root = nullptr;
}

//  Destructor
template <typename KeyType, typename DataType> BST<KeyType, DataType>::~BST() {
  destroy(root);
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::destroy(Node<KeyType, DataType> *node) {
  if (node) {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::insert(KeyType key, DataType data) {
  root = insert(root, key, data);
}

template <typename KeyType, typename DataType>
Node<KeyType, DataType> *
BST<KeyType, DataType>::insert(Node<KeyType, DataType> *node, KeyType key,
                               DataType data) {
  if (!node)
    return new Node<KeyType, DataType>(key, data);

  if (key < node->key) {
    node->left = insert(node->left, key, data);
  } else if (key > node->key) {
    node->right = insert(node->right, key, data);
  }

  return node;
}

template <typename KeyType, typename DataType>
bool BST<KeyType, DataType>::empty() {
  return root == nullptr;
}

template <typename KeyType, typename DataType>
Node<KeyType, DataType> *BST<KeyType, DataType>::search(KeyType key) {
  return search(root, key);
}

template <typename KeyType, typename DataType>
Node<KeyType, DataType> *
BST<KeyType, DataType>::search(Node<KeyType, DataType> *node, KeyType key) {
  if (!node)
    return nullptr;

  if (key == node->key)
    return node;
  else if (key < node->key)
    return search(node->left, key);
  else
    return search(node->right, key);
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::retrieve(KeyType key, DataType &data) {
  Node<KeyType, DataType> *node = search(key);
  if (node)
    data = node->data;
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::inOrder(Node<KeyType, DataType> *node) {
  if (node) {
    inOrder(node->left);
    cout << node->key << ": " << node->data << endl;
    inOrder(node->right);
  }
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::traverse() {
  inOrder(root);
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::preorder() {
  preOrder(root);
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::preOrder(Node<KeyType, DataType> *node) {
  if (node) {
    cout << node->key << ": " << node->data << endl;
    preOrder(node->left);
    preOrder(node->right);
  }
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::levelorder() {
  levelOrder(root);
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::levelOrder(Node<KeyType, DataType> *node) {
  if (!node)
    return;

  queue<Node<KeyType, DataType> *> q;
  q.push(node);

  while (!q.empty()) {
    Node<KeyType, DataType> *current = q.front();
    q.pop();

    cout << current->key << ": " << current->data << endl;

    if (current->left)
      q.push(current->left);
    if (current->right)
      q.push(current->right);
  }
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::remove(KeyType key) {
  root = remove(root, key);
}

template <typename KeyType, typename DataType>
Node<KeyType, DataType> *
BST<KeyType, DataType>::remove(Node<KeyType, DataType> *node, KeyType key) {
  if (!node)
    return nullptr;

  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  } else {
    if (!node->left) {
      Node<KeyType, DataType> *temp = node->right;
      delete node;
      return temp;
    } else if (!node->right) {
      Node<KeyType, DataType> *temp = node->left;
      delete node;
      return temp;
    }

    Node<KeyType, DataType> *temp = minValueNode(node->right);
    node->key = temp->key;
    node->data = temp->data;
    node->right = remove(node->right, temp->key);
  }

  return node;
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::save_to_file(const std::string &filename) {
  ofstream file(filename);

  if (!file.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return;
  }

  save_inorder(root, file);

  file.close();
}

template <typename KeyType, typename DataType>
void BST<KeyType, DataType>::save_inorder(Node<KeyType, DataType> *node,
                                          ofstream &file) {
  if (node == nullptr) {
    return;
  }

  save_inorder(node->left, file);

  file << node->data.cityName << " " << node->data.latitude << " "
       << node->data.longitude << " " << node->data.country << std::endl;

  save_inorder(node->right, file);
}
