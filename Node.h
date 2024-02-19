// CSCI 311 - Spring 2023
// Project 3 - Node Class
// Author: Daniel Hawkins

#ifndef NODE_H
#define NODE_H

#include <memory>
#include <string>
#include <vector>

using std::shared_ptr;
using std::string;
using std::vector;

class Node{
  public:
    int id;
    int idTwo;
    int dist;
    int discovered;
    int finished;
    bool visited;
    bool isChgStation;
    shared_ptr<Node> predecessor;
    string color;
    vector<shared_ptr<Node>> neighbors;
    
    Node();
    Node(int);
};

#endif