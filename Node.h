#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

template <typename KeyType, typename DataType> class Node {
public:
  KeyType key;
  DataType data;
  Node *left;
  Node *right;

  Node(KeyType k, DataType d)
      : key(k), data(d), left(nullptr), right(nullptr) {}
};
