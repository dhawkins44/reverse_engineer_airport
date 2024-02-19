// CSCI 311 - Spring 2023
// Project 3 - Priority Queue header file
// Author: Daniel Hawkins

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <memory>
#include <vector>
#include "Node.h"

using std::shared_ptr;
using std::vector;

class PriorityQueue{
  public:
    PriorityQueue();

    int size();
    shared_ptr<Node> peek();
    bool empty(); 
    void push(shared_ptr<Node>);
    shared_ptr<Node> pop();
    void minHeapify(int, int);
    vector<shared_ptr<Node>> heap;

  private:
    
};

#endif
