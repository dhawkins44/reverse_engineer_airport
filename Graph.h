// CSCI 311 - Spring 2023
// Project 3 - Graph class header
// Author: Daniel Hawkins

#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <vector>
#include "Node.h"
#include "priorityQueue.h"

using std::shared_ptr;
using std::vector;

class Graph{
  public:
    vector<shared_ptr<Node>> nodes;
    vector<vector<int>> adjMatrix;

    Graph(int);

    void printAdjList();
    bool isNeighbor(int, int);
    void DFS();
    int DFSVisit(int, int);
    void BFS(int);
    vector<int> distancesFrom(int);
    bool isTwoColorable();
    bool isConnected();
    bool hasCycle();
    bool isReachable(int, int);
    void dijkstra(int);
    vector<int> path(shared_ptr<Node>);
};

#endif